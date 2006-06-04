# $Id$

SUBDIRS = src scripts

docs_DOCS = AUTHORS ChangeLog COPYING INSTALL NEWS README
docsdir = $(prefix)/share/doc/@PACKAGE@

EXTRA_DIST = libonir.m4 libonir.pro win32-install.sh doxygen.cfg libonir.pc
bin_SCRIPTS = libonir-config
BUILT_SOURCES = libonir-config
onir-config: libonir-config.in

m4datadir = $(datadir)/aclocal
m4data_DATA = libonir.m4

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = libonir.pc

gen-docs: doxygen.cfg
	doxygen doxygen.cfg

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
