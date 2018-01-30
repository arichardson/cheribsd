/*
 * System call numbers.
 *
 * DO NOT EDIT-- this file is automatically generated.
 * $FreeBSD$
 */

#define	CHERIABI_SYS_cheriabi_syscall	0
#define	CHERIABI_SYS_exit	1
#define	CHERIABI_SYS_fork	2
#define	CHERIABI_SYS_cheriabi_read	3
#define	CHERIABI_SYS_cheriabi_write	4
#define	CHERIABI_SYS_cheriabi_open	5
#define	CHERIABI_SYS_close	6
#define	CHERIABI_SYS_cheriabi_wait4	7
				/* 8 is obsolete old creat */
#define	CHERIABI_SYS_cheriabi_link	9
#define	CHERIABI_SYS_cheriabi_unlink	10
				/* 11 is obsolete execv */
#define	CHERIABI_SYS_cheriabi_chdir	12
#define	CHERIABI_SYS_fchdir	13
				/* 14 is obsolete fbsd11_mknod */
#define	CHERIABI_SYS_cheriabi_chmod	15
#define	CHERIABI_SYS_cheriabi_chown	16
				/* 17 is obsolete obreak */
				/* 18 is obsolete getstatfs */
				/* 19 is obsolete lseek */
#define	CHERIABI_SYS_getpid	20
#define	CHERIABI_SYS_cheriabi_mount	21
#define	CHERIABI_SYS_cheriabi_unmount	22
#define	CHERIABI_SYS_setuid	23
#define	CHERIABI_SYS_getuid	24
#define	CHERIABI_SYS_geteuid	25
#define	CHERIABI_SYS_ptrace	26
#define	CHERIABI_SYS_cheriabi_recvmsg	27
#define	CHERIABI_SYS_cheriabi_sendmsg	28
#define	CHERIABI_SYS_recvfrom	29
#define	CHERIABI_SYS_accept	30
#define	CHERIABI_SYS_getpeername	31
#define	CHERIABI_SYS_getsockname	32
#define	CHERIABI_SYS_cheriabi_access	33
#define	CHERIABI_SYS_cheriabi_chflags	34
#define	CHERIABI_SYS_fchflags	35
#define	CHERIABI_SYS_sync	36
#define	CHERIABI_SYS_kill	37
				/* 38 is obsolete stat */
#define	CHERIABI_SYS_getppid	39
				/* 40 is obsolete lstat */
#define	CHERIABI_SYS_dup	41
				/* 42 is obsolete pipe */
#define	CHERIABI_SYS_getegid	43
#define	CHERIABI_SYS_cheriabi_profil	44
#define	CHERIABI_SYS_cheriabi_ktrace	45
				/* 46 is obsolete sigaction */
#define	CHERIABI_SYS_getgid	47
				/* 48 is obsolete sigprocmask */
#define	CHERIABI_SYS_cheriabi_getlogin	49
#define	CHERIABI_SYS_cheriabi_setlogin	50
#define	CHERIABI_SYS_cheriabi_acct	51
				/* 52 is obsolete sigpending */
#define	CHERIABI_SYS_cheriabi_sigaltstack	53
#define	CHERIABI_SYS_cheriabi_ioctl	54
#define	CHERIABI_SYS_reboot	55
#define	CHERIABI_SYS_cheriabi_revoke	56
#define	CHERIABI_SYS_cheriabi_symlink	57
#define	CHERIABI_SYS_cheriabi_readlink	58
#define	CHERIABI_SYS_cheriabi_execve	59
#define	CHERIABI_SYS_umask	60
#define	CHERIABI_SYS_cheriabi_chroot	61
				/* 62 is obsolete fstat */
				/* 63 is obsolete ogetkerninfo */
				/* 64 is obsolete getpagesize */
#define	CHERIABI_SYS_msync	65
#define	CHERIABI_SYS_vfork	66
				/* 67 is obsolete vread */
				/* 68 is obsolete vwrite */
				/* 69 is obsolete sbrk */
				/* 70 is obsolete sstk */
				/* 71 is obsolete mmap */
				/* 72 is obsolete ovadvise */
#define	CHERIABI_SYS_munmap	73
#define	CHERIABI_SYS_cheriabi_mprotect	74
#define	CHERIABI_SYS_cheriabi_madvise	75
				/* 76 is obsolete vhangup */
				/* 77 is obsolete vlimit */
#define	CHERIABI_SYS_mincore	78
#define	CHERIABI_SYS_cheriabi_getgroups	79
#define	CHERIABI_SYS_cheriabi_setgroups	80
#define	CHERIABI_SYS_getpgrp	81
#define	CHERIABI_SYS_setpgid	82
#define	CHERIABI_SYS_cheriabi_setitimer	83
				/* 84 is obsolete owait */
#define	CHERIABI_SYS_cheriabi_swapon	85
#define	CHERIABI_SYS_cheriabi_getitimer	86
				/* 87 is obsolete ogethostname */
				/* 88 is obsolete osethostname */
#define	CHERIABI_SYS_getdtablesize	89
#define	CHERIABI_SYS_dup2	90
#define	CHERIABI_SYS_fcntl	92
#define	CHERIABI_SYS_cheriabi_select	93
#define	CHERIABI_SYS_fsync	95
#define	CHERIABI_SYS_setpriority	96
#define	CHERIABI_SYS_socket	97
#define	CHERIABI_SYS_connect	98
				/* 99 is obsolete oaccept */
#define	CHERIABI_SYS_getpriority	100
				/* 101 is obsolete osend */
				/* 102 is obsolete orecv */
				/* 103 is obsolete sigreturn */
#define	CHERIABI_SYS_bind	104
#define	CHERIABI_SYS_setsockopt	105
#define	CHERIABI_SYS_listen	106
				/* 107 is obsolete vtimes */
				/* 108 is obsolete sigvec */
				/* 109 is obsolete sigblock */
				/* 110 is obsolete sigsetmask */
				/* 111 is obsolete sigsuspend */
				/* 112 is obsolete sigstack */
				/* 113 is obsolete orecvmsg */
				/* 114 is obsolete osendmsg */
				/* 115 is obsolete vtrace */
#define	CHERIABI_SYS_cheriabi_gettimeofday	116
#define	CHERIABI_SYS_cheriabi_getrusage	117
#define	CHERIABI_SYS_getsockopt	118
#define	CHERIABI_SYS_cheriabi_readv	120
#define	CHERIABI_SYS_cheriabi_writev	121
#define	CHERIABI_SYS_cheriabi_settimeofday	122
#define	CHERIABI_SYS_fchown	123
#define	CHERIABI_SYS_fchmod	124
				/* 125 is obsolete orecvfrom */
#define	CHERIABI_SYS_setreuid	126
#define	CHERIABI_SYS_setregid	127
#define	CHERIABI_SYS_cheriabi_rename	128
				/* 129 is obsolete truncate */
				/* 130 is obsolete ftruncate */
#define	CHERIABI_SYS_flock	131
#define	CHERIABI_SYS_cheriabi_mkfifo	132
#define	CHERIABI_SYS_sendto	133
#define	CHERIABI_SYS_shutdown	134
#define	CHERIABI_SYS_socketpair	135
#define	CHERIABI_SYS_cheriabi_mkdir	136
#define	CHERIABI_SYS_cheriabi_rmdir	137
#define	CHERIABI_SYS_cheriabi_utimes	138
				/* 139 is obsolete sigreturn */
#define	CHERIABI_SYS_cheriabi_adjtime	140
				/* 141 is obsolete ogetpeername */
				/* 142 is obsolete ogethostid */
				/* 143 is obsolete sethostid */
				/* 144 is obsolete getrlimit */
				/* 145 is obsolete setrlimit */
				/* 146 is obsolete killpg */
#define	CHERIABI_SYS_setsid	147
#define	CHERIABI_SYS_cheriabi_quotactl	148
				/* 149 is obsolete oquota */
				/* 150 is obsolete ogetsockname */
#define	CHERIABI_SYS_cheriabi_nlm_syscall	154
#define	CHERIABI_SYS_cheriabi_nfssvc	155
				/* 156 is obsolete getdirentries */
				/* 157 is obsolete statfs */
				/* 158 is obsolete fstatfs */
#define	CHERIABI_SYS_cheriabi_lgetfh	160
#define	CHERIABI_SYS_cheriabi_getfh	161
				/* 162 is obsolete getdomainname */
				/* 163 is obsolete setdomainname */
				/* 164 is obsolete uname */
#define	CHERIABI_SYS_cheriabi_sysarch	165
#define	CHERIABI_SYS_cheriabi_rtprio	166
				/* 169 is obsolete semsys */
				/* 170 is obsolete msgsys */
				/* 171 is obsolete shmsys */
				/* 173 is obsolete pread */
				/* 174 is obsolete pwrite */
#define	CHERIABI_SYS_setfib	175
#define	CHERIABI_SYS_cheriabi_ntp_adjtime	176
#define	CHERIABI_SYS_setgid	181
#define	CHERIABI_SYS_setegid	182
#define	CHERIABI_SYS_seteuid	183
				/* 188 is obsolete fbsd11_stat */
				/* 189 is obsolete fbsd11_fstat */
				/* 190 is obsolete fbsd11_lstat */
#define	CHERIABI_SYS_cheriabi_pathconf	191
#define	CHERIABI_SYS_fpathconf	192
#define	CHERIABI_SYS_cheriabi_getrlimit	194
#define	CHERIABI_SYS_cheriabi_setrlimit	195
				/* 196 is obsolete fbsd11_getdirentries */
				/* 197 is obsolete mmap */
				/* 198 is obsolete __syscall */
				/* 199 is obsolete lseek */
				/* 200 is obsolete truncate */
				/* 201 is obsolete ftruncate */
#define	CHERIABI_SYS___sysctl	202
#define	CHERIABI_SYS_mlock	203
#define	CHERIABI_SYS_munlock	204
#define	CHERIABI_SYS_cheriabi_undelete	205
#define	CHERIABI_SYS_cheriabi_futimes	206
#define	CHERIABI_SYS_getpgid	207
#define	CHERIABI_SYS_cheriabi_poll	209
				/* 220 is obsolete __semctl */
#define	CHERIABI_SYS_semget	221
#define	CHERIABI_SYS_cheriabi_semop	222
				/* 224 is obsolete msgctl */
#define	CHERIABI_SYS_msgget	225
#define	CHERIABI_SYS_cheriabi_msgsnd	226
#define	CHERIABI_SYS_cheriabi_msgrcv	227
#define	CHERIABI_SYS_shmat	228
				/* 229 is obsolete shmctl */
#define	CHERIABI_SYS_shmdt	230
#define	CHERIABI_SYS_shmget	231
#define	CHERIABI_SYS_cheriabi_clock_gettime	232
#define	CHERIABI_SYS_cheriabi_clock_settime	233
#define	CHERIABI_SYS_cheriabi_clock_getres	234
#define	CHERIABI_SYS_cheriabi_ktimer_create	235
#define	CHERIABI_SYS_ktimer_delete	236
#define	CHERIABI_SYS_cheriabi_ktimer_settime	237
#define	CHERIABI_SYS_cheriabi_ktimer_gettime	238
#define	CHERIABI_SYS_ktimer_getoverrun	239
#define	CHERIABI_SYS_cheriabi_nanosleep	240
#define	CHERIABI_SYS_cheriabi_ffclock_getcounter	241
#define	CHERIABI_SYS_cheriabi_ffclock_setestimate	242
#define	CHERIABI_SYS_cheriabi_ffclock_getestimate	243
#define	CHERIABI_SYS_cheriabi_clock_nanosleep	244
#define	CHERIABI_SYS_cheriabi_clock_getcpuclockid2	247
#define	CHERIABI_SYS_cheriabi_ntp_gettime	248
#define	CHERIABI_SYS_minherit	250
#define	CHERIABI_SYS_rfork	251
#define	CHERIABI_SYS_issetugid	253
#define	CHERIABI_SYS_lchown	254
#define	CHERIABI_SYS_cheriabi_aio_read	255
#define	CHERIABI_SYS_cheriabi_aio_write	256
#define	CHERIABI_SYS_cheriabi_lio_listio	257
#define	CHERIABI_SYS_cheriabi_kbounce	258
				/* 272 is obsolete fbsd11_getdents */
#define	CHERIABI_SYS_cheriabi_lchmod	274
#define	CHERIABI_SYS_cheriabi_lutimes	276
#define	CHERIABI_SYS_freebsd11_nstat	278
#define	CHERIABI_SYS_freebsd11_nfstat	279
#define	CHERIABI_SYS_freebsd11_nlstat	280
#define	CHERIABI_SYS_cheriabi_preadv	289
#define	CHERIABI_SYS_cheriabi_pwritev	290
				/* 297 is obsolete fhstatfs */
#define	CHERIABI_SYS_fhopen	298
				/* 299 is obsolete fbsd11_fhstat */
#define	CHERIABI_SYS_modnext	300
#define	CHERIABI_SYS_modstat	301
#define	CHERIABI_SYS_modfnext	302
#define	CHERIABI_SYS_modfind	303
#define	CHERIABI_SYS_kldload	304
#define	CHERIABI_SYS_kldunload	305
#define	CHERIABI_SYS_kldfind	306
#define	CHERIABI_SYS_kldnext	307
#define	CHERIABI_SYS_cheriabi_kldstat	308
#define	CHERIABI_SYS_kldfirstmod	309
#define	CHERIABI_SYS_getsid	310
#define	CHERIABI_SYS_setresuid	311
#define	CHERIABI_SYS_setresgid	312
				/* 313 is obsolete signanosleep */
#define	CHERIABI_SYS_cheriabi_aio_return	314
#define	CHERIABI_SYS_cheriabi_aio_suspend	315
#define	CHERIABI_SYS_cheriabi_aio_cancel	316
#define	CHERIABI_SYS_cheriabi_aio_error	317
				/* 318 is obsolete oaio_read */
				/* 319 is obsolete oaio_write */
				/* 320 is obsolete olio_listio */
				/* 321 is obsolete yield */
				/* 322 is obsolete thr_sleep */
				/* 323 is obsolete thr_wakeup */
#define	CHERIABI_SYS_mlockall	324
#define	CHERIABI_SYS_munlockall	325
#define	CHERIABI_SYS___getcwd	326
#define	CHERIABI_SYS_sched_setparam	327
#define	CHERIABI_SYS_sched_getparam	328
#define	CHERIABI_SYS_sched_setscheduler	329
#define	CHERIABI_SYS_sched_getscheduler	330
#define	CHERIABI_SYS_sched_yield	331
#define	CHERIABI_SYS_sched_get_priority_max	332
#define	CHERIABI_SYS_sched_get_priority_min	333
#define	CHERIABI_SYS_sched_rr_get_interval	334
#define	CHERIABI_SYS_cheriabi_utrace	335
				/* 336 is obsolete sendfile */
#define	CHERIABI_SYS_cheriabi_kldsym	337
#define	CHERIABI_SYS_cheriabi_jail	338
#define	CHERIABI_SYS_sigprocmask	340
#define	CHERIABI_SYS_sigsuspend	341
				/* 342 is obsolete sigaction */
#define	CHERIABI_SYS_sigpending	343
				/* 344 is obsolete sigreturn */
#define	CHERIABI_SYS_cheriabi_sigtimedwait	345
#define	CHERIABI_SYS_cheriabi_sigwaitinfo	346
#define	CHERIABI_SYS___acl_get_file	347
#define	CHERIABI_SYS___acl_set_file	348
#define	CHERIABI_SYS___acl_get_fd	349
#define	CHERIABI_SYS___acl_set_fd	350
#define	CHERIABI_SYS___acl_delete_file	351
#define	CHERIABI_SYS___acl_delete_fd	352
#define	CHERIABI_SYS___acl_aclcheck_file	353
#define	CHERIABI_SYS___acl_aclcheck_fd	354
#define	CHERIABI_SYS_extattrctl	355
#define	CHERIABI_SYS_extattr_set_file	356
#define	CHERIABI_SYS_extattr_get_file	357
#define	CHERIABI_SYS_extattr_delete_file	358
#define	CHERIABI_SYS_cheriabi_aio_waitcomplete	359
#define	CHERIABI_SYS_cheriabi_getresuid	360
#define	CHERIABI_SYS_cheriabi_getresgid	361
#define	CHERIABI_SYS_kqueue	362
#define	CHERIABI_SYS_extattr_set_fd	371
#define	CHERIABI_SYS_extattr_get_fd	372
#define	CHERIABI_SYS_extattr_delete_fd	373
#define	CHERIABI_SYS___setugid	374
#define	CHERIABI_SYS_eaccess	376
#define	CHERIABI_SYS_cheriabi_nmount	378
				/* 379 is obsolete kse_exit */
				/* 380 is obsolete kse_wakeup */
				/* 381 is obsolete kse_create */
				/* 382 is obsolete kse_thr_interrupt */
				/* 383 is obsolete kse_release */
#define	CHERIABI_SYS_cheriabi___mac_get_proc	384
#define	CHERIABI_SYS_cheriabi___mac_set_proc	385
#define	CHERIABI_SYS_cheriabi___mac_get_fd	386
#define	CHERIABI_SYS_cheriabi___mac_get_file	387
#define	CHERIABI_SYS_cheriabi___mac_set_fd	388
#define	CHERIABI_SYS_cheriabi___mac_set_file	389
#define	CHERIABI_SYS_cheriabi_kenv	390
#define	CHERIABI_SYS_cheriabi_lchflags	391
#define	CHERIABI_SYS_uuidgen	392
#define	CHERIABI_SYS_cheriabi_sendfile	393
#define	CHERIABI_SYS_cheriabi_mac_syscall	394
				/* 395 is obsolete fbsd11_getfsstat */
				/* 396 is obsolete fbsd11_statfs */
				/* 397 is obsolete fbsd11_ftatfs */
				/* 398 is obsolete fbsd11_fhstat */
				/* 400 is obsolete ksem_close */
				/* 401 is obsolete ksem_post */
				/* 402 is obsolete ksem_wait */
				/* 403 is obsolete ksem_trywait */
				/* 404 is obsolete ksem_init */
				/* 405 is obsolete ksem_open */
				/* 406 is obsolete ksem_unlink */
				/* 407 is obsolete ksem_getvalue */
				/* 408 is obsolete ksem_destroy */
#define	CHERIABI_SYS_cheriabi___mac_get_pid	409
#define	CHERIABI_SYS_cheriabi___mac_get_link	410
#define	CHERIABI_SYS_cheriabi___mac_set_link	411
#define	CHERIABI_SYS_extattr_set_link	412
#define	CHERIABI_SYS_extattr_get_link	413
#define	CHERIABI_SYS_extattr_delete_link	414
#define	CHERIABI_SYS_cheriabi___mac_execve	415
#define	CHERIABI_SYS_cheriabi_sigaction	416
#define	CHERIABI_SYS_cheriabi_sigreturn	417
#define	CHERIABI_SYS_cheriabi_getcontext	421
#define	CHERIABI_SYS_cheriabi_setcontext	422
#define	CHERIABI_SYS_cheriabi_swapcontext	423
#define	CHERIABI_SYS_cheriabi_swapoff	424
#define	CHERIABI_SYS___acl_get_link	425
#define	CHERIABI_SYS___acl_set_link	426
#define	CHERIABI_SYS___acl_delete_link	427
#define	CHERIABI_SYS___acl_aclcheck_link	428
#define	CHERIABI_SYS_sigwait	429
#define	CHERIABI_SYS_cheriabi_thr_create	430
#define	CHERIABI_SYS_thr_exit	431
#define	CHERIABI_SYS_thr_self	432
#define	CHERIABI_SYS_thr_kill	433
#define	CHERIABI_SYS_jail_attach	436
#define	CHERIABI_SYS_extattr_list_fd	437
#define	CHERIABI_SYS_extattr_list_file	438
#define	CHERIABI_SYS_extattr_list_link	439
				/* 440 is obsolete kse_switchin */
#define	CHERIABI_SYS_ksem_timedwait	441
#define	CHERIABI_SYS_thr_suspend	442
#define	CHERIABI_SYS_thr_wake	443
#define	CHERIABI_SYS_kldunloadf	444
#define	CHERIABI_SYS_audit	445
#define	CHERIABI_SYS_cheriabi_auditon	446
#define	CHERIABI_SYS_getauid	447
#define	CHERIABI_SYS_setauid	448
#define	CHERIABI_SYS_getaudit	449
#define	CHERIABI_SYS_setaudit	450
#define	CHERIABI_SYS_getaudit_addr	451
#define	CHERIABI_SYS_setaudit_addr	452
#define	CHERIABI_SYS_auditctl	453
#define	CHERIABI_SYS__umtx_op	454
#define	CHERIABI_SYS_cheriabi_thr_new	455
#define	CHERIABI_SYS_cheriabi_sigqueue	456
#define	CHERIABI_SYS_kmq_open	457
#define	CHERIABI_SYS_kmq_setattr	458
#define	CHERIABI_SYS_kmq_timedreceive	459
#define	CHERIABI_SYS_kmq_timedsend	460
#define	CHERIABI_SYS_cheriabi_kmq_notify	461
#define	CHERIABI_SYS_kmq_unlink	462
#define	CHERIABI_SYS_cheriabi_abort2	463
#define	CHERIABI_SYS_thr_set_name	464
#define	CHERIABI_SYS_cheriabi_aio_fsync	465
#define	CHERIABI_SYS_cheriabi_rtprio_thread	466
#define	CHERIABI_SYS_sctp_peeloff	471
#define	CHERIABI_SYS_sctp_generic_sendmsg	472
#define	CHERIABI_SYS_sctp_generic_sendmsg_iov	473
#define	CHERIABI_SYS_sctp_generic_recvmsg	474
#define	CHERIABI_SYS_cheriabi_pread	475
#define	CHERIABI_SYS_cheriabi_pwrite	476
#define	CHERIABI_SYS_cheriabi_mmap	477
#define	CHERIABI_SYS_lseek	478
#define	CHERIABI_SYS_cheriabi_truncate	479
#define	CHERIABI_SYS_ftruncate	480
#define	CHERIABI_SYS_thr_kill2	481
#define	CHERIABI_SYS_shm_open	482
#define	CHERIABI_SYS_shm_unlink	483
#define	CHERIABI_SYS_cpuset	484
#define	CHERIABI_SYS_cpuset_setid	485
#define	CHERIABI_SYS_cpuset_getid	486
#define	CHERIABI_SYS_cpuset_getaffinity	487
#define	CHERIABI_SYS_cpuset_setaffinity	488
#define	CHERIABI_SYS_cheriabi_faccessat	489
#define	CHERIABI_SYS_cheriabi_fchmodat	490
#define	CHERIABI_SYS_cheriabi_fchownat	491
#define	CHERIABI_SYS_cheriabi_fexecve	492
				/* 493 is obsolete fbsd11_fstatat */
#define	CHERIABI_SYS_cheriabi_futimesat	494
#define	CHERIABI_SYS_cheriabi_linkat	495
#define	CHERIABI_SYS_cheriabi_mkdirat	496
#define	CHERIABI_SYS_cheriabi_mkfifoat	497
				/* 498 is obsolete fbsd11_mknodat */
#define	CHERIABI_SYS_cheriabi_openat	499
#define	CHERIABI_SYS_cheriabi_readlinkat	500
#define	CHERIABI_SYS_cheriabi_renameat	501
#define	CHERIABI_SYS_cheriabi_symlinkat	502
#define	CHERIABI_SYS_cheriabi_unlinkat	503
#define	CHERIABI_SYS_posix_openpt	504
#define	CHERIABI_SYS_gssd_syscall	505
#define	CHERIABI_SYS_cheriabi_jail_get	506
#define	CHERIABI_SYS_cheriabi_jail_set	507
#define	CHERIABI_SYS_jail_remove	508
#define	CHERIABI_SYS_closefrom	509
#define	CHERIABI_SYS_cheriabi___semctl	510
#define	CHERIABI_SYS_cheriabi_msgctl	511
#define	CHERIABI_SYS_shmctl	512
#define	CHERIABI_SYS_cheriabi_lpathconf	513
				/* 514 is obsolete cap_new */
#define	CHERIABI_SYS___cap_rights_get	515
#define	CHERIABI_SYS_cap_enter	516
#define	CHERIABI_SYS_cap_getmode	517
#define	CHERIABI_SYS_pdfork	518
#define	CHERIABI_SYS_pdkill	519
#define	CHERIABI_SYS_pdgetpid	520
#define	CHERIABI_SYS_cheriabi_pselect	522
#define	CHERIABI_SYS_getloginclass	523
#define	CHERIABI_SYS_setloginclass	524
#define	CHERIABI_SYS_rctl_get_racct	525
#define	CHERIABI_SYS_rctl_get_rules	526
#define	CHERIABI_SYS_rctl_get_limits	527
#define	CHERIABI_SYS_rctl_add_rule	528
#define	CHERIABI_SYS_rctl_remove_rule	529
#define	CHERIABI_SYS_posix_fallocate	530
#define	CHERIABI_SYS_posix_fadvise	531
#define	CHERIABI_SYS_cheriabi_wait6	532
#define	CHERIABI_SYS_cap_rights_limit	533
#define	CHERIABI_SYS_cap_ioctls_limit	534
#define	CHERIABI_SYS_cap_ioctls_get	535
#define	CHERIABI_SYS_cap_fcntls_limit	536
#define	CHERIABI_SYS_cap_fcntls_get	537
#define	CHERIABI_SYS_bindat	538
#define	CHERIABI_SYS_connectat	539
#define	CHERIABI_SYS_cheriabi_chflagsat	540
#define	CHERIABI_SYS_accept4	541
#define	CHERIABI_SYS_pipe2	542
#define	CHERIABI_SYS_cheriabi_aio_mlock	543
#define	CHERIABI_SYS_cheriabi_procctl	544
#define	CHERIABI_SYS_cheriabi_ppoll	545
#define	CHERIABI_SYS_cheriabi_futimens	546
#define	CHERIABI_SYS_cheriabi_utimensat	547
#define	CHERIABI_SYS_numa_getaffinity	548
#define	CHERIABI_SYS_numa_setaffinity	549
#define	CHERIABI_SYS_fdatasync	550
#define	CHERIABI_SYS_fstat	551
#define	CHERIABI_SYS_fstatat	552
#define	CHERIABI_SYS_fhstat	553
#define	CHERIABI_SYS_getdirentries	554
#define	CHERIABI_SYS_statfs	555
#define	CHERIABI_SYS_fstatfs	556
#define	CHERIABI_SYS_getfsstat	557
#define	CHERIABI_SYS_fhstatfs	558
#define	CHERIABI_SYS_cheriabi_mknodat	559
#define	CHERIABI_SYS_cheriabi_kevent	560
#define	CHERIABI_SYS_MAXSYSCALL	561
