#!/bin/sh
# $Id$

if test "$*"; then
  ARGS="$*"
else
  test -f config.log && ARGS=`grep '^  \$ \./configure ' config.log | sed 's/^  \$ \.\/configure //' 2> /dev/null`
fi

echo "Running aclocal $AUTOGEN_ACLOCAL_FLAGS ..."
aclocal -I ../tools/aclocal $AUTOGEN_ACLOCAL_FLAGS

echo "Running autoheader..."
autoheader

echo "Running automake..."
automake --foreign --add-missing --copy

echo "Running autoconf..."
autoconf

test x$NOCONFIGURE = x && echo "Running ./configure $ARGS" && ./configure $ARGS

