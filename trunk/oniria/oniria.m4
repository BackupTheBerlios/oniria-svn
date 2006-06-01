# Configure paths for oniria
# A hacked up version of Owen Taylor's gtk.m4 (Copyright 1997)
# $Id$

# Owen Taylor     97-11-3

dnl AM_PATH_ONIRIA([MINIMUM-VERSION, [ACTION-IF-FOUND [, ACTION-IF-NOT-FOUND [, MODULES]]]])
dnl Test for ONIRIA, and define ONIRIA_CFLAGS and ONIRIA_LIBS
dnl
AC_DEFUN([AM_PATH_ONIRIA],
[dnl 
dnl Get the cflags and libraries from the oniria-config script
dnl
AC_ARG_WITH(oniria-prefix,[  --with-oniria-prefix=PFX   Prefix where oniria is installed (optional)],
            oniria_config_prefix="$withval", oniria_config_prefix="")
AC_ARG_WITH(oniria-exec-prefix,[  --with-oniria-exec-prefix=PFX Exec prefix where oniria is installed (optional)],
            oniria_config_exec_prefix="$withval", oniria_config_exec_prefix="")

  if test x$oniria_config_exec_prefix != x ; then
     oniria_config_args="$oniria_config_args --exec-prefix=$oniria_config_exec_prefix"
     if test x${ONIRIA_CONFIG+set} != xset ; then
        ONIRIA_CONFIG=$oniria_config_exec_prefix/bin/oniria-config
     fi
  fi
  if test x$oniria_config_prefix != x ; then
     oniria_config_args="$oniria_config_args --prefix=$oniria_config_prefix"
     if test x${ONIRIA_CONFIG+set} != xset ; then
        ONIRIA_CONFIG=$oniria_config_prefix/bin/oniria-config
     fi
  fi

  AC_PATH_PROG(ONIRIA_CONFIG, oniria-config, no)
  no_oniria=""
  if test "$ONIRIA_CONFIG" = "no" ; then
    no_oniria=yes
  else
    AC_MSG_CHECKING([where to install oniria plugins])
    ONIRIA_PLUGINDIR=`$ONIRIA_CONFIG $oniria_config_args --plugindir`
    AC_MSG_RESULT([$ONIRIA_PLUGINDIR])
    AC_MSG_CHECKING([where to install oniria plugins locales])
    ONIRIA_PLUGINLOCALEDIR=`$ONIRIA_CONFIG $oniria_config_args --pluginlocaledir`
    AC_MSG_RESULT([$ONIRIA_PLUGINLOCALEDIR])
    AC_MSG_CHECKING([where to install oniria plugins documentation])
    ONIRIA_PLUGINDOCSDIR=`$ONIRIA_CONFIG $oniria_config_args --plugindocsdir`
    AC_MSG_RESULT([$ONIRIA_PLUGINDOCSDIR])
  fi
  if test "x$no_oniria" = x ; then
     ifelse([$2], , :, [$2])
  else
     if test "$ONIRIA_CONFIG" = "no" ; then
       echo "*** The oniria-config script installed by oniria could not be found"
       echo "*** If oniria was installed in PREFIX, make sure PREFIX/bin is in"
       echo "*** your path, or set the ONIRIA_CONFIG environment variable to the"
       echo "*** full path to oniria-config."
     fi
     ifelse([$3], , :, [$3])
  fi
  AC_SUBST(ONIRIA_PLUGINDIR)
  AC_SUBST(ONIRIA_PLUGINLOCALEDIR)
  AC_SUBST(ONIRIA_PLUGINDOCSDIR)
])

