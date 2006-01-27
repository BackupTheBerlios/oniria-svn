dnl Process this file with autoconf to produce a configure script.
dnl $Id$

AC_PREREQ([2.52])

AC_INIT([liboxml], [0.1.0], [choman@foto-koszalin.pl])
AC_CONFIG_AUX_DIR(scripts)
AC_CANONICAL_BUILD
AC_CANONICAL_HOST
AC_CANONICAL_TARGET
AM_INIT_AUTOMAKE(AC_PACKAGE_NAME, AC_PACKAGE_VERSION)
AM_MAINTAINER_MODE

AC_REVISION([$Revision$])
AC_CONFIG_SRCDIR([src/xml.cc])

AC_CONFIG_HEADERS(config.h)
AC_CONFIG_FILES([liboxml-config
		 Makefile
		 scripts/Makefile 
		 src/Makefile
		 src/tests/Makefile
		 src/oxml_config.h
		 liboxml.pc
	 	 doxygen.cfg
		],
		[chmod -f +x liboxml-config])

OXML_MAJOR_VERSION=0
OXML_MINOR_VERSION=1
OXML_MICRO_VERSION=0
OXML_INTERFACE_AGE=0
OXML_BINARY_AGE=0
OXML_VERSION=$OXML_MAJOR_VERSION.$OXML_MINOR_VERSION.$OXML_MICRO_VERSION

AC_SUBST(OXML_MAJOR_VERSION)
AC_SUBST(OXML_MINOR_VERSION)
AC_SUBST(OXML_MICRO_VERSION)
AC_SUBST(OXML_VERSION)
AC_SUBST(OXML_INTERFACE_AGE)
AC_SUBST(OXML_BINARY_AGE)

# libtool versioning
LT_RELEASE=$OXML_MAJOR_VERSION.$OXML_MINOR_VERSION
LT_CURRENT=`expr $OXML_MICRO_VERSION - $OXML_INTERFACE_AGE`
LT_REVISION=$OXML_INTERFACE_AGE
LT_AGE=`expr $OXML_BINARY_AGE - $OXML_INTERFACE_AGE`
AC_SUBST(LT_RELEASE)
AC_SUBST(LT_CURRENT)
AC_SUBST(LT_REVISION)
AC_SUBST(LT_AGE)
# Define version stuff
AC_DEFINE_UNQUOTED(OXML_MAJOR_VERSION, $OXML_MAJOR_VERSION, [oxml major version])
AC_DEFINE_UNQUOTED(OXML_MINOR_VERSION, $OXML_MINOR_VERSION, [oxml minor version])
AC_DEFINE_UNQUOTED(OXML_MICRO_VERSION, $OXML_MICRO_VERSION, [oxml micro version])
AC_DEFINE_UNQUOTED(OXML_INTERFACE_AGE, $OXML_INTERFACE_AGE, [oxml interface age])
AC_DEFINE_UNQUOTED(OXML_BINARY_AGE, $OXML_BINARY_AGE, [oxml binary age])

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
PKG_CHECK_MODULES(QT, [QtCore >= 4.0.1 QtXml >= 4.0.1])
AC_LANG_POP(C++)


AC_OUTPUT

