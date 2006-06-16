# $Id$

#SUBDIRS = win32

plugindir = @ONIRIA_PLUGINDIR@


plugin_LTLIBRARIES = libjabber.la
libjabber_la_CPPFLAGS = -Wall @ONIR_CFLAGS@ @OXML_CFLAGS@ @OSASL_CFLAGS@ @OIM_CFLAGS@
libjabber_la_LDFLAGS = @ONIR_LIBS@ @OXML_LIBS@ @OSASL_LIBS@ @OIM_LIBS@

INCLUDES = -DLOCALEDIR=\"$(localedir)\"

libjabber_la_HEADERS_moc = jSession.h


libjabber_la_SOURCES = jabber.cc		\
		       jJid.cc			\
		       jJid.h			\
		       jRosterItem.cc		\
		       jRosterItem.h		\
		       jRosterSubItem.cc	\
		       jRosterSubItem.h		\
		       jRoster.cc		\
		       jRoster.h		\
		       jPlugin.cc		\
		       jPlugin.h		\
		       jProtocol.cc		\
		       jProtocol.h		\
		       jPeer.cc			\
		       jPeer.h			\
		       jMessageQueue.cc		\
		       jMessageQueue.h		\
		       jSession.cc		\
		       jSession.h		\
		       $(libjabber_la_HEADERS_moc:.h=.moc.cc)

CLEANFILES = *.moc.cc

%.moc.cc: %.h
	$(QTMOC) $< -o $@


