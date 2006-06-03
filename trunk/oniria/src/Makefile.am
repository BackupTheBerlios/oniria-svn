# $Id$

datadir = @datadir@/@PACKAGE@


#SUBDIRS = win32 data

EXTRA_DIST = oniria_config.h.in

oniria_CPPFLAGS = -Wall @QT_CFLAGS@ @OGUR_CFLAGS@ -DPLUGINDIR=\"@PLUGINDIR@\" -DDATADIR=\"@datadir@/@PACKAGE@\"
oniria_LDFLAGS = @QT_LIBS@ @OGUR_LIBS@

bin_PROGRAMS = oniria

oniria_SOURCES = oniria.cc
		 
noinst_DATA = oniria_config.h
#data_DATA = xrc/oniria.xrc
