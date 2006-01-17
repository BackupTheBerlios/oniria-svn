#!/bin/sh
# $Id$

function install_header ()
{
        install -Dv ./src/$1 ../win32-build/libogur/include/ogur/$1
}

function install_lib ()
{
        install -Dv ./$1 ../win32-build/libogur/lib/$1
}

install -Dv ./src/ogur_config.h ../win32-build/libogur/include/ogur/ogur_config.h

install_header TreeList.h
install_header TreeListItem.h

install_lib ogur*.dll
install_lib libogur*.a
install -Dv ./ogur*.dll ../win32-build/oniria/ogur.dll