# $Id$

#SUBDIRS = win32

plugindir = @ONIRIA_PLUGINDIR@


plugin_LTLIBRARIES = libjabber.la
libjabber_la_CPPFLAGS = -Wall #@LIBONIR_CFLAGS@
libjabber_la_LDFLAGS = #@LTLIBINTL@ @LIBONIR_LIBS@

INCLUDES = -DLOCALEDIR=\"$(localedir)\"

libjabber_la_SOURCES = jabber.cc

