#!/bin/sh
# $Id: win32-install.sh 445 2005-08-23 21:05:36Z morg $

install -Dv ./src/xrc/oniria.xrc ../win32-build/oniria/data/oniria.xrc
install -Dv ./src/win32/oniria.exe.Manifest ../win32-build/oniria/oniria.exe.Manifest

