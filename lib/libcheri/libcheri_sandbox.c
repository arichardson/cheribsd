/*-
 * Copyright (c) 2012-2017 Robert N. M. Watson
 * Copyright (c) 2015 SRI International
 * All rights reserved.
 *
 * This software was developed by SRI International and the University of
 * Cambridge Computer Laboratory under DARPA/AFRL contract (FA8750-10-C-0237)
 * ("CTSRD"), as part of the DARPA CRASH research programme.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <sys/cdefs.h>

#include <sys/types.h>
#include <sys/param.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/sysctl.h>

#include <cheri/cheri.h>
#include <cheri/cheric.h>

#include <assert.h>
#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <inttypes.h>
#include <libgen.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "libcheri_ccall.h"
#include "libcheri_class.h"
#include "libcheri_enter.h"
#include "libcheri_fd.h"
#include "libcheri_invoke.h"
#include "libcheri_init.h"
#include "libcheri_private.h"
#include "libcheri_sandbox.h"
#include "libcheri_sandbox_elf.h"
#include "libcheri_sandbox_internal.h"
#include "libcheri_sandbox_methods.h"
#include "libcheri_sandboxasm.h"
#include "libcheri_system.h"

#if !__has_feature(capabilities)
#error "This code requires a CHERI-aware compiler"
#endif

static size_t			num_sandbox_classes;
static size_t			max_sandbox_classes;
static struct sandbox_class	**sandbox_classes;

static struct sandbox_provided_classes	*main_provided_classes;
static struct sandbox_required_methods	*main_required_methods;

/*
 * libcheri_system_vtable is defined here and not in libcheri_system.h to avoid
 * running into https://github.com/CTSRD-CHERI/cheribsd/issues/180
 */
vm_offset_t * __capability	 libcheri_system_vtable;


static int	sandbox_program_init(void);

#define	SANDBOX_STACK_SIZE	32 * PAGE_SIZE

/*
 * Control verbose debugging output around sandbox invocation; disabled by
 * default but may be enabled using an environmental variable.
 */
int sb_verbose;

void
sandbox_init(void)
{

	if (getenv("LIBCHERI_SB_VERBOSE"))
		sb_verbose = 1;

	if (sandbox_program_init() < -1) {
		err(1, "%s: sandbox_program_init", __func__);
	}
}

/* XXXBD: should be done in sandbox_init(), but need access to argv[0]. */
int
sandbox_program_init(void)
{
	int fd = -1;
	int mib[4];
	mib[0] = CTL_KERN;
	mib[1] = KERN_PROC;
	mib[2] = KERN_PROC_PATHNAME;
	mib[3] = -1;
	char buf[MAXPATHLEN];
	size_t cb = sizeof(buf);

	/* XXXBD: do this with RTLD or hypothentical getexecfd(). */
	if ((sysctl(mib, 4, buf, &cb, NULL, 0) != -1) && cb > 0) {
		if ((fd = open(buf, O_RDONLY)) == -1)
			warn("%s: open %s (from kern.proc.pathname.(-1))",
			    __func__, buf);
	}

	if (sandbox_parse_ccall_methods(fd, &main_provided_classes,
	    &main_required_methods) == -1) {
		warn("%s: sandbox_parse_ccall_methods for main program",
		    __func__);
		close(fd);
		return (-1);
	}
#ifdef __CHERI_PURE_CAPABILITY__
	// This needs full address space $pcc
	void *datacap = cheri_clearperm(
	    cheri_setoffset(cheri_getpcc(), 0), CHERI_PERM_EXECUTE);
#else
	void *__capability datacap = cheri_getdefault();
#endif
	if (sandbox_set_required_method_variables(
		datacap, main_required_methods) == -1) {
		warnx("%s: sandbox_set_required_method_variables for main "
		    "program", __func__);
		return (-1);
	}
	/* XXXBD: cheri_system needs to do this. */
	libcheri_system_vtable = sandbox_make_vtable(NULL,
	    "_libcheri_system_object", main_provided_classes);
	libcheri_fd_vtable = sandbox_make_vtable(NULL, "libcheri_fd",
	    main_provided_classes);
	close(fd);
	return (0);
}

static int
sandbox_program_sanity_check(void)
{
	size_t i;
	struct sandbox_required_methods *required_methods;

	assert(main_provided_classes != NULL);
	assert(main_required_methods != NULL);

	/*
	 * Check that all methods in the main program have been
	 * provided.
	 */
	if (sandbox_get_unresolved_methods(main_required_methods) > 0) {
		warnx("%s: main program has %zu unresolved methods", __func__,
		    sandbox_get_unresolved_methods(main_required_methods));
		if (sb_verbose)
			sandbox_warn_unresolved_methods(main_required_methods);
		return (-1);
	}

	/*
	 * Sanity check sandbox classes for unresolved methods.
	 *
	 * XXXBD: Does this make sense here or should we just fail attempts
	 * to call sandbox_object_new() on incomplete classes?
	 */
	for (i = 0; i < num_sandbox_classes; i++) {
		required_methods = sandbox_classes[i]->sbc_required_methods;
		assert(required_methods != NULL);
		if (sandbox_get_unresolved_methods(required_methods) > 0) {
			warnx("%s: sandbox %s has %zu unresolved methods",
			    __func__, sandbox_classes[i]->sbc_path,
			    sandbox_get_unresolved_methods(required_methods));
			if (sb_verbose)
				sandbox_warn_unresolved_methods(
				    required_methods);
			return (-1);
		}
	}

	return (0);
}

#if 0
int
sandbox_program_fini(void)
{

	if (main_provided_classes != NULL)
		sandbox_free_provided_classes(main_provided_classes);
	main_provided_classes = NULL;
	if (main_required_methods != NULL)
		sandbox_free_required_methods(main_required_methods);
	main_required_methods = NULL;
	return (0);
}
#endif

int
sandbox_class_new(const char *path, size_t maxmaplen,
    struct sandbox_class **sbcpp)
{
	struct sandbox_class *sbcp;
	struct sandbox_class **new_sandbox_classes;
	int fd, saved_errno;
	size_t i;

	loader_dbg("Loading sandbox %s\n", path);
	fd = open(path, O_RDONLY);
	if (fd == -1) {
		saved_errno = errno;
		warn("%s: open %s", __func__, path);
		errno = saved_errno;
		return (-1);
	}

	sbcp = calloc(1, sizeof(*sbcp));
	if (sbcp == NULL) {
		saved_errno = errno;
		warn("%s: malloc", __func__);
		close(fd);
		errno = saved_errno;
		return (-1);
	}
	sbcp->sbc_fd = fd;
	sbcp->sbc_path = strdup(path);
	if (sbcp->sbc_path == NULL) {
		saved_errno = errno;
		warn("%s: fstat %s", __func__, path);
		goto error;
	}

	if (fstat(sbcp->sbc_fd, &sbcp->sbc_stat) < 0) {
		saved_errno = errno;
		warn("%s: fstat %s", __func__, path);
		goto error;
	}

	/*
	 * Parse the ELF and produce mappings for code and data.
	 */
#ifdef SPLIT_CODE_DATA
	if ((sbcp->sbc_codemap = sandbox_parse_elf64(fd, path,
	    SANDBOX_LOADELF_CODE)) == NULL) {
		saved_errno = EINVAL;
		warnx("%s: sandbox_parse_elf64(CODE) failed for %s", __func__,
		    path);
		goto error;
	}
	if ((sbcp->sbc_datamap = sandbox_parse_elf64(fd, path,
	    SANDBOX_LOADELF_DATA)) == NULL) {
		saved_errno = EINVAL;
		warnx("%s: sandbox_parse_elf64(DATA) failed for %s", __func__,
		    path);
		goto error;
	}
#else
	if ((sbcp->sbc_datamap = sandbox_parse_elf64(fd, path,
	    SANDBOX_LOADELF_CODE | SANDBOX_LOADELF_DATA)) == NULL) {
		saved_errno = EINVAL;
		warnx("%s: sandbox_parse_elf64(DATA) failed for %s", __func__,
		    path);
		goto error;
	}
#endif

	/*
	 * Don't allow sandbox binaries to request over maxmaplen of
	 * either code or data.
	 *
	 * XXXBD: It would be nice to have some sort of default sane
	 * value, but programs can have astonishing amounts of BSS
	 * relative to file size.
	 */
#ifdef SPLIT_CODE_DATA
	if (maxmaplen > 0 &&
	    sandbox_map_maxoffset(sbcp->sbc_codemap) > maxmaplen) {
		saved_errno = EINVAL;
		warnx("%s: %s code too large", __func__, path);
		goto error;
	}
#endif
	if (maxmaplen > 0 &&
	    sandbox_map_maxoffset(sbcp->sbc_datamap) > maxmaplen) {
		saved_errno = EINVAL;
		warnx("%s: %s data too large", __func__, path);
		goto error;
	}

	/*
	 * Initialise the class mapping: this will be the code capabilty used
	 * by all sandboxes.  For now, we just map the code segment in exactly
	 * the same way we do the data segment.  In the future, we will want
	 * to initialise them differently.
	 */
	if (sandbox_class_load(sbcp) < 0) {
		saved_errno = EINVAL;
		warnx("%s: sandbox_class_load() failed for %s", __func__,
		    path);
		goto error;
	}

	/*
	 * Resolve methods in other classes.
	 */
	for (i = 0; i < num_sandbox_classes; i++) {
		/* XXXBD: Check there are no conflicting class names */
		if (sandbox_resolve_methods(sbcp->sbc_provided_classes,
		    sandbox_classes[i]->sbc_required_methods) < 0) {
			saved_errno = EINVAL;
			warnx("%s: sandbox_resolve_methods() failed providing "
			    "methods from %s to %s", __func__, path,
			    sandbox_classes[i]->sbc_path);
			goto error;
		}
		if (sandbox_resolve_methods(
		    sandbox_classes[i]->sbc_provided_classes,
		    sbcp->sbc_required_methods) < 0) {
			saved_errno = EINVAL;
			warnx("%s: sandbox_resolve_methods() failed providing "
			    "methods from %s to %s", __func__,
			    sandbox_classes[i]->sbc_path, path);
			goto error;
		}
	}
	/*
	 * XXXBD: failure to initalize main_*_methods should eventually
	 * be impossible and trigger an assert.
	 */
	if (main_provided_classes != NULL && main_required_methods != NULL) {
		if (sandbox_resolve_methods(sbcp->sbc_provided_classes,
		    main_required_methods) < 0) {
			saved_errno = EINVAL;
			warnx("%s: sandbox_resolve_methods() failed providing "
			    "methods from %s main program", __func__, path);
			goto error;
		}
		if (sandbox_resolve_methods(main_provided_classes,
		    sbcp->sbc_required_methods) < 0) {
			saved_errno = EINVAL;
			warnx("%s: sandbox_resolve_methods() failed providing "
			    "methods from main program to %s", __func__,
			    path);
			goto error;
		}
	}

	/*
	 * XXXAR: this crashes in the main program because we don't have a
	 * writable $pcc. I'm not quite sure what this is doing, but if I
	 * #if 0 this code we get further into startup.
	 */
#ifndef SPLIT_CODE_DATA
	/*
	 * Update main program method variables.
	 *
	 * XXXBD: Doing this in every class is inefficient.
	 */
#ifdef __CHERI_PURE_CAPABILITY__
	// This needs full address space $pcc
	void *datacap = cheri_clearperm(
	    cheri_setoffset(cheri_getpcc(), 0), CHERI_PERM_EXECUTE);
#else
	void *__capability datacap = cheri_getdefault();
#endif
	if (sandbox_set_required_method_variables(
		datacap, main_required_methods) == -1) {
		warnx("%s: sandbox_set_required_method_variables for main "
		    "program", __func__);
		return (-1);
	}
#endif

	/*
	 * Register the class on the list of classes.
	 */
	if (max_sandbox_classes == 0) {
		max_sandbox_classes = 4;
		if ((sandbox_classes = calloc(max_sandbox_classes,
		   sizeof(*sandbox_classes))) == NULL) {
			saved_errno = errno;
			warn("%s: calloc sandbox_classes array", __func__);
			goto error;
		}
	}
	if (num_sandbox_classes >= max_sandbox_classes) {
		if ((new_sandbox_classes = realloc(sandbox_classes,
		    max_sandbox_classes * 2 * sizeof(*sandbox_classes)))
		    == NULL) {
			saved_errno = errno;
			warn("%s: realloc sandbox_classes array", __func__);
			goto error;
		}
		free(sandbox_classes);
		sandbox_classes = new_sandbox_classes;
		max_sandbox_classes *= 2;
	}
	sandbox_classes[num_sandbox_classes++] = sbcp;

	*sbcpp = sbcp;
	return (0);

error:
	if (sbcp->sbc_path != NULL)
		free(sbcp->sbc_path);
	close(sbcp->sbc_fd);
	free(sbcp);
	errno = saved_errno;
	return (-1);
}

int
sandbox_class_method_declare(struct sandbox_class *sbcp, u_int methodnum,
    const char *methodname __unused)
{

	if (methodnum >= SANDBOX_CLASS_METHOD_COUNT) {
		errno = E2BIG;
		return (-1);
	}
	if (sbcp->sbc_sandbox_methods[methodnum] != NULL) {
		errno = EEXIST;
		return (-1);
	}
	return (0);
}

void
sandbox_class_destroy(struct sandbox_class *sbcp)
{

	sandbox_class_unload(sbcp);
	close(sbcp->sbc_fd);
	free(sbcp->sbc_path);
	free(sbcp);
}

/*
 * XXXRW: I'm not really happy with this approach of limiting access to system
 * resources via flags passed here.  We should use a more general security
 * model based on capability permissions.  However, this does allow us to more
 * generally get up and running.
 * XXXBD: I broke the flags when switching system functions to cheri_ccallee.
 */
int
sandbox_object_new_flags(struct sandbox_class *sbcp, size_t heaplen,
    uint flags, struct sandbox_object **sbopp)
{
	struct sandbox_object *sbop;
	int error, saved_errno;

	if (sandbox_program_sanity_check() < 0)
		errx(1, "%s: sandbox_program_sanity_check", __func__);

	sbop = calloc(1, sizeof(*sbop));
	if (sbop == NULL)
		return (-1);
	sbop->sbo_sandbox_classp = sbcp;
	sbop->sbo_flags = flags;
	sbop->sbo_heaplen = heaplen;

	/*
	 * XXXRW: In due course, stack size should be a parameter rather than
	 * a constant.
	 */
	sbop->sbo_stacklen = SANDBOX_STACK_SIZE;
	sbop->sbo_stackmem = mmap(0, sbop->sbo_stacklen,
	    PROT_READ | PROT_WRITE, MAP_ANON, -1, 0);
	if (sbop->sbo_stackmem == NULL) {
		saved_errno = errno;
		free(sbop);
		errno = saved_errno;
		return (-1);
	}

	/*
	 * Configure the object's stack before loading so that the stack
	 * capability can be installed into sandbox metadata.  Note that the
	 * capability is local (can't be shared) and can store local pointers
	 * (i.e., further stack-derived capabilities such as return
	 * addresses).
	 */
	sbop->sbo_stackcap = cheri_local(cheri_ptrperm(sbop->sbo_stackmem,
	    sbop->sbo_stacklen, CHERI_PERM_LOAD | CHERI_PERM_LOAD_CAP |
	    CHERI_PERM_STORE | CHERI_PERM_STORE_CAP |
	    CHERI_PERM_STORE_LOCAL_CAP));
	sbop->sbo_csp = ((char *__capability )sbop->sbo_stackcap +
	    sbop->sbo_stacklen);

	/*
	 * Set up the sandbox's code/data segments, sealed capabilities.
	 */
	error = sandbox_object_load(sbcp, sbop);
	if (error) {
		saved_errno = errno;
		goto error;
	}

	/*
	 * Invoke object instance's constructors.  Note that, given the tight
	 * binding of class and object in the sandbox library currently, this
	 * will need to change in the future.  We also need to think more
	 * carefully about the mechanism here.
	 */
	if (libcheri_invoke(sbop->sbo_cheri_object_rtld,
	    SANDBOX_RUNTIME_CONSTRUCTORS,
	    0, 0, 0, 0, 0, 0, 0, 0,
	    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL) != 0) {
		sandbox_object_unload(sbop);
		saved_errno = EPROT;
		goto error;
	}

	error = sandbox_object_protect(sbcp, sbop);
	if (error) {
		saved_errno = errno;
		goto error;
	}

	/*
	 * Now that constructors have completed, return object.
	 */
	*sbopp = sbop;
	return (0);
error:
	(void)munmap(sbop->sbo_stackmem, sbop->sbo_stacklen);
	free(sbop);
	errno = saved_errno;
	return (-1);
}

#define	SANDBOX_OBJECT_FLAG_DEFAULT	(SANDBOX_OBJECT_FLAG_CONSOLE |	\
	    SANDBOX_OBJECT_FLAG_ALLOCFREE | SANDBOX_OBJECT_FLAG_USERFN)
int
sandbox_object_new(struct sandbox_class *sbcp, size_t heaplen,
    struct sandbox_object **sbopp)
{

	return (sandbox_object_new_flags(sbcp, heaplen,
	    SANDBOX_OBJECT_FLAG_DEFAULT, sbopp));
}

/*
 * libcheri system objects require a sandbox_object to be used with common
 * invocation and rtld vectors, so provide a way to initialise those here.
 *
 * NB: System classes have NULL sbop->sbo_sandbox_classp pointers, which
 * allows us to differentiate them during later object destruction.
 *
 * XXXRW: Should we instead require that system classes also register
 * sandbox_class instances?  That would be more consistent...
 */
int
sandbox_object_new_system_object(void * __capability private_data,
    void * __capability invoke_pcc, vm_offset_t * __capability vtable,
    struct sandbox_object **sbopp)
{

	/*
	 * XXXRW: We skip the sanity check because system objects might be
	 * created before we've loaded classes that the main program depends
	 * on.  This is a bit backwards, but it's unclear what to do about it.
	if (sandbox_program_sanity_check() < 0)
		errx(1, "%s: sandbox_program_sanity_check", __func__);
	 */

	*sbopp = calloc(1, sizeof(**sbopp));
	if (*sbopp == NULL)
		return (-1);

	(*sbopp)->sbo_idc =
	    (__cheri_tocap void * __capability)(void *)*sbopp;
	(*sbopp)->sbo_rtld_pcc = NULL;
	(*sbopp)->sbo_invoke_pcc = invoke_pcc;
	(*sbopp)->sbo_vtable = vtable;
	(*sbopp)->sbo_ddc = cheri_getdefault();
	(*sbopp)->sbo_private_data = private_data;

	/* XXXRW: Does this remain the right capability to use for TLS? */
#ifdef __CHERI_CAPABILITY_TLS__
	__asm__ volatile("creadhwr %0, $chwr_userlocal": "=C"((*sbopp)->sbo_libcheri_tls));
#else
	(*sbopp)->sbo_libcheri_tls = cheri_getdefault();
#endif

	/*
	 * Construct sealed invocation capabilities for use with
	 * libcheri_invoke(), which will transition to the libcheri CCall
	 * trampoline.  Leave rtld calabilities as NULL.
	 */
        (*sbopp)->sbo_cheri_object_invoke =
            libcheri_sandbox_make_sealed_invoke_object(
	    (__cheri_tocap struct sandbox_object * __capability)*sbopp);
	return (0);
}

int
sandbox_object_stack_reset(struct sandbox_object *sbop)
{
	if (mmap(sbop->sbo_stackmem, sbop->sbo_stacklen,
	    PROT_READ | PROT_WRITE, MAP_ANON | MAP_FIXED, -1, 0) ==
	    MAP_FAILED) {
		warn("%s: stack reset", __func__);
		return (-1);
	}
	return 0;
}

int
sandbox_object_reset(struct sandbox_object *sbop)
{
	struct sandbox_class *sbcp;

	assert(sbop != NULL);
	sbcp = sbop->sbo_sandbox_classp;
	assert(sbcp != NULL);

	/*
	 * Reset loader-managed address space.
	 */
	if (sandbox_object_reload(sbop) == -1) {
		warn("%s:, sandbox_object_reload", __func__);
		return (-1);
	}

	/*
	 * Reset external stack.
	 */
	if (sandbox_object_stack_reset(sbop)) {
		return (-1);
	}

	/*
	 * (Re-)invoke object instance's constructors.  Note that, given the
	 * tight binding of class and object in the sandbox library currently,
	 * this will need to change in the future.  We also need to think more
	 * carefully about the mechanism here.
	 */
	(void)libcheri_invoke(sbop->sbo_cheri_object_rtld,
	    SANDBOX_RUNTIME_CONSTRUCTORS,
	    0, 0, 0, 0, 0, 0, 0, 0,
	    cheri_zerocap(), cheri_zerocap(), cheri_zerocap(),
	    cheri_zerocap(), cheri_zerocap(), cheri_zerocap(),
	    cheri_zerocap(), cheri_zerocap());

	return (0);
}

register_t
sandbox_object_invoke(struct sandbox_object *sbop, register_t methodnum,
    register_t a1, register_t a2, register_t a3,
    register_t a4, register_t a5, register_t a6, register_t a7,
    void * __capability c3, void * __capability c4, void * __capability c5,
    void * __capability c6, void * __capability c7, void * __capability c8,
    void * __capability c9, void * __capability c10)
{
	struct sandbox_class *sbcp;
	uint64_t sample, start;
	register_t v0;

	/*
	 * XXXRW: TODO:
	 *
	 * 1. What about $v1, capability return values?
	 * 2. Does the right thing happen with $a0..$a7, $c3..$c10?
	 */
	sbcp = sbop->sbo_sandbox_classp;
	start = cheri_get_cyclecount();
	v0 = libcheri_invoke(sbop->sbo_cheri_object_invoke,
	    CHERI_INVOKE_METHOD_LEGACY_INVOKE,
	    methodnum,
	    a1, a2, a3, a4, a5, a6, a7,
	    c3, c4, c5, c6, c7, c8, c9, c10);
	sample = cheri_get_cyclecount() - start;
	return (v0);
}

void
sandbox_object_destroy(struct sandbox_object *sbop)
{
	struct sandbox_class *sbcp;

	/*
	 * NB: There is a minor bit of recursion here to free the dependent
	 * system object.
	 */
	sbcp = sbop->sbo_sandbox_classp;
	if (sbcp != NULL) {
		/* Explicitly loaded class. */
		sandbox_object_unload(sbop);		/* Unmap memory. */
		(void)munmap(sbop->sbo_stackmem, sbop->sbo_stacklen);

		/* Ensure recursion is bounded. */
		assert(sbop->sbo_sandbox_system_objectp->sbo_sandbox_classp ==
		    NULL);
		sandbox_object_destroy(sbop->sbo_sandbox_system_objectp);
	} else {
		/* System class. */
		assert(sbop->sbo_stackmem == NULL);
		assert(sbop->sbo_sandbox_system_objectp == NULL);
	}
	free_c(sbop->sbo_vtable);
	bzero(sbop, sizeof(*sbop));		/* Clears tags. */
	free(sbop);
}

struct cheri_object
sandbox_object_getobject(struct sandbox_object *sbop)
{

	return (sbop->sbo_cheri_object_invoke);
}

void * __capability
sandbox_object_getsandboxdata(struct sandbox_object *sbop)
{

	return (sbop->sbo_idc);
}

void * __capability
sandbox_object_getsandboxstack(struct sandbox_object *sbop)
{

	return (sbop->sbo_stackcap);
}

struct cheri_object
sandbox_object_getsystemobject(struct sandbox_object *sbop)
{

	return (sbop->sbo_cheri_object_system);
}

void * __capability
sandbox_object_private_get(struct sandbox_object *sbop)
{

	return (sbop->sbo_private_data);
}

void * __capability
sandbox_object_private_get_idc(void)
{
	struct sandbox_object *sbop;

	sbop = (struct sandbox_object *)(__cheri_fromcap void *)cheri_getidc();
	return (sbop->sbo_private_data);
}
