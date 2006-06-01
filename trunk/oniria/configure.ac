dnl Process this file with autoconf to produce a configure script.
dnl $Id$

AC_PREREQ([2.52])

AC_INIT([oniria], [0.1.0], [choman@foto-koszalin.pl])
AC_CONFIG_AUX_DIR(scripts)
AC_CANONICAL_BUILD
AC_CANONICAL_HOST
AC_CANONICAL_TARGET
AM_INIT_AUTOMAKE(AC_PACKAGE_NAME, AC_PACKAGE_VERSION)
AM_MAINTAINER_MODE

AC_REVISION([$Revision$])
AC_CONFIG_SRCDIR([src/oniria.cc])

AC_CONFIG_HEADERS(config.h)
AC_CONFIG_FILES([Makefile 
		 oniria-config
		 scripts/Makefile 
		 src/Makefile
		 src/oniria_config.h
		 doxygen.cfg
		],
		[chmod -f +x oniria-config])

ONIRIA_MAJOR_VERSION=0
ONIRIA_MINOR_VERSION=1
ONIRIA_MICRO_VERSION=0
ONIRIA_VERSION=$ONIRIA_MAJOR_VERSION.$ONIRIA_MINOR_VERSION.$ONIRIA_MICRO_VERSION

AC_SUBST(ONIRIA_MAJOR_VERSION)
AC_SUBST(ONIRIA_MINOR_VERSION)
AC_SUBST(ONIRIA_MICRO_VERSION)
AC_SUBST(ONIRIA_VERSION)

# Define version stuff
AC_DEFINE_UNQUOTED(ONIRIA_MAJOR_VERSION, $ONIRIA_MAJOR_VERSION, [oniria major version])
AC_DEFINE_UNQUOTED(ONIRIA_MINOR_VERSION, $ONIRIA_MINOR_VERSION, [oniria minor version])
AC_DEFINE_UNQUOTED(ONIRIA_MICRO_VERSION, $ONIRIA_MICRO_VERSION, [oniria micro version])

PLUGINDIR="$libexecdir/oniria/plugins"
AC_SUBST(PLUGINDIR)

dnl Checks for programs.
AC_PROG_CXX
AC_ISC_POSIX
AC_PROG_INSTALL
AC_PATH_PROGS(ZIP, [zip pkzip], [zip])

dnl Checks for header files.
dnl AC_CHECK_HEADERS([stdio.h stdlib.h stdint.h errno.h string.h strings.h assert.h \
dnl		  unistd.h sys/select.h sys/time.h sys/types.h \
dnl		  malloc.h sys/socket.h netinet/in.h netdb.h fcntl.h],
dnl		 [],
dnl		 [AC_ERROR([cannot find one of required header file..
dnl		  your system is a bit strange.])])

dnl Checks for typedefs, structures, and compiler characteristics.

dnl Checks for library functions.
dnl AC_CHECK_FUNCS([malloc calloc free \
dnl		sprintf \
dnl		strlen strchr strcat strdup index \
dnl		memmove memcpy memcmp \
dnl		socket connect bind accept listen recv send \
dnl		gethostbyname htons htonl \
dnl		fcntl select close \
dnl		],
dnl	       [],
dnl	       [AC_ERROR([cannot find one of required functions..
dnl	          your system is a bit strange.])])

PKG_CHECK_MODULES(OGUR, [libogur >= 0.1.0])

AC_OUTPUT

dnl
dnl $Log$
dnl

