dnl Process this file with autoconf to produce a configure script.
dnl $Id$

AC_PREREQ([2.52])

AC_INIT([jabber], [0.1.0], [choman@foto-koszalin.pl])
AC_CONFIG_AUX_DIR(scripts)
AC_CANONICAL_BUILD
AC_CANONICAL_HOST
AC_CANONICAL_TARGET
AM_INIT_AUTOMAKE(AC_PACKAGE_NAME, AC_PACKAGE_VERSION)
AM_MAINTAINER_MODE

AC_REVISION([$Revision$])
AC_CONFIG_SRCDIR([src/jabber.cc])

AC_CONFIG_HEADERS(config.h)
AC_CONFIG_FILES([Makefile 
		 scripts/Makefile 
		 src/Makefile
		],
		[])

dnl Checks for programs.
AC_PROG_CXX
AC_ISC_POSIX
AC_PROG_INSTALL
AC_PROG_LIBTOOL
AC_PATH_PROG(QTMOC, moc)

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

PKG_CHECK_MODULES(QT, [QtCore >= 4.0.1 QtXml >= 4.0.1])
PKG_CHECK_MODULES(ONIR, [libonir >= 0.1.0 liboim >= 0.1.0 liboxml >= 0.1.0 libosasl >= 0.1.0])
AM_PATH_ONIRIA

AC_OUTPUT

