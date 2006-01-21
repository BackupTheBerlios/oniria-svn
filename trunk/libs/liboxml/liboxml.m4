# Configure paths for liboxml
# A hacked up version of Owen Taylor's gtk.m4 (Copyright 1997)
# $Id$

# Owen Taylor     97-11-3

dnl AM_PATH_LIBOXML([MINIMUM-VERSION, [ACTION-IF-FOUND [, ACTION-IF-NOT-FOUND [, MODULES]]]])
dnl Test for LIBOXML, and define LIBOXML_CFLAGS and LIBOXML_LIBS
dnl
AC_DEFUN([AM_PATH_LIBOXML],
[dnl 
dnl Get the cflags and libraries from the liboxml-config script
dnl
AC_ARG_WITH(liboxml-prefix,[  --with-liboxml-prefix=PFX   Prefix where liboxml is installed (optional)],
            liboxml_config_prefix="$withval", liboxml_config_prefix="")
AC_ARG_WITH(liboxml-exec-prefix,[  --with-liboxml-exec-prefix=PFX Exec prefix where liboxml is installed (optional)],
            liboxml_config_exec_prefix="$withval", liboxml_config_exec_prefix="")
AC_ARG_ENABLE(liboxmltest, [  --disable-liboxmltest       Do not try to compile and run a test liboxml program],
		    , enable_liboxmltest=yes)

  if test x$liboxml_config_exec_prefix != x ; then
     liboxml_config_args="$liboxml_config_args --exec-prefix=$liboxml_config_exec_prefix"
     if test x${LIBOXML_CONFIG+set} != xset ; then
        LIBOXML_CONFIG=$liboxml_config_exec_prefix/bin/liboxml-config
     fi
  fi
  if test x$liboxml_config_prefix != x ; then
     liboxml_config_args="$liboxml_config_args --prefix=$liboxml_config_prefix"
     if test x${LIBOXML_CONFIG+set} != xset ; then
        LIBOXML_CONFIG=$liboxml_config_prefix/bin/liboxml-config
     fi
  fi

  AC_PATH_PROG(LIBOXML_CONFIG, liboxml-config, no)
  min_liboxml_version=ifelse([$1], ,0.1.0,$1)
  AC_MSG_CHECKING(for liboxml - version >= $min_liboxml_version)
  no_liboxml=""
  if test "$LIBOXML_CONFIG" = "no" ; then
    no_liboxml=yes
  else
    LIBOXML_CFLAGS=`$LIBOXML_CONFIG $liboxml_config_args --cflags`
    LIBOXML_CXXFLAGS=`$LIBOXML_CONFIG $liboxml_config_args --cxxflags`
    LIBOXML_LIBS=`$LIBOXML_CONFIG $liboxml_config_args --libs`
    liboxml_config_major_version=`$LIBOXML_CONFIG $liboxml_config_args --version | \
           sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\1/'`
    liboxml_config_minor_version=`$LIBOXML_CONFIG $liboxml_config_args --version | \
           sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\2/'`
    liboxml_config_micro_version=`$LIBOXML_CONFIG $liboxml_config_args --version | \
           sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\3/'`
    if test "x$enable_liboxmltest" = "xyes" ; then
      ac_save_CFLAGS="$CFLAGS"
      ac_save_CXXFLAGS="$CXXFLAGS"
      ac_save_LIBS="$LIBS"
      CFLAGS="$CFLAGS $LIBOXML_CFLAGS"
      CXXFLAGS="$CXXFLAGS $LIBOXML_CXXFLAGS"
      LIBS="$LIBOXML_LIBS $LIBS"
dnl
dnl Now check if the installed liboxml is sufficiently new. (Also sanity
dnl checks the results of liboxml-config to some extent
dnl
      rm -f conf.liboxmltest
      AC_LANG_PUSH(C++)
      AC_RUN_IFELSE([
#include <oxml/oxml.h>
#include <cstdio>
#include <cstring>
#include <stdlib.h>

int 
main ()
{
  int major, minor, micro;
  char *tmp_version;

  system ("touch conf.liboxmltest");

  /* HP/UX 9 (%@#!) writes to sscanf strings */
  tmp_version = strdup("$min_liboxml_version");
  if (sscanf(tmp_version, "%d.%d.%d", &major, &minor, &micro) != 3) {
     printf("%s, bad version string\n", "$min_liboxml_version");
     exit(1);
   }

  if ((liboxml_major_version != $liboxml_config_major_version) ||
      (liboxml_minor_version != $liboxml_config_minor_version) ||
      (liboxml_micro_version != $liboxml_config_micro_version))
    {
      printf("\n*** 'liboxml-config --version' returned %d.%d.%d, but liboxml (%d.%d.%d)\n", 
             $liboxml_config_major_version, $liboxml_config_minor_version, $liboxml_config_micro_version,
             liboxml_major_version, liboxml_minor_version, liboxml_micro_version);
      printf ("*** was found! If liboxml-config was correct, then it is best\n");
      printf ("*** to remove the old version of liboxml. You may also be able to fix the error\n");
      printf("*** by modifying your LD_LIBRARY_PATH enviroment variable, or by editing\n");
      printf("*** /etc/ld.so.conf. Make sure you have run ldconfig if that is\n");
      printf("*** required on your system.\n");
      printf("*** If liboxml-config was wrong, set the environment variable LIBOXML_CONFIG\n");
      printf("*** to point to the correct copy of liboxml-config, and remove the file config.cache\n");
      printf("*** before re-running configure\n");
    } 
#if defined (LIBOXML_MAJOR_VERSION) && defined (LIBOXML_MINOR_VERSION) && defined (LIBOXML_MICRO_VERSION)
  else if ((liboxml_major_version != LIBOXML_MAJOR_VERSION) ||
	   (liboxml_minor_version != LIBOXML_MINOR_VERSION) ||
           (liboxml_micro_version != LIBOXML_MICRO_VERSION))
    {
      printf("*** liboxml header files (version %d.%d.%d) do not match\n",
	     LIBOXML_MAJOR_VERSION, LIBOXML_MINOR_VERSION, LIBOXML_MICRO_VERSION);
      printf("*** library (version %d.%d.%d)\n",
	     liboxml_major_version, liboxml_minor_version, liboxml_micro_version);
    }
#endif /* defined (LIBOXML_MAJOR_VERSION) ... */
  else
    {
      if ((liboxml_major_version > major) ||
        ((liboxml_major_version == major) && (liboxml_minor_version > minor)) ||
        ((liboxml_major_version == major) && (liboxml_minor_version == minor) && (liboxml_micro_version >= micro)))
      {
        return 0;
       }
     else
      {
        printf("\n*** An old version of liboxml (%d.%d.%d) was found.\n",
               liboxml_major_version, liboxml_minor_version, liboxml_micro_version);
        printf("*** You need a version of liboxml newer than %d.%d.%d. The latest version of\n",
	       major, minor, micro);
        printf("*** liboxml is always available from http://www.liboxmllibrary.org.\n");
        printf("***\n");
        printf("*** If you have already installed a sufficiently new version, this error\n");
        printf("*** probably means that the wrong copy of the liboxml-config shell script is\n");
        printf("*** being found. The easiest way to fix this is to remove the old version\n");
        printf("*** of liboxml, but you can also set the LIBOXML_CONFIG environment to point to the\n");
        printf("*** correct copy of liboxml-config. (In this case, you will have to\n");
        printf("*** modify your LD_LIBRARY_PATH enviroment variable, or edit /etc/ld.so.conf\n");
        printf("*** so that the correct libraries are found at run-time))\n");
      }
    }
  return 1;
}
],, no_liboxml=yes,[echo $ac_n "cross compiling; assumed OK... $ac_c"])
       AC_LANG_POP
       CFLAGS="$ac_save_CFLAGS"
       CXXFLAGS="$ac_save_CXXFLAGS"
       LIBS="$ac_save_LIBS"
     fi
  fi
  if test "x$no_liboxml" = x ; then
     AC_MSG_RESULT(yes)
     ifelse([$2], , :, [$2])     
  else
     AC_MSG_RESULT(no)
     if test "$LIBOXML_CONFIG" = "no" ; then
       echo "*** The liboxml-config script installed by liboxml could not be found"
       echo "*** If liboxml was installed in PREFIX, make sure PREFIX/bin is in"
       echo "*** your path, or set the LIBOXML_CONFIG environment variable to the"
       echo "*** full path to liboxml-config."
     else
       if test -f conf.liboxmltest ; then
        :
       else
          echo "*** Could not run liboxml test program, checking why..."
          CFLAGS="$CFLAGS $LIBOXML_CFLAGS"
          CXXFLAGS="$CXXFLAGS $LIBOXML_CFLAGS"
          LIBS="$LIBS $LIBOXML_LIBS"
          AC_LANG_PUSH(C++)
          AC_LINK_IFELSE([
#include <oxml/oxml.h>
#include <stdio.h>
int main() {
return ((liboxml_major_version) || (liboxml_minor_version) || (liboxml_micro_version)); 
}
],
        [ echo "*** The test program compiled, but did not run. This usually means"
          echo "*** that the run-time linker is not finding liboxml or finding the wrong"
          echo "*** version of liboxml. If it is not finding liboxml, you'll need to set your"
          echo "*** LD_LIBRARY_PATH environment variable, or edit /etc/ld.so.conf to point"
          echo "*** to the installed location  Also, make sure you have run ldconfig if that"
          echo "*** is required on your system"
	  echo "***"
          echo "*** If you have an old version installed, it is best to remove it, although"
          echo "*** you may also be able to get things to work by modifying LD_LIBRARY_PATH"
          echo "***"
          echo "*** If you have a RedHat 5.0 system, you should remove the liboxml package that"
          echo "*** came with the system with the command"
          echo "***"
          echo "***    rpm --erase --nodeps liboxml liboxml-devel" ],
        [ echo "*** The test program failed to compile or link. See the file config.log for the"
          echo "*** exact error that occured. This usually means liboxml was incorrectly installed"
          echo "*** or that you have moved liboxml since it was installed. In the latter case, you"
          echo "*** may want to edit the liboxml-config script: $LIBOXML_CONFIG" ])
          AC_LANG_POP
          CFLAGS="$ac_save_CFLAGS"
          LIBS="$ac_save_LIBS"
       fi
     fi
     LIBOXML_CFLAGS=""
     LIBOXML_CXXFLAGS=""
     LIBOXML_LIBS=""
     ifelse([$3], , :, [$3])
  fi
  AC_SUBST(LIBOXML_CFLAGS)
  AC_SUBST(LIBOXML_CXXFLAGS)
  AC_SUBST(LIBOXML_LIBS)
  rm -f conf.liboxmltest
])

