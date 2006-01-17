# $Id: Makefile 628 2006-01-02 11:16:03Z choman $

datadir = @datadir@/@PACKAGE@

data_DATA = base1.pak
CLEANFILES = base1.pak

BASE1_XML =	resources.xml

BASE1_ICONS =	icons/roster/online.png \
		icons/roster/away.png \
		icons/roster/xa.png \
		icons/roster/dnd.png \
		icons/roster/na.png \
		icons/roster/inv.png \
		icons/roster/chat.png \
		icons/buttons/tab-close.png \
		icons/buttons/tab-close-disable.png \
		icons/buttons/tab-dock.png \
		icons/buttons/tab-dock-disable.png

BASE1_SKINS =	skins/default/default.xml \
		skins/default/roster.xml

base1.pak: $(BASE1_XML) $(BASE1_ICONS) $(BASE1_SKINS)
	$(ZIP) $@ $?

