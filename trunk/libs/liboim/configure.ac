dnl Process this file with autoconf to produce a configure script.
dnl $Id$

AC_PREREQ([2.52])

AC_INIT([liboim], [0.1.0], [choman@foto-koszalin.pl])
AC_CONFIG_AUX_DIR(scripts)
AC_CANONICAL_BUILD
AC_CANONICAL_HOST
AC_CANONICAL_TARGET
AM_INIT_AUTOMAKE(AC_PACKAGE_NAME, AC_PACKAGE_VERSION)
AM_MAINTAINER_MODE

AC_REVISION([$Revision$])
AC_CONFIG_SRCDIR([src/im.cc])

AC_CONFIG_HEADERS(config.h)
AC_CONFIG_FILES([liboim-config
		 Makefile
		 scripts/Makefile 
		 src/Makefile
		 src/oim_config.h
		 liboim.pc
		 doxygen.cfg
		],
		[chmod -f +x liboim-config])

OIM_MAJOR_VERSION=0
OIM_MINOR_VERSION=1
OIM_MICRO_VERSION=0
OIM_INTERFACE_AGE=0
OIM_BINARY_AGE=0
OIM_VERSION=$OIM_MAJOR_VERSION.$OIM_MINOR_VERSION.$OIM_MICRO_VERSION

AC_SUBST(OIM_MAJOR_VERSION)
AC_SUBST(OIM_MINOR_VERSION)
AC_SUBST(OIM_MICRO_VERSION)
AC_SUBST(OIM_VERSION)
AC_SUBST(OIM_INTERFACE_AGE)
AC_SUBST(OIM_BINARY_AGE)

# libtool versioning
LT_RELEASE=$OIM_MAJOR_VERSION.$OIM_MINOR_VERSION
LT_CURRENT=`expr $OIM_MICRO_VERSION - $OIM_INTERFACE_AGE`
LT_REVISION=$OIM_INTERFACE_AGE
LT_AGE=`expr $OIM_BINARY_AGE - $OIM_INTERFACE_AGE`
AC_SUBST(LT_RELEASE)
AC_SUBST(LT_CURRENT)
AC_SUBST(LT_REVISION)
AC_SUBST(LT_AGE)
# Define version stuff
AC_DEFINE_UNQUOTED(OIM_MAJOR_VERSION, $OIM_MAJOR_VERSION, [oim major version])
AC_DEFINE_UNQUOTED(OIM_MINOR_VERSION, $OIM_MINOR_VERSION, [oim minor version])
AC_DEFINE_UNQUOTED(OIM_MICRO_VERSION, $OIM_MICRO_VERSION, [oim micro version])
AC_DEFINE_UNQUOTED(OIM_INTERFACE_AGE, $OIM_INTERFACE_AGE, [oim interface age])
AC_DEFINE_UNQUOTED(OIM_BINARY_AGE, $OIM_BINARY_AGE, [oim binary age])

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
PKG_CHECK_MODULES(OXML, [liboxml >= 0.1.0])
AC_LANG_POP(C++)


AC_OUTPUT

