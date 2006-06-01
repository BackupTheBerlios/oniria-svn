# Configure paths for libogur
# A hacked up version of Owen Taylor's gtk.m4 (Copyright 1997)
# $Id$

# Owen Taylor     97-11-3

dnl AM_PATH_LIBOGUR([MINIMUM-VERSION, [ACTION-IF-FOUND [, ACTION-IF-NOT-FOUND [, MODULES]]]])
dnl Test for LIBOGUR, and define LIBOGUR_CFLAGS and LIBOGUR_LIBS
dnl
AC_DEFUN([AM_PATH_LIBOGUR],
[dnl 
dnl Get the cflags and libraries from the libogur-config script
dnl
AC_ARG_WITH(libogur-prefix,[  --with-libogur-prefix=PFX   Prefix where libogur is installed (optional)],
            libogur_config_prefix="$withval", libogur_config_prefix="")
AC_ARG_WITH(libogur-exec-prefix,[  --with-libogur-exec-prefix=PFX Exec prefix where libogur is installed (optional)],
            libogur_config_exec_prefix="$withval", libogur_config_exec_prefix="")
AC_ARG_ENABLE(libogurtest, [  --disable-libogurtest       Do not try to compile and run a test libogur program],
		    , enable_libogurtest=yes)

  if test x$libogur_config_exec_prefix != x ; then
     libogur_config_args="$libogur_config_args --exec-prefix=$libogur_config_exec_prefix"
     if test x${LIBOGUR_CONFIG+set} != xset ; then
        LIBOGUR_CONFIG=$libogur_config_exec_prefix/bin/libogur-config
     fi
  fi
  if test x$libogur_config_prefix != x ; then
     libogur_config_args="$libogur_config_args --prefix=$libogur_config_prefix"
     if test x${LIBOGUR_CONFIG+set} != xset ; then
        LIBOGUR_CONFIG=$libogur_config_prefix/bin/libogur-config
     fi
  fi

  AC_PATH_PROG(LIBOGUR_CONFIG, libogur-config, no)
  min_libogur_version=ifelse([$1], ,0.1.0,$1)
  AC_MSG_CHECKING(for libogur - version >= $min_libogur_version)
  no_libogur=""
  if test "$LIBOGUR_CONFIG" = "no" ; then
    no_libogur=yes
  else
    LIBOGUR_CFLAGS=`$LIBOGUR_CONFIG $libogur_config_args --cflags`
    LIBOGUR_CXXFLAGS=`$LIBOGUR_CONFIG $libogur_config_args --cxxflags`
    LIBOGUR_LIBS=`$LIBOGUR_CONFIG $libogur_config_args --libs`
    libogur_config_major_version=`$LIBOGUR_CONFIG $libogur_config_args --version | \
           sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\1/'`
    libogur_config_minor_version=`$LIBOGUR_CONFIG $libogur_config_args --version | \
           sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\2/'`
    libogur_config_micro_version=`$LIBOGUR_CONFIG $libogur_config_args --version | \
           sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\3/'`
    if test "x$enable_libogurtest" = "xyes" ; then
      ac_save_CFLAGS="$CFLAGS"
      ac_save_CXXFLAGS="$CXXFLAGS"
      ac_save_LIBS="$LIBS"
      CFLAGS="$CFLAGS $LIBOGUR_CFLAGS"
      CXXFLAGS="$CXXFLAGS $LIBOGUR_CXXFLAGS"
      LIBS="$LIBOGUR_LIBS $LIBS"
dnl
dnl Now check if the installed libogur is sufficiently new. (Also sanity
dnl checks the results of libogur-config to some extent
dnl
      rm -f conf.libogurtest
      AC_LANG_PUSH(C++)
      AC_RUN_IFELSE([
#include <ogur/ogur.h>
#include <cstdio>
#include <cstring>
#include <stdlib.h>

int 
main ()
{
  int major, minor, micro;
  char *tmp_version;

  system ("touch conf.libogurtest");

  /* HP/UX 9 (%@#!) writes to sscanf strings */
  tmp_version = strdup("$min_libogur_version");
  if (sscanf(tmp_version, "%d.%d.%d", &major, &minor, &micro) != 3) {
     printf("%s, bad version string\n", "$min_libogur_version");
     exit(1);
   }

  if ((libogur_major_version != $libogur_config_major_version) ||
      (libogur_minor_version != $libogur_config_minor_version) ||
      (libogur_micro_version != $libogur_config_micro_version))
    {
      printf("\n*** 'libogur-config --version' returned %d.%d.%d, but libogur (%d.%d.%d)\n", 
             $libogur_config_major_version, $libogur_config_minor_version, $libogur_config_micro_version,
             libogur_major_version, libogur_minor_version, libogur_micro_version);
      printf ("*** was found! If libogur-config was correct, then it is best\n");
      printf ("*** to remove the old version of libogur. You may also be able to fix the error\n");
      printf("*** by modifying your LD_LIBRARY_PATH enviroment variable, or by editing\n");
      printf("*** /etc/ld.so.conf. Make sure you have run ldconfig if that is\n");
      printf("*** required on your system.\n");
      printf("*** If libogur-config was wrong, set the environment variable LIBOGUR_CONFIG\n");
      printf("*** to point to the correct copy of libogur-config, and remove the file config.cache\n");
      printf("*** before re-running configure\n");
    } 
#if defined (LIBOGUR_MAJOR_VERSION) && defined (LIBOGUR_MINOR_VERSION) && defined (LIBOGUR_MICRO_VERSION)
  else if ((libogur_major_version != LIBOGUR_MAJOR_VERSION) ||
	   (libogur_minor_version != LIBOGUR_MINOR_VERSION) ||
           (libogur_micro_version != LIBOGUR_MICRO_VERSION))
    {
      printf("*** libogur header files (version %d.%d.%d) do not match\n",
	     LIBOGUR_MAJOR_VERSION, LIBOGUR_MINOR_VERSION, LIBOGUR_MICRO_VERSION);
      printf("*** library (version %d.%d.%d)\n",
	     libogur_major_version, libogur_minor_version, libogur_micro_version);
    }
#endif /* defined (LIBOGUR_MAJOR_VERSION) ... */
  else
    {
      if ((libogur_major_version > major) ||
        ((libogur_major_version == major) && (libogur_minor_version > minor)) ||
        ((libogur_major_version == major) && (libogur_minor_version == minor) && (libogur_micro_version >= micro)))
      {
        return 0;
       }
     else
      {
        printf("\n*** An old version of libogur (%d.%d.%d) was found.\n",
               libogur_major_version, libogur_minor_version, libogur_micro_version);
        printf("*** You need a version of libogur newer than %d.%d.%d. The latest version of\n",
	       major, minor, micro);
        printf("*** libogur is always available from http://www.libogurlibrary.org.\n");
        printf("***\n");
        printf("*** If you have already installed a sufficiently new version, this error\n");
        printf("*** probably means that the wrong copy of the libogur-config shell script is\n");
        printf("*** being found. The easiest way to fix this is to remove the old version\n");
        printf("*** of libogur, but you can also set the LIBOGUR_CONFIG environment to point to the\n");
        printf("*** correct copy of libogur-config. (In this case, you will have to\n");
        printf("*** modify your LD_LIBRARY_PATH enviroment variable, or edit /etc/ld.so.conf\n");
        printf("*** so that the correct libraries are found at run-time))\n");
      }
    }
  return 1;
}
],, no_libogur=yes,[echo $ac_n "cross compiling; assumed OK... $ac_c"])
       AC_LANG_POP
       CFLAGS="$ac_save_CFLAGS"
       CXXFLAGS="$ac_save_CXXFLAGS"
       LIBS="$ac_save_LIBS"
     fi
  fi
  if test "x$no_libogur" = x ; then
     AC_MSG_RESULT(yes)
     ifelse([$2], , :, [$2])     
  else
     AC_MSG_RESULT(no)
     if test "$LIBOGUR_CONFIG" = "no" ; then
       echo "*** The libogur-config script installed by libogur could not be found"
       echo "*** If libogur was installed in PREFIX, make sure PREFIX/bin is in"
       echo "*** your path, or set the LIBOGUR_CONFIG environment variable to the"
       echo "*** full path to libogur-config."
     else
       if test -f conf.libogurtest ; then
        :
       else
          echo "*** Could not run libogur test program, checking why..."
          CFLAGS="$CFLAGS $LIBOGUR_CFLAGS"
          CXXFLAGS="$CXXFLAGS $LIBOGUR_CFLAGS"
          LIBS="$LIBS $LIBOGUR_LIBS"
          AC_LANG_PUSH(C++)
          AC_LINK_IFELSE([
#include <ogur/ogur.h>
#include <stdio.h>
int main() {
return ((libogur_major_version) || (libogur_minor_version) || (libogur_micro_version)); 
}
],
        [ echo "*** The test program compiled, but did not run. This usually means"
          echo "*** that the run-time linker is not finding libogur or finding the wrong"
          echo "*** version of libogur. If it is not finding libogur, you'll need to set your"
          echo "*** LD_LIBRARY_PATH environment variable, or edit /etc/ld.so.conf to point"
          echo "*** to the installed location  Also, make sure you have run ldconfig if that"
          echo "*** is required on your system"
	  echo "***"
          echo "*** If you have an old version installed, it is best to remove it, although"
          echo "*** you may also be able to get things to work by modifying LD_LIBRARY_PATH"
          echo "***"
          echo "*** If you have a RedHat 5.0 system, you should remove the libogur package that"
          echo "*** came with the system with the command"
          echo "***"
          echo "***    rpm --erase --nodeps libogur libogur-devel" ],
        [ echo "*** The test program failed to compile or link. See the file config.log for the"
          echo "*** exact error that occured. This usually means libogur was incorrectly installed"
          echo "*** or that you have moved libogur since it was installed. In the latter case, you"
          echo "*** may want to edit the libogur-config script: $LIBOGUR_CONFIG" ])
          AC_LANG_POP
          CFLAGS="$ac_save_CFLAGS"
          LIBS="$ac_save_LIBS"
       fi
     fi
     LIBOGUR_CFLAGS=""
     LIBOGUR_CXXFLAGS=""
     LIBOGUR_LIBS=""
     ifelse([$3], , :, [$3])
  fi
  AC_SUBST(LIBOGUR_CFLAGS)
  AC_SUBST(LIBOGUR_CXXFLAGS)
  AC_SUBST(LIBOGUR_LIBS)
  rm -f conf.libogurtest
])

