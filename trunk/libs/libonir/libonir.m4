# Configure paths for libonir
# A hacked up version of Owen Taylor's gtk.m4 (Copyright 1997)
# $Id$

# Owen Taylor     97-11-3

dnl AM_PATH_LIBONIR([MINIMUM-VERSION, [ACTION-IF-FOUND [, ACTION-IF-NOT-FOUND [, MODULES]]]])
dnl Test for LIBONIR, and define LIBONIR_CFLAGS and LIBONIR_LIBS
dnl
AC_DEFUN([AM_PATH_LIBONIR],
[dnl 
dnl Get the cflags and libraries from the libonir-config script
dnl
AC_ARG_WITH(libonir-prefix,[  --with-libonir-prefix=PFX   Prefix where libonir is installed (optional)],
            libonir_config_prefix="$withval", libonir_config_prefix="")
AC_ARG_WITH(libonir-exec-prefix,[  --with-libonir-exec-prefix=PFX Exec prefix where libonir is installed (optional)],
            libonir_config_exec_prefix="$withval", libonir_config_exec_prefix="")
AC_ARG_ENABLE(libonirtest, [  --disable-libonirtest       Do not try to compile and run a test libonir program],
		    , enable_libonirtest=yes)

  if test x$libonir_config_exec_prefix != x ; then
     libonir_config_args="$libonir_config_args --exec-prefix=$libonir_config_exec_prefix"
     if test x${LIBONIR_CONFIG+set} != xset ; then
        LIBONIR_CONFIG=$libonir_config_exec_prefix/bin/libonir-config
     fi
  fi
  if test x$libonir_config_prefix != x ; then
     libonir_config_args="$libonir_config_args --prefix=$libonir_config_prefix"
     if test x${LIBONIR_CONFIG+set} != xset ; then
        LIBONIR_CONFIG=$libonir_config_prefix/bin/libonir-config
     fi
  fi

  AC_PATH_PROG(LIBONIR_CONFIG, libonir-config, no)
  min_libonir_version=ifelse([$1], ,0.1.0,$1)
  AC_MSG_CHECKING(for libonir - version >= $min_libonir_version)
  no_libonir=""
  if test "$LIBONIR_CONFIG" = "no" ; then
    no_libonir=yes
  else
    LIBONIR_CFLAGS=`$LIBONIR_CONFIG $libonir_config_args --cflags`
    LIBONIR_CXXFLAGS=`$LIBONIR_CONFIG $libonir_config_args --cxxflags`
    LIBONIR_LIBS=`$LIBONIR_CONFIG $libonir_config_args --libs`
    libonir_config_major_version=`$LIBONIR_CONFIG $libonir_config_args --version | \
           sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\1/'`
    libonir_config_minor_version=`$LIBONIR_CONFIG $libonir_config_args --version | \
           sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\2/'`
    libonir_config_micro_version=`$LIBONIR_CONFIG $libonir_config_args --version | \
           sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\3/'`
    if test "x$enable_libonirtest" = "xyes" ; then
      ac_save_CFLAGS="$CFLAGS"
      ac_save_CXXFLAGS="$CXXFLAGS"
      ac_save_LIBS="$LIBS"
      CFLAGS="$CFLAGS $LIBONIR_CFLAGS"
      CXXFLAGS="$CXXFLAGS $LIBONIR_CXXFLAGS"
      LIBS="$LIBONIR_LIBS $LIBS"
dnl
dnl Now check if the installed libonir is sufficiently new. (Also sanity
dnl checks the results of libonir-config to some extent
dnl
      rm -f conf.libonirtest
      AC_LANG_PUSH(C++)
      AC_RUN_IFELSE([
#include <onir/onir.h>
#include <cstdio>
#include <cstring>
#include <stdlib.h>

int 
main ()
{
  int major, minor, micro;
  char *tmp_version;

  system ("touch conf.libonirtest");

  /* HP/UX 9 (%@#!) writes to sscanf strings */
  tmp_version = strdup("$min_libonir_version");
  if (sscanf(tmp_version, "%d.%d.%d", &major, &minor, &micro) != 3) {
     printf("%s, bad version string\n", "$min_libonir_version");
     exit(1);
   }

  if ((libonir_major_version != $libonir_config_major_version) ||
      (libonir_minor_version != $libonir_config_minor_version) ||
      (libonir_micro_version != $libonir_config_micro_version))
    {
      printf("\n*** 'libonir-config --version' returned %d.%d.%d, but libonir (%d.%d.%d)\n", 
             $libonir_config_major_version, $libonir_config_minor_version, $libonir_config_micro_version,
             libonir_major_version, libonir_minor_version, libonir_micro_version);
      printf ("*** was found! If libonir-config was correct, then it is best\n");
      printf ("*** to remove the old version of libonir. You may also be able to fix the error\n");
      printf("*** by modifying your LD_LIBRARY_PATH enviroment variable, or by editing\n");
      printf("*** /etc/ld.so.conf. Make sure you have run ldconfig if that is\n");
      printf("*** required on your system.\n");
      printf("*** If libonir-config was wrong, set the environment variable LIBONIR_CONFIG\n");
      printf("*** to point to the correct copy of libonir-config, and remove the file config.cache\n");
      printf("*** before re-running configure\n");
    } 
#if defined (LIBONIR_MAJOR_VERSION) && defined (LIBONIR_MINOR_VERSION) && defined (LIBONIR_MICRO_VERSION)
  else if ((libonir_major_version != LIBONIR_MAJOR_VERSION) ||
	   (libonir_minor_version != LIBONIR_MINOR_VERSION) ||
           (libonir_micro_version != LIBONIR_MICRO_VERSION))
    {
      printf("*** libonir header files (version %d.%d.%d) do not match\n",
	     LIBONIR_MAJOR_VERSION, LIBONIR_MINOR_VERSION, LIBONIR_MICRO_VERSION);
      printf("*** library (version %d.%d.%d)\n",
	     libonir_major_version, libonir_minor_version, libonir_micro_version);
    }
#endif /* defined (LIBONIR_MAJOR_VERSION) ... */
  else
    {
      if ((libonir_major_version > major) ||
        ((libonir_major_version == major) && (libonir_minor_version > minor)) ||
        ((libonir_major_version == major) && (libonir_minor_version == minor) && (libonir_micro_version >= micro)))
      {
        return 0;
       }
     else
      {
        printf("\n*** An old version of libonir (%d.%d.%d) was found.\n",
               libonir_major_version, libonir_minor_version, libonir_micro_version);
        printf("*** You need a version of libonir newer than %d.%d.%d. The latest version of\n",
	       major, minor, micro);
        printf("*** libonir is always available from http://www.libonirlibrary.org.\n");
        printf("***\n");
        printf("*** If you have already installed a sufficiently new version, this error\n");
        printf("*** probably means that the wrong copy of the libonir-config shell script is\n");
        printf("*** being found. The easiest way to fix this is to remove the old version\n");
        printf("*** of libonir, but you can also set the LIBONIR_CONFIG environment to point to the\n");
        printf("*** correct copy of libonir-config. (In this case, you will have to\n");
        printf("*** modify your LD_LIBRARY_PATH enviroment variable, or edit /etc/ld.so.conf\n");
        printf("*** so that the correct libraries are found at run-time))\n");
      }
    }
  return 1;
}
],, no_libonir=yes,[echo $ac_n "cross compiling; assumed OK... $ac_c"])
       AC_LANG_POP
       CFLAGS="$ac_save_CFLAGS"
       CXXFLAGS="$ac_save_CXXFLAGS"
       LIBS="$ac_save_LIBS"
     fi
  fi
  if test "x$no_libonir" = x ; then
     AC_MSG_RESULT(yes)
     ifelse([$2], , :, [$2])     
  else
     AC_MSG_RESULT(no)
     if test "$LIBONIR_CONFIG" = "no" ; then
       echo "*** The libonir-config script installed by libonir could not be found"
       echo "*** If libonir was installed in PREFIX, make sure PREFIX/bin is in"
       echo "*** your path, or set the LIBONIR_CONFIG environment variable to the"
       echo "*** full path to libonir-config."
     else
       if test -f conf.libonirtest ; then
        :
       else
          echo "*** Could not run libonir test program, checking why..."
          CFLAGS="$CFLAGS $LIBONIR_CFLAGS"
          CXXFLAGS="$CXXFLAGS $LIBONIR_CFLAGS"
          LIBS="$LIBS $LIBONIR_LIBS"
          AC_LANG_PUSH(C++)
          AC_LINK_IFELSE([
#include <onir/onir.h>
#include <stdio.h>
int main() {
return ((libonir_major_version) || (libonir_minor_version) || (libonir_micro_version)); 
}
],
        [ echo "*** The test program compiled, but did not run. This usually means"
          echo "*** that the run-time linker is not finding libonir or finding the wrong"
          echo "*** version of libonir. If it is not finding libonir, you'll need to set your"
          echo "*** LD_LIBRARY_PATH environment variable, or edit /etc/ld.so.conf to point"
          echo "*** to the installed location  Also, make sure you have run ldconfig if that"
          echo "*** is required on your system"
	  echo "***"
          echo "*** If you have an old version installed, it is best to remove it, although"
          echo "*** you may also be able to get things to work by modifying LD_LIBRARY_PATH"
          echo "***"
          echo "*** If you have a RedHat 5.0 system, you should remove the libonir package that"
          echo "*** came with the system with the command"
          echo "***"
          echo "***    rpm --erase --nodeps libonir libonir-devel" ],
        [ echo "*** The test program failed to compile or link. See the file config.log for the"
          echo "*** exact error that occured. This usually means libonir was incorrectly installed"
          echo "*** or that you have moved libonir since it was installed. In the latter case, you"
          echo "*** may want to edit the libonir-config script: $LIBONIR_CONFIG" ])
          AC_LANG_POP
          CFLAGS="$ac_save_CFLAGS"
          LIBS="$ac_save_LIBS"
       fi
     fi
     LIBONIR_CFLAGS=""
     LIBONIR_CXXFLAGS=""
     LIBONIR_LIBS=""
     ifelse([$3], , :, [$3])
  fi
  AC_SUBST(LIBONIR_CFLAGS)
  AC_SUBST(LIBONIR_CXXFLAGS)
  AC_SUBST(LIBONIR_LIBS)
  rm -f conf.libonirtest
])

