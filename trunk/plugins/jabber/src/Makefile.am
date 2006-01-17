# $Id: Makefile.am 470 2005-08-26 11:51:21Z choman $

SUBDIRS = win32

localedir = @ONIRIA_PLUGINLOCALEDIR@
plugindir = @ONIRIA_PLUGINDIR@


plugin_LTLIBRARIES = libjabber.la
libjabber_la_CPPFLAGS = -Wall @LIBONIR_CFLAGS@
libjabber_la_LDFLAGS = @LTLIBINTL@ @LIBONIR_LIBS@

INCLUDES = -DLOCALEDIR=\"$(localedir)\"

libjabber_la_SOURCES = jabber.cpp		\
		       jPlugin.cpp		\
		       jPlugin.h		\
		       jProtocol.cpp		\
		       jProtocol.h		\
		       jSession.cpp		\
		       jSession.h		\
		       jJid.cpp			\
		       jJid.h			\
		       jRosterItem.cpp		\
		       jRosterItem.h		\
		       jRosterSubItem.cpp	\
		       jRosterSubItem.h

