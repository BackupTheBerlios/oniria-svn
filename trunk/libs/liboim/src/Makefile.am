# $Id$

oimincludedir = $(includedir)/oniria/oim

EXTRA_DIST = oim_config.h.in

lib_LTLIBRARIES = liboim.la

liboim_la_CPPFLAGS = -Wall @QT_CFLAGS@ @OXML_CFLAGS@ -DBUILDING_LIBOIM_DLL
liboim_la_LDFLAGS = -version-info $(LT_CURRENT):$(LT_REVISION):$(LT_AGE) \
		       -release $(LT_RELEASE) \
		       @QT_LIBS@ @OXML_LIBS@



liboim_la_HEADERS_moc = imMessage.h		\
			imMessageQueue.h	\
			imMessageThread.h	\
			imMessageThreadUI.h	\
			imPeer.h		\
			imProtocol.h		\
			imRosterEntry.h		\
			imRosterGroup.h		\
			imRoster.h		\
			imRosterItem.h		\
			imSession.h

nobase_oiminclude_HEADERS = oim.h		\
			    oim_dll.h		\
			    imStatus.h		\
			    $(liboim_la_HEADERS_moc)

liboim_la_SOURCES = im.cc			\
		    imMessage.cc		\
		    imMessageQueue.cc		\
		    imMessageThread.cc		\
		    imMessageThreadUI.cc	\
		    imPeer.cc			\
		    imProtocol.cc		\
		    imRoster.cc			\
		    imRosterEntry.cc		\
		    imRosterGroup.cc		\
		    imRosterItem.cc		\
		    imSession.cc		\
		    imStatus.cc			\
		    $(liboim_la_HEADERS_moc:.h=.moc.cc)

CLEANFILES = *.moc.cc

oiminclude_DATA = oim_config.h

%.moc.cc: %.h
	$(QTMOC) $< -o $@

