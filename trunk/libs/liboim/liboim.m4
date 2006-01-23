# Configure paths for liboim
# A hacked up version of Owen Taylor's gtk.m4 (Copyright 1997)
# $Id$

# Owen Taylor     97-11-3

dnl AM_PATH_LIBOIM([MINIMUM-VERSION, [ACTION-IF-FOUND [, ACTION-IF-NOT-FOUND [, MODULES]]]])
dnl Test for LIBOIM, and define LIBOIM_CFLAGS and LIBOIM_LIBS
dnl
AC_DEFUN([AM_PATH_LIBOIM],
[dnl 
dnl Get the cflags and libraries from the liboim-config script
dnl
AC_ARG_WITH(liboim-prefix,[  --with-liboim-prefix=PFX   Prefix where liboim is installed (optional)],
            liboim_config_prefix="$withval", liboim_config_prefix="")
AC_ARG_WITH(liboim-exec-prefix,[  --with-liboim-exec-prefix=PFX Exec prefix where liboim is installed (optional)],
            liboim_config_exec_prefix="$withval", liboim_config_exec_prefix="")
AC_ARG_ENABLE(liboimtest, [  --disable-liboimtest       Do not try to compile and run a test liboim program],
		    , enable_liboimtest=yes)

  if test x$liboim_config_exec_prefix != x ; then
     liboim_config_args="$liboim_config_args --exec-prefix=$liboim_config_exec_prefix"
     if test x${LIBOIM_CONFIG+set} != xset ; then
        LIBOIM_CONFIG=$liboim_config_exec_prefix/bin/liboim-config
     fi
  fi
  if test x$liboim_config_prefix != x ; then
     liboim_config_args="$liboim_config_args --prefix=$liboim_config_prefix"
     if test x${LIBOIM_CONFIG+set} != xset ; then
        LIBOIM_CONFIG=$liboim_config_prefix/bin/liboim-config
     fi
  fi

  AC_PATH_PROG(LIBOIM_CONFIG, liboim-config, no)
  min_liboim_version=ifelse([$1], ,0.1.0,$1)
  AC_MSG_CHECKING(for liboim - version >= $min_liboim_version)
  no_liboim=""
  if test "$LIBOIM_CONFIG" = "no" ; then
    no_liboim=yes
  else
    LIBOIM_CFLAGS=`$LIBOIM_CONFIG $liboim_config_args --cflags`
    LIBOIM_CXXFLAGS=`$LIBOIM_CONFIG $liboim_config_args --cxxflags`
    LIBOIM_LIBS=`$LIBOIM_CONFIG $liboim_config_args --libs`
    liboim_config_major_version=`$LIBOIM_CONFIG $liboim_config_args --version | \
           sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\1/'`
    liboim_config_minor_version=`$LIBOIM_CONFIG $liboim_config_args --version | \
           sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\2/'`
    liboim_config_micro_version=`$LIBOIM_CONFIG $liboim_config_args --version | \
           sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\3/'`
    if test "x$enable_liboimtest" = "xyes" ; then
      ac_save_CFLAGS="$CFLAGS"
      ac_save_CXXFLAGS="$CXXFLAGS"
      ac_save_LIBS="$LIBS"
      CFLAGS="$CFLAGS $LIBOIM_CFLAGS"
      CXXFLAGS="$CXXFLAGS $LIBOIM_CXXFLAGS"
      LIBS="$LIBOIM_LIBS $LIBS"
dnl
dnl Now check if the installed liboim is sufficiently new. (Also sanity
dnl checks the results of liboim-config to some extent
dnl
      rm -f conf.liboimtest
      AC_LANG_PUSH(C++)
      AC_RUN_IFELSE([
#include <oim/oim.h>
#include <cstdio>
#include <cstring>
#include <stdlib.h>

int 
main ()
{
  int major, minor, micro;
  char *tmp_version;

  system ("touch conf.liboimtest");

  /* HP/UX 9 (%@#!) writes to sscanf strings */
  tmp_version = strdup("$min_liboim_version");
  if (sscanf(tmp_version, "%d.%d.%d", &major, &minor, &micro) != 3) {
     printf("%s, bad version string\n", "$min_liboim_version");
     exit(1);
   }

  if ((liboim_major_version != $liboim_config_major_version) ||
      (liboim_minor_version != $liboim_config_minor_version) ||
      (liboim_micro_version != $liboim_config_micro_version))
    {
      printf("\n*** 'liboim-config --version' returned %d.%d.%d, but liboim (%d.%d.%d)\n", 
             $liboim_config_major_version, $liboim_config_minor_version, $liboim_config_micro_version,
             liboim_major_version, liboim_minor_version, liboim_micro_version);
      printf ("*** was found! If liboim-config was correct, then it is best\n");
      printf ("*** to remove the old version of liboim. You may also be able to fix the error\n");
      printf("*** by modifying your LD_LIBRARY_PATH enviroment variable, or by editing\n");
      printf("*** /etc/ld.so.conf. Make sure you have run ldconfig if that is\n");
      printf("*** required on your system.\n");
      printf("*** If liboim-config was wrong, set the environment variable LIBOIM_CONFIG\n");
      printf("*** to point to the correct copy of liboim-config, and remove the file config.cache\n");
      printf("*** before re-running configure\n");
    } 
#if defined (LIBOIM_MAJOR_VERSION) && defined (LIBOIM_MINOR_VERSION) && defined (LIBOIM_MICRO_VERSION)
  else if ((liboim_major_version != LIBOIM_MAJOR_VERSION) ||
	   (liboim_minor_version != LIBOIM_MINOR_VERSION) ||
           (liboim_micro_version != LIBOIM_MICRO_VERSION))
    {
      printf("*** liboim header files (version %d.%d.%d) do not match\n",
	     LIBOIM_MAJOR_VERSION, LIBOIM_MINOR_VERSION, LIBOIM_MICRO_VERSION);
      printf("*** library (version %d.%d.%d)\n",
	     liboim_major_version, liboim_minor_version, liboim_micro_version);
    }
#endif /* defined (LIBOIM_MAJOR_VERSION) ... */
  else
    {
      if ((liboim_major_version > major) ||
        ((liboim_major_version == major) && (liboim_minor_version > minor)) ||
        ((liboim_major_version == major) && (liboim_minor_version == minor) && (liboim_micro_version >= micro)))
      {
        return 0;
       }
     else
      {
        printf("\n*** An old version of liboim (%d.%d.%d) was found.\n",
               liboim_major_version, liboim_minor_version, liboim_micro_version);
        printf("*** You need a version of liboim newer than %d.%d.%d. The latest version of\n",
	       major, minor, micro);
        printf("*** liboim is always available from http://www.liboimlibrary.org.\n");
        printf("***\n");
        printf("*** If you have already installed a sufficiently new version, this error\n");
        printf("*** probably means that the wrong copy of the liboim-config shell script is\n");
        printf("*** being found. The easiest way to fix this is to remove the old version\n");
        printf("*** of liboim, but you can also set the LIBOIM_CONFIG environment to point to the\n");
        printf("*** correct copy of liboim-config. (In this case, you will have to\n");
        printf("*** modify your LD_LIBRARY_PATH enviroment variable, or edit /etc/ld.so.conf\n");
        printf("*** so that the correct libraries are found at run-time))\n");
      }
    }
  return 1;
}
],, no_liboim=yes,[echo $ac_n "cross compiling; assumed OK... $ac_c"])
       AC_LANG_POP
       CFLAGS="$ac_save_CFLAGS"
       CXXFLAGS="$ac_save_CXXFLAGS"
       LIBS="$ac_save_LIBS"
     fi
  fi
  if test "x$no_liboim" = x ; then
     AC_MSG_RESULT(yes)
     ifelse([$2], , :, [$2])     
  else
     AC_MSG_RESULT(no)
     if test "$LIBOIM_CONFIG" = "no" ; then
       echo "*** The liboim-config script installed by liboim could not be found"
       echo "*** If liboim was installed in PREFIX, make sure PREFIX/bin is in"
       echo "*** your path, or set the LIBOIM_CONFIG environment variable to the"
       echo "*** full path to liboim-config."
     else
       if test -f conf.liboimtest ; then
        :
       else
          echo "*** Could not run liboim test program, checking why..."
          CFLAGS="$CFLAGS $LIBOIM_CFLAGS"
          CXXFLAGS="$CXXFLAGS $LIBOIM_CFLAGS"
          LIBS="$LIBS $LIBOIM_LIBS"
          AC_LANG_PUSH(C++)
          AC_LINK_IFELSE([
#include <oim/oim.h>
#include <stdio.h>
int main() {
return ((liboim_major_version) || (liboim_minor_version) || (liboim_micro_version)); 
}
],
        [ echo "*** The test program compiled, but did not run. This usually means"
          echo "*** that the run-time linker is not finding liboim or finding the wrong"
          echo "*** version of liboim. If it is not finding liboim, you'll need to set your"
          echo "*** LD_LIBRARY_PATH environment variable, or edit /etc/ld.so.conf to point"
          echo "*** to the installed location  Also, make sure you have run ldconfig if that"
          echo "*** is required on your system"
	  echo "***"
          echo "*** If you have an old version installed, it is best to remove it, although"
          echo "*** you may also be able to get things to work by modifying LD_LIBRARY_PATH"
          echo "***"
          echo "*** If you have a RedHat 5.0 system, you should remove the liboim package that"
          echo "*** came with the system with the command"
          echo "***"
          echo "***    rpm --erase --nodeps liboim liboim-devel" ],
        [ echo "*** The test program failed to compile or link. See the file config.log for the"
          echo "*** exact error that occured. This usually means liboim was incorrectly installed"
          echo "*** or that you have moved liboim since it was installed. In the latter case, you"
          echo "*** may want to edit the liboim-config script: $LIBOIM_CONFIG" ])
          AC_LANG_POP
          CFLAGS="$ac_save_CFLAGS"
          LIBS="$ac_save_LIBS"
       fi
     fi
     LIBOIM_CFLAGS=""
     LIBOIM_CXXFLAGS=""
     LIBOIM_LIBS=""
     ifelse([$3], , :, [$3])
  fi
  AC_SUBST(LIBOIM_CFLAGS)
  AC_SUBST(LIBOIM_CXXFLAGS)
  AC_SUBST(LIBOIM_LIBS)
  rm -f conf.liboimtest
])

