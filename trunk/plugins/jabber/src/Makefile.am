# $Id$

#SUBDIRS = win32

plugindir = @ONIRIA_PLUGINDIR@


plugin_LTLIBRARIES = libjabber.la
libjabber_la_CPPFLAGS = -Wall @ONIR_CFLAGS@
libjabber_la_LDFLAGS = @ONIR_LIBS@

INCLUDES = -DLOCALEDIR=\"$(localedir)\"

libjabber_la_SOURCES = jabber.cc		\
		       jPlugin.cc		\
		       jPlugin.h

