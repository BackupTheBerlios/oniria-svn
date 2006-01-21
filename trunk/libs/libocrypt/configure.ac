dnl Process this file with autoconf to produce a configure script.
dnl $Id$

AC_PREREQ([2.52])

AC_INIT([libocrypt], [0.1.0], [choman@foto-koszalin.pl])
AC_CONFIG_AUX_DIR(scripts)
AC_CANONICAL_BUILD
AC_CANONICAL_HOST
AC_CANONICAL_TARGET
AM_INIT_AUTOMAKE(AC_PACKAGE_NAME, AC_PACKAGE_VERSION)
AM_MAINTAINER_MODE

AC_REVISION([$Revision$])
AC_CONFIG_SRCDIR([src/crypt.cc])

AC_CONFIG_HEADERS(config.h)
AC_CONFIG_FILES([libocrypt-config
		 Makefile
		 scripts/Makefile 
		 src/Makefile
		 src/ocrypt_config.h
		 libocrypt.pc
		 doxygen.cfg
		],
		[chmod -f +x libocrypt-config])

OCRYPT_MAJOR_VERSION=0
OCRYPT_MINOR_VERSION=1
OCRYPT_MICRO_VERSION=0
OCRYPT_INTERFACE_AGE=0
OCRYPT_BINARY_AGE=0
OCRYPT_VERSION=$OCRYPT_MAJOR_VERSION.$OCRYPT_MINOR_VERSION.$OCRYPT_MICRO_VERSION

AC_SUBST(OCRYPT_MAJOR_VERSION)
AC_SUBST(OCRYPT_MINOR_VERSION)
AC_SUBST(OCRYPT_MICRO_VERSION)
AC_SUBST(OCRYPT_VERSION)
AC_SUBST(OCRYPT_INTERFACE_AGE)
AC_SUBST(OCRYPT_BINARY_AGE)

# libtool versioning
LT_RELEASE=$OCRYPT_MAJOR_VERSION.$OCRYPT_MINOR_VERSION
LT_CURRENT=`expr $OCRYPT_MICRO_VERSION - $OCRYPT_INTERFACE_AGE`
LT_REVISION=$OCRYPT_INTERFACE_AGE
LT_AGE=`expr $OCRYPT_BINARY_AGE - $OCRYPT_INTERFACE_AGE`
AC_SUBST(LT_RELEASE)
AC_SUBST(LT_CURRENT)
AC_SUBST(LT_REVISION)
AC_SUBST(LT_AGE)
# Define version stuff
AC_DEFINE_UNQUOTED(OCRYPT_MAJOR_VERSION, $OCRYPT_MAJOR_VERSION, [ocrypt major version])
AC_DEFINE_UNQUOTED(OCRYPT_MINOR_VERSION, $OCRYPT_MINOR_VERSION, [ocrypt minor version])
AC_DEFINE_UNQUOTED(OCRYPT_MICRO_VERSION, $OCRYPT_MICRO_VERSION, [ocrypt micro version])
AC_DEFINE_UNQUOTED(OCRYPT_INTERFACE_AGE, $OCRYPT_INTERFACE_AGE, [ocrypt interface age])
AC_DEFINE_UNQUOTED(OCRYPT_BINARY_AGE, $OCRYPT_BINARY_AGE, [ocrypt binary age])

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
PKG_CHECK_MODULES(QT, [QtCore >= 4.0.1])
AC_LANG_POP(C++)


AC_OUTPUT

