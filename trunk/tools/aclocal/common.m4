# $Id$
# Common autoconf macros for autotools based build system


dnl Detect for additional flags which should be passed to libtool when linking
dnl shared libraries. At the moment it only checks if we are under win32 
dnl system, and adds -no-undefined. Defines LIBTOOL_EXTRA_LDFLAGS.
AC_DEFUN([AC_LIBTOOL_EXTRA_LDFLAGS],
[
  AC_MSG_CHECKING([whether extra linker flags are needed])
  LIBTOOL_EXTRA_LDFLAGS=""
  case $host_os in
  cygwin* | mingw* | pw32* | os2*)
    LIBTOOL_EXTRA_LDFLAGS="-no-undefined"
    ;;
  esac
  AC_SUBST(LIBTOOL_EXTRA_LDFLAGS)
  if test "x$LIBTOOL_EXTRA_LDFLAGS" = "x";
  then
    AC_MSG_RESULT([no])
  else
    AC_MSG_RESULT($LIBTOOL_EXTRA_LDFLAGS)
  fi
])

AC_DEFUN([AC_PROG_MOC],
[
  AC_ARG_WITH(moc, [AC_HELP_STRING([--with-moc=path], [use given path for moc program])], [AC_SUBST(QTMOC), $withval], [AC_PATH_PROG(QTMOC, moc)])
])
 
