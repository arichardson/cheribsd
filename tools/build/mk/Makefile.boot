# $FreeBSD$

.if empty(CROSSBUILD)
CFLAGS+=	-I${WORLDTMP}/legacy/usr/include
DPADD+=		${WORLDTMP}/legacy/usr/lib/libegacy.a
LDADD+=		-legacy
LDFLAGS+=	-L${WORLDTMP}/legacy/usr/lib
.elif ${CROSSBUILD} == "linux"
CFLAGS+=	-I/usr/include/bsd -DLIBBSD_OVERLAY=1 -D_GNU_SOURCE=1 -D__unused= -DEFTYPE=EINVAL
LDFLAGS+=	-lbsd
.elif ${CROSSBUILD} == "mac"
CFLAGS+=	-D_DARWIN_C_SOURCE=1 -D__packed= -D__unused=
.endif

# we do not want to capture dependencies referring to the above
UPDATE_DEPENDFILE= no
