dnl Process this file with autoconf to produce a configure script.
dnl $Id$

AC_PREREQ([2.52])

AC_INIT([libosasl], [0.1.0], [choman@foto-koszalin.pl])
AC_CONFIG_AUX_DIR(scripts)
AC_CANONICAL_BUILD
AC_CANONICAL_HOST
AC_CANONICAL_TARGET
AM_INIT_AUTOMAKE(AC_PACKAGE_NAME, AC_PACKAGE_VERSION)
AM_MAINTAINER_MODE

AC_REVISION([$Revision$])
AC_CONFIG_SRCDIR([src/sasl.cc])

AC_CONFIG_HEADERS(config.h)
AC_CONFIG_FILES([libosasl-config
		 Makefile
		 scripts/Makefile 
		 src/Makefile
		 src/osasl_config.h
		 libosasl.pc
		 doxygen.cfg
		],
		[chmod -f +x libosasl-config])

OSASL_MAJOR_VERSION=0
OSASL_MINOR_VERSION=1
OSASL_MICRO_VERSION=0
OSASL_INTERFACE_AGE=0
OSASL_BINARY_AGE=0
OSASL_VERSION=$OSASL_MAJOR_VERSION.$OSASL_MINOR_VERSION.$OSASL_MICRO_VERSION

AC_SUBST(OSASL_MAJOR_VERSION)
AC_SUBST(OSASL_MINOR_VERSION)
AC_SUBST(OSASL_MICRO_VERSION)
AC_SUBST(OSASL_VERSION)
AC_SUBST(OSASL_INTERFACE_AGE)
AC_SUBST(OSASL_BINARY_AGE)

# libtool versioning
LT_RELEASE=$OSASL_MAJOR_VERSION.$OSASL_MINOR_VERSION
LT_CURRENT=`expr $OSASL_MICRO_VERSION - $OSASL_INTERFACE_AGE`
LT_REVISION=$OSASL_INTERFACE_AGE
LT_AGE=`expr $OSASL_BINARY_AGE - $OSASL_INTERFACE_AGE`
AC_SUBST(LT_RELEASE)
AC_SUBST(LT_CURRENT)
AC_SUBST(LT_REVISION)
AC_SUBST(LT_AGE)
# Define version stuff
AC_DEFINE_UNQUOTED(OSASL_MAJOR_VERSION, $OSASL_MAJOR_VERSION, [osasl major version])
AC_DEFINE_UNQUOTED(OSASL_MINOR_VERSION, $OSASL_MINOR_VERSION, [osasl minor version])
AC_DEFINE_UNQUOTED(OSASL_MICRO_VERSION, $OSASL_MICRO_VERSION, [osasl micro version])
AC_DEFINE_UNQUOTED(OSASL_INTERFACE_AGE, $OSASL_INTERFACE_AGE, [osasl interface age])
AC_DEFINE_UNQUOTED(OSASL_BINARY_AGE, $OSASL_BINARY_AGE, [osasl binary age])

dnl Checks for programs.
AC_PROG_CXX
AC_ISC_POSIX
AC_PROG_INSTALL
AC_PROG_LIBTOOL
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
PKG_CHECK_MODULES(QT, [QtCore >= 4.0.1 QtXml >= 4.0.1])
PKG_CHECK_MODULES(OCRYPT, [libocrypt >= 0.1.0])
AC_LANG_POP(C++)


AC_OUTPUT

