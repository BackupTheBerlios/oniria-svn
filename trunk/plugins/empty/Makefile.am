# $Id$

SUBDIRS = src scripts

docs_DOCS = AUTHORS ChangeLog COPYING INSTALL NEWS README
docsdir = @ONIRIA_PLUGINDOCSDIR@/@PACKAGE@

EXTRA_DIST = scripts/config.rpath scripts/mkinstalldirs \
	     win32-install.sh 

install-docs:
	$(mkinstalldirs) $(docsdir)
	for doc in $(docs_DOCS); do \
		$(INSTALL_DATA) $$doc $(docsdir)/$$doc; \
		echo "installing $$doc as $(docsdir)/$$doc"; \
	done

uninstall-docs:
	for doc in $(docs_DOCS); do \
		rm -f $(docsdir)/$$doc; \
		echo "removing $(docsdir)/$$doc" ; \
	done

install-data-local: install-docs

uninstall-local: uninstall-docs


ACLOCAL_AMFLAGS = -I m4
