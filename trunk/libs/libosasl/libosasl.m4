# Configure paths for libosasl
# A hacked up version of Owen Taylor's gtk.m4 (Copyright 1997)
# $Id$

# Owen Taylor     97-11-3

dnl AM_PATH_LIBOSASL([MINIMUM-VERSION, [ACTION-IF-FOUND [, ACTION-IF-NOT-FOUND [, MODULES]]]])
dnl Test for LIBOSASL, and define LIBOSASL_CFLAGS and LIBOSASL_LIBS
dnl
AC_DEFUN([AM_PATH_LIBOSASL],
[dnl 
dnl Get the cflags and libraries from the libosasl-config script
dnl
AC_ARG_WITH(libosasl-prefix,[  --with-libosasl-prefix=PFX   Prefix where libosasl is installed (optional)],
            libosasl_config_prefix="$withval", libosasl_config_prefix="")
AC_ARG_WITH(libosasl-exec-prefix,[  --with-libosasl-exec-prefix=PFX Exec prefix where libosasl is installed (optional)],
            libosasl_config_exec_prefix="$withval", libosasl_config_exec_prefix="")
AC_ARG_ENABLE(libosasltest, [  --disable-libosasltest       Do not try to compile and run a test libosasl program],
		    , enable_libosasltest=yes)

  if test x$libosasl_config_exec_prefix != x ; then
     libosasl_config_args="$libosasl_config_args --exec-prefix=$libosasl_config_exec_prefix"
     if test x${LIBOSASL_CONFIG+set} != xset ; then
        LIBOSASL_CONFIG=$libosasl_config_exec_prefix/bin/libosasl-config
     fi
  fi
  if test x$libosasl_config_prefix != x ; then
     libosasl_config_args="$libosasl_config_args --prefix=$libosasl_config_prefix"
     if test x${LIBOSASL_CONFIG+set} != xset ; then
        LIBOSASL_CONFIG=$libosasl_config_prefix/bin/libosasl-config
     fi
  fi

  AC_PATH_PROG(LIBOSASL_CONFIG, libosasl-config, no)
  min_libosasl_version=ifelse([$1], ,0.1.0,$1)
  AC_MSG_CHECKING(for libosasl - version >= $min_libosasl_version)
  no_libosasl=""
  if test "$LIBOSASL_CONFIG" = "no" ; then
    no_libosasl=yes
  else
    LIBOSASL_CFLAGS=`$LIBOSASL_CONFIG $libosasl_config_args --cflags`
    LIBOSASL_CXXFLAGS=`$LIBOSASL_CONFIG $libosasl_config_args --cxxflags`
    LIBOSASL_LIBS=`$LIBOSASL_CONFIG $libosasl_config_args --libs`
    libosasl_config_major_version=`$LIBOSASL_CONFIG $libosasl_config_args --version | \
           sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\1/'`
    libosasl_config_minor_version=`$LIBOSASL_CONFIG $libosasl_config_args --version | \
           sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\2/'`
    libosasl_config_micro_version=`$LIBOSASL_CONFIG $libosasl_config_args --version | \
           sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\3/'`
    if test "x$enable_libosasltest" = "xyes" ; then
      ac_save_CFLAGS="$CFLAGS"
      ac_save_CXXFLAGS="$CXXFLAGS"
      ac_save_LIBS="$LIBS"
      CFLAGS="$CFLAGS $LIBOSASL_CFLAGS"
      CXXFLAGS="$CXXFLAGS $LIBOSASL_CXXFLAGS"
      LIBS="$LIBOSASL_LIBS $LIBS"
dnl
dnl Now check if the installed libosasl is sufficiently new. (Also sanity
dnl checks the results of libosasl-config to some extent
dnl
      rm -f conf.libosasltest
      AC_LANG_PUSH(C++)
      AC_RUN_IFELSE([
#include <osasl/osasl.h>
#include <cstdio>
#include <cstring>
#include <stdlib.h>

int 
main ()
{
  int major, minor, micro;
  char *tmp_version;

  system ("touch conf.libosasltest");

  /* HP/UX 9 (%@#!) writes to sscanf strings */
  tmp_version = strdup("$min_libosasl_version");
  if (sscanf(tmp_version, "%d.%d.%d", &major, &minor, &micro) != 3) {
     printf("%s, bad version string\n", "$min_libosasl_version");
     exit(1);
   }

  if ((libosasl_major_version != $libosasl_config_major_version) ||
      (libosasl_minor_version != $libosasl_config_minor_version) ||
      (libosasl_micro_version != $libosasl_config_micro_version))
    {
      printf("\n*** 'libosasl-config --version' returned %d.%d.%d, but libosasl (%d.%d.%d)\n", 
             $libosasl_config_major_version, $libosasl_config_minor_version, $libosasl_config_micro_version,
             libosasl_major_version, libosasl_minor_version, libosasl_micro_version);
      printf ("*** was found! If libosasl-config was correct, then it is best\n");
      printf ("*** to remove the old version of libosasl. You may also be able to fix the error\n");
      printf("*** by modifying your LD_LIBRARY_PATH enviroment variable, or by editing\n");
      printf("*** /etc/ld.so.conf. Make sure you have run ldconfig if that is\n");
      printf("*** required on your system.\n");
      printf("*** If libosasl-config was wrong, set the environment variable LIBOSASL_CONFIG\n");
      printf("*** to point to the correct copy of libosasl-config, and remove the file config.cache\n");
      printf("*** before re-running configure\n");
    } 
#if defined (LIBOSASL_MAJOR_VERSION) && defined (LIBOSASL_MINOR_VERSION) && defined (LIBOSASL_MICRO_VERSION)
  else if ((libosasl_major_version != LIBOSASL_MAJOR_VERSION) ||
	   (libosasl_minor_version != LIBOSASL_MINOR_VERSION) ||
           (libosasl_micro_version != LIBOSASL_MICRO_VERSION))
    {
      printf("*** libosasl header files (version %d.%d.%d) do not match\n",
	     LIBOSASL_MAJOR_VERSION, LIBOSASL_MINOR_VERSION, LIBOSASL_MICRO_VERSION);
      printf("*** library (version %d.%d.%d)\n",
	     libosasl_major_version, libosasl_minor_version, libosasl_micro_version);
    }
#endif /* defined (LIBOSASL_MAJOR_VERSION) ... */
  else
    {
      if ((libosasl_major_version > major) ||
        ((libosasl_major_version == major) && (libosasl_minor_version > minor)) ||
        ((libosasl_major_version == major) && (libosasl_minor_version == minor) && (libosasl_micro_version >= micro)))
      {
        return 0;
       }
     else
      {
        printf("\n*** An old version of libosasl (%d.%d.%d) was found.\n",
               libosasl_major_version, libosasl_minor_version, libosasl_micro_version);
        printf("*** You need a version of libosasl newer than %d.%d.%d. The latest version of\n",
	       major, minor, micro);
        printf("*** libosasl is always available from http://www.libosasllibrary.org.\n");
        printf("***\n");
        printf("*** If you have already installed a sufficiently new version, this error\n");
        printf("*** probably means that the wrong copy of the libosasl-config shell script is\n");
        printf("*** being found. The easiest way to fix this is to remove the old version\n");
        printf("*** of libosasl, but you can also set the LIBOSASL_CONFIG environment to point to the\n");
        printf("*** correct copy of libosasl-config. (In this case, you will have to\n");
        printf("*** modify your LD_LIBRARY_PATH enviroment variable, or edit /etc/ld.so.conf\n");
        printf("*** so that the correct libraries are found at run-time))\n");
      }
    }
  return 1;
}
],, no_libosasl=yes,[echo $ac_n "cross compiling; assumed OK... $ac_c"])
       AC_LANG_POP
       CFLAGS="$ac_save_CFLAGS"
       CXXFLAGS="$ac_save_CXXFLAGS"
       LIBS="$ac_save_LIBS"
     fi
  fi
  if test "x$no_libosasl" = x ; then
     AC_MSG_RESULT(yes)
     ifelse([$2], , :, [$2])     
  else
     AC_MSG_RESULT(no)
     if test "$LIBOSASL_CONFIG" = "no" ; then
       echo "*** The libosasl-config script installed by libosasl could not be found"
       echo "*** If libosasl was installed in PREFIX, make sure PREFIX/bin is in"
       echo "*** your path, or set the LIBOSASL_CONFIG environment variable to the"
       echo "*** full path to libosasl-config."
     else
       if test -f conf.libosasltest ; then
        :
       else
          echo "*** Could not run libosasl test program, checking why..."
          CFLAGS="$CFLAGS $LIBOSASL_CFLAGS"
          CXXFLAGS="$CXXFLAGS $LIBOSASL_CFLAGS"
          LIBS="$LIBS $LIBOSASL_LIBS"
          AC_LANG_PUSH(C++)
          AC_LINK_IFELSE([
#include <osasl/osasl.h>
#include <stdio.h>
int main() {
return ((libosasl_major_version) || (libosasl_minor_version) || (libosasl_micro_version)); 
}
],
        [ echo "*** The test program compiled, but did not run. This usually means"
          echo "*** that the run-time linker is not finding libosasl or finding the wrong"
          echo "*** version of libosasl. If it is not finding libosasl, you'll need to set your"
          echo "*** LD_LIBRARY_PATH environment variable, or edit /etc/ld.so.conf to point"
          echo "*** to the installed location  Also, make sure you have run ldconfig if that"
          echo "*** is required on your system"
	  echo "***"
          echo "*** If you have an old version installed, it is best to remove it, although"
          echo "*** you may also be able to get things to work by modifying LD_LIBRARY_PATH"
          echo "***"
          echo "*** If you have a RedHat 5.0 system, you should remove the libosasl package that"
          echo "*** came with the system with the command"
          echo "***"
          echo "***    rpm --erase --nodeps libosasl libosasl-devel" ],
        [ echo "*** The test program failed to compile or link. See the file config.log for the"
          echo "*** exact error that occured. This usually means libosasl was incorrectly installed"
          echo "*** or that you have moved libosasl since it was installed. In the latter case, you"
          echo "*** may want to edit the libosasl-config script: $LIBOSASL_CONFIG" ])
          AC_LANG_POP
          CFLAGS="$ac_save_CFLAGS"
          LIBS="$ac_save_LIBS"
       fi
     fi
     LIBOSASL_CFLAGS=""
     LIBOSASL_CXXFLAGS=""
     LIBOSASL_LIBS=""
     ifelse([$3], , :, [$3])
  fi
  AC_SUBST(LIBOSASL_CFLAGS)
  AC_SUBST(LIBOSASL_CXXFLAGS)
  AC_SUBST(LIBOSASL_LIBS)
  rm -f conf.libosasltest
])

