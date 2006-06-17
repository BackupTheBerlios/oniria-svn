# $Id$

#SUBDIRS = win32

plugindir = @ONIRIA_PLUGINDIR@


plugin_LTLIBRARIES = libempty.la
libempty_la_CPPFLAGS = -Wall @ONIR_CFLAGS@ @OXML_CFLAGS@ 
libempty_la_LDFLAGS = @ONIR_LIBS@ @OXML_LIBS@

INCLUDES = -DLOCALEDIR=\"$(localedir)\"

libempty_la_HEADERS_moc =


libempty_la_SOURCES = empty.cc			\
		      ePlugin.cc		\
		      ePlugin.h			\
		      $(libempty_la_HEADERS_moc:.h=.moc.cc)

CLEANFILES = *.moc.cc

%.moc.cc: %.h
	$(QTMOC) $< -o $@


