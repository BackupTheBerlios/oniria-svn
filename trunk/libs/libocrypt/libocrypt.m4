# Configure paths for libocrypt
# A hacked up version of Owen Taylor's gtk.m4 (Copyright 1997)
# $Id$

# Owen Taylor     97-11-3

dnl AM_PATH_LIBOCRYPT([MINIMUM-VERSION, [ACTION-IF-FOUND [, ACTION-IF-NOT-FOUND [, MODULES]]]])
dnl Test for LIBOCRYPT, and define LIBOCRYPT_CFLAGS and LIBOCRYPT_LIBS
dnl
AC_DEFUN([AM_PATH_LIBOCRYPT],
[dnl 
dnl Get the cflags and libraries from the libocrypt-config script
dnl
AC_ARG_WITH(libocrypt-prefix,[  --with-libocrypt-prefix=PFX   Prefix where libocrypt is installed (optional)],
            libocrypt_config_prefix="$withval", libocrypt_config_prefix="")
AC_ARG_WITH(libocrypt-exec-prefix,[  --with-libocrypt-exec-prefix=PFX Exec prefix where libocrypt is installed (optional)],
            libocrypt_config_exec_prefix="$withval", libocrypt_config_exec_prefix="")
AC_ARG_ENABLE(libocrypttest, [  --disable-libocrypttest       Do not try to compile and run a test libocrypt program],
		    , enable_libocrypttest=yes)

  if test x$libocrypt_config_exec_prefix != x ; then
     libocrypt_config_args="$libocrypt_config_args --exec-prefix=$libocrypt_config_exec_prefix"
     if test x${LIBOCRYPT_CONFIG+set} != xset ; then
        LIBOCRYPT_CONFIG=$libocrypt_config_exec_prefix/bin/libocrypt-config
     fi
  fi
  if test x$libocrypt_config_prefix != x ; then
     libocrypt_config_args="$libocrypt_config_args --prefix=$libocrypt_config_prefix"
     if test x${LIBOCRYPT_CONFIG+set} != xset ; then
        LIBOCRYPT_CONFIG=$libocrypt_config_prefix/bin/libocrypt-config
     fi
  fi

  AC_PATH_PROG(LIBOCRYPT_CONFIG, libocrypt-config, no)
  min_libocrypt_version=ifelse([$1], ,0.1.0,$1)
  AC_MSG_CHECKING(for libocrypt - version >= $min_libocrypt_version)
  no_libocrypt=""
  if test "$LIBOCRYPT_CONFIG" = "no" ; then
    no_libocrypt=yes
  else
    LIBOCRYPT_CFLAGS=`$LIBOCRYPT_CONFIG $libocrypt_config_args --cflags`
    LIBOCRYPT_CXXFLAGS=`$LIBOCRYPT_CONFIG $libocrypt_config_args --cxxflags`
    LIBOCRYPT_LIBS=`$LIBOCRYPT_CONFIG $libocrypt_config_args --libs`
    libocrypt_config_major_version=`$LIBOCRYPT_CONFIG $libocrypt_config_args --version | \
           sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\1/'`
    libocrypt_config_minor_version=`$LIBOCRYPT_CONFIG $libocrypt_config_args --version | \
           sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\2/'`
    libocrypt_config_micro_version=`$LIBOCRYPT_CONFIG $libocrypt_config_args --version | \
           sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\3/'`
    if test "x$enable_libocrypttest" = "xyes" ; then
      ac_save_CFLAGS="$CFLAGS"
      ac_save_CXXFLAGS="$CXXFLAGS"
      ac_save_LIBS="$LIBS"
      CFLAGS="$CFLAGS $LIBOCRYPT_CFLAGS"
      CXXFLAGS="$CXXFLAGS $LIBOCRYPT_CXXFLAGS"
      LIBS="$LIBOCRYPT_LIBS $LIBS"
dnl
dnl Now check if the installed libocrypt is sufficiently new. (Also sanity
dnl checks the results of libocrypt-config to some extent
dnl
      rm -f conf.libocrypttest
      AC_LANG_PUSH(C++)
      AC_RUN_IFELSE([
#include <ocrypt/ocrypt.h>
#include <cstdio>
#include <cstring>
#include <stdlib.h>

int 
main ()
{
  int major, minor, micro;
  char *tmp_version;

  system ("touch conf.libocrypttest");

  /* HP/UX 9 (%@#!) writes to sscanf strings */
  tmp_version = strdup("$min_libocrypt_version");
  if (sscanf(tmp_version, "%d.%d.%d", &major, &minor, &micro) != 3) {
     printf("%s, bad version string\n", "$min_libocrypt_version");
     exit(1);
   }

  if ((libocrypt_major_version != $libocrypt_config_major_version) ||
      (libocrypt_minor_version != $libocrypt_config_minor_version) ||
      (libocrypt_micro_version != $libocrypt_config_micro_version))
    {
      printf("\n*** 'libocrypt-config --version' returned %d.%d.%d, but libocrypt (%d.%d.%d)\n", 
             $libocrypt_config_major_version, $libocrypt_config_minor_version, $libocrypt_config_micro_version,
             libocrypt_major_version, libocrypt_minor_version, libocrypt_micro_version);
      printf ("*** was found! If libocrypt-config was correct, then it is best\n");
      printf ("*** to remove the old version of libocrypt. You may also be able to fix the error\n");
      printf("*** by modifying your LD_LIBRARY_PATH enviroment variable, or by editing\n");
      printf("*** /etc/ld.so.conf. Make sure you have run ldconfig if that is\n");
      printf("*** required on your system.\n");
      printf("*** If libocrypt-config was wrong, set the environment variable LIBOCRYPT_CONFIG\n");
      printf("*** to point to the correct copy of libocrypt-config, and remove the file config.cache\n");
      printf("*** before re-running configure\n");
    } 
#if defined (LIBOCRYPT_MAJOR_VERSION) && defined (LIBOCRYPT_MINOR_VERSION) && defined (LIBOCRYPT_MICRO_VERSION)
  else if ((libocrypt_major_version != LIBOCRYPT_MAJOR_VERSION) ||
	   (libocrypt_minor_version != LIBOCRYPT_MINOR_VERSION) ||
           (libocrypt_micro_version != LIBOCRYPT_MICRO_VERSION))
    {
      printf("*** libocrypt header files (version %d.%d.%d) do not match\n",
	     LIBOCRYPT_MAJOR_VERSION, LIBOCRYPT_MINOR_VERSION, LIBOCRYPT_MICRO_VERSION);
      printf("*** library (version %d.%d.%d)\n",
	     libocrypt_major_version, libocrypt_minor_version, libocrypt_micro_version);
    }
#endif /* defined (LIBOCRYPT_MAJOR_VERSION) ... */
  else
    {
      if ((libocrypt_major_version > major) ||
        ((libocrypt_major_version == major) && (libocrypt_minor_version > minor)) ||
        ((libocrypt_major_version == major) && (libocrypt_minor_version == minor) && (libocrypt_micro_version >= micro)))
      {
        return 0;
       }
     else
      {
        printf("\n*** An old version of libocrypt (%d.%d.%d) was found.\n",
               libocrypt_major_version, libocrypt_minor_version, libocrypt_micro_version);
        printf("*** You need a version of libocrypt newer than %d.%d.%d. The latest version of\n",
	       major, minor, micro);
        printf("*** libocrypt is always available from http://www.libocryptlibrary.org.\n");
        printf("***\n");
        printf("*** If you have already installed a sufficiently new version, this error\n");
        printf("*** probably means that the wrong copy of the libocrypt-config shell script is\n");
        printf("*** being found. The easiest way to fix this is to remove the old version\n");
        printf("*** of libocrypt, but you can also set the LIBOCRYPT_CONFIG environment to point to the\n");
        printf("*** correct copy of libocrypt-config. (In this case, you will have to\n");
        printf("*** modify your LD_LIBRARY_PATH enviroment variable, or edit /etc/ld.so.conf\n");
        printf("*** so that the correct libraries are found at run-time))\n");
      }
    }
  return 1;
}
],, no_libocrypt=yes,[echo $ac_n "cross compiling; assumed OK... $ac_c"])
       AC_LANG_POP
       CFLAGS="$ac_save_CFLAGS"
       CXXFLAGS="$ac_save_CXXFLAGS"
       LIBS="$ac_save_LIBS"
     fi
  fi
  if test "x$no_libocrypt" = x ; then
     AC_MSG_RESULT(yes)
     ifelse([$2], , :, [$2])     
  else
     AC_MSG_RESULT(no)
     if test "$LIBOCRYPT_CONFIG" = "no" ; then
       echo "*** The libocrypt-config script installed by libocrypt could not be found"
       echo "*** If libocrypt was installed in PREFIX, make sure PREFIX/bin is in"
       echo "*** your path, or set the LIBOCRYPT_CONFIG environment variable to the"
       echo "*** full path to libocrypt-config."
     else
       if test -f conf.libocrypttest ; then
        :
       else
          echo "*** Could not run libocrypt test program, checking why..."
          CFLAGS="$CFLAGS $LIBOCRYPT_CFLAGS"
          CXXFLAGS="$CXXFLAGS $LIBOCRYPT_CFLAGS"
          LIBS="$LIBS $LIBOCRYPT_LIBS"
          AC_LANG_PUSH(C++)
          AC_LINK_IFELSE([
#include <ocrypt/ocrypt.h>
#include <stdio.h>
int main() {
return ((libocrypt_major_version) || (libocrypt_minor_version) || (libocrypt_micro_version)); 
}
],
        [ echo "*** The test program compiled, but did not run. This usually means"
          echo "*** that the run-time linker is not finding libocrypt or finding the wrong"
          echo "*** version of libocrypt. If it is not finding libocrypt, you'll need to set your"
          echo "*** LD_LIBRARY_PATH environment variable, or edit /etc/ld.so.conf to point"
          echo "*** to the installed location  Also, make sure you have run ldconfig if that"
          echo "*** is required on your system"
	  echo "***"
          echo "*** If you have an old version installed, it is best to remove it, although"
          echo "*** you may also be able to get things to work by modifying LD_LIBRARY_PATH"
          echo "***"
          echo "*** If you have a RedHat 5.0 system, you should remove the libocrypt package that"
          echo "*** came with the system with the command"
          echo "***"
          echo "***    rpm --erase --nodeps libocrypt libocrypt-devel" ],
        [ echo "*** The test program failed to compile or link. See the file config.log for the"
          echo "*** exact error that occured. This usually means libocrypt was incorrectly installed"
          echo "*** or that you have moved libocrypt since it was installed. In the latter case, you"
          echo "*** may want to edit the libocrypt-config script: $LIBOCRYPT_CONFIG" ])
          AC_LANG_POP
          CFLAGS="$ac_save_CFLAGS"
          LIBS="$ac_save_LIBS"
       fi
     fi
     LIBOCRYPT_CFLAGS=""
     LIBOCRYPT_CXXFLAGS=""
     LIBOCRYPT_LIBS=""
     ifelse([$3], , :, [$3])
  fi
  AC_SUBST(LIBOCRYPT_CFLAGS)
  AC_SUBST(LIBOCRYPT_CXXFLAGS)
  AC_SUBST(LIBOCRYPT_LIBS)
  rm -f conf.libocrypttest
])

