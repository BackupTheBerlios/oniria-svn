dnl Process this file with autoconf to produce a configure script.
dnl $Id$

AC_PREREQ([2.52])

AC_INIT([libogur], [0.1.0], [choman@foto-koszalin.pl])
AC_CONFIG_AUX_DIR(scripts)
AC_CANONICAL_BUILD
AC_CANONICAL_HOST
AC_CANONICAL_TARGET
AM_INIT_AUTOMAKE(AC_PACKAGE_NAME, AC_PACKAGE_VERSION)
AM_MAINTAINER_MODE

AC_REVISION([$Revision$])
AC_CONFIG_SRCDIR([src/ogur.cc])

AC_CONFIG_HEADERS(config.h)
AC_CONFIG_FILES([libogur-config
		 Makefile
		 scripts/Makefile 
		 src/Makefile
		 src/ogur_config.h
		 libogur.pc
	 	 doxygen.cfg
		],
		[chmod -f +x libogur-config])

OGUR_MAJOR_VERSION=0
OGUR_MINOR_VERSION=1
OGUR_MICRO_VERSION=0
OGUR_INTERFACE_AGE=0
OGUR_BINARY_AGE=0
OGUR_VERSION=$OGUR_MAJOR_VERSION.$OGUR_MINOR_VERSION.$OGUR_MICRO_VERSION

AC_SUBST(OGUR_MAJOR_VERSION)
AC_SUBST(OGUR_MINOR_VERSION)
AC_SUBST(OGUR_MICRO_VERSION)
AC_SUBST(OGUR_VERSION)
AC_SUBST(OGUR_INTERFACE_AGE)
AC_SUBST(OGUR_BINARY_AGE)

# libtool versioning
LT_RELEASE=$OGUR_MAJOR_VERSION.$OGUR_MINOR_VERSION
LT_CURRENT=`expr $OGUR_MICRO_VERSION - $OGUR_INTERFACE_AGE`
LT_REVISION=$OGUR_INTERFACE_AGE
LT_AGE=`expr $OGUR_BINARY_AGE - $OGUR_INTERFACE_AGE`
AC_SUBST(LT_RELEASE)
AC_SUBST(LT_CURRENT)
AC_SUBST(LT_REVISION)
AC_SUBST(LT_AGE)
# Define version stuff
AC_DEFINE_UNQUOTED(OGUR_MAJOR_VERSION, $OGUR_MAJOR_VERSION, [ogur major version])
AC_DEFINE_UNQUOTED(OGUR_MINOR_VERSION, $OGUR_MINOR_VERSION, [ogur minor version])
AC_DEFINE_UNQUOTED(OGUR_MICRO_VERSION, $OGUR_MICRO_VERSION, [ogur micro version])
AC_DEFINE_UNQUOTED(OGUR_INTERFACE_AGE, $OGUR_INTERFACE_AGE, [ogur interface age])
AC_DEFINE_UNQUOTED(OGUR_BINARY_AGE, $OGUR_BINARY_AGE, [ogur binary age])

dnl Checks for programs.
AC_PROG_CXX
AC_ISC_POSIX
AC_PROG_INSTALL
AC_PROG_LIBTOOL
AC_LIBTOOL_EXTRA_LDFLAGS
AC_PATH_PROG(QTMOC, moc)

dnl Checks for header files.
dnl AC_CHECK_HEADERS(stdio.h stdlib.h stdint.h errno.h string.h strings.h assert.h \
dnl		  unistd.h sys/select.h sys/time.h sys/types.h \
dnl		  malloc.h sys/socket.h netinet/in.h netdb.h fcntl.h],
dnl		 [],
dnl		 [AC_ERROR([cannot find one of required header file..
dnl		  your system is a bit strange.])])

#AC_CHECK_HEADERS([stringprep.h], [],
#		 [AC_MSG_ERROR([stringprep.h not found])])

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

#AC_CHECK_LIB(idn, stringprep_convert, [], [AC_MSG_ERROR([libidn not found])])
AC_LANG_PUSH(C++)
PKG_CHECK_MODULES(QT, [QtCore >= 4.0.1 QtXml >= 4.0.1, QtGui >= 4.0.1])
AC_LANG_POP(C++)


AC_OUTPUT

