# $Id$

ogurincludedir = $(includedir)/oniria/ogur

#SUBDIRS = tests

EXTRA_DIST = ogur_config.h.in

lib_LTLIBRARIES = libogur.la

libogur_la_CPPFLAGS = -Wall @QT_CFLAGS@ -DBUILDING_LIBOGUR_DLL
libogur_la_LDFLAGS = -version-info $(LT_CURRENT):$(LT_REVISION):$(LT_AGE) \
		       -release $(LT_RELEASE) @LIBTOOL_EXTRA_LDFLAGS@ \
		       @QT_LIBS@



libogur_la_HEADERS_moc = gAction.h				\
			 gCore.h				\
			 gItemCanvas.h				\
			 gItemCol.h				\
			 gItemLine.h				\
			 gTreeList.h				\
			 gTreeListItem.h			\
			 gTreeListItemMoveAction.h

nobase_ogurinclude_HEADERS = ogur.h				\
			     ogur_dll.h				\
			     $(libogur_la_HEADERS_moc)

libogur_la_SOURCES = ogur.cc					\
		     gAction.cc					\
		     gCore.cc					\
		     gItemCanvas.cc				\
		     gItemCol.cc				\
		     gItemLine.cc				\
		     gTreeList.cc				\
		     gTreeListItem.cc				\
		     gTreeListItemMoveAction.cc			\
		     $(libogur_la_HEADERS_moc:.h=.moc.cc)

CLEANFILES = *.moc.cc

ogurinclude_DATA = ogur_config.h

%.moc.cc: %.h
	$(QTMOC) $< -o $@


