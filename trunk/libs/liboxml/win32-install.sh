#!/bin/sh
# $Id: win32-install.sh 636 2006-01-03 14:04:42Z choman $

function install_header ()
{
        install -Dv ./src/$1 ../win32-build/libonir/include/onir/$1
}

function install_lib ()
{
        install -Dv ./$1 ../win32-build/libonir/lib/$1
}

install -Dv ./src/win32/onir_config.h ../win32-build/libonir/include/onir/onir_config.h

install_header onir.h
install_header dll.h
install_header plugin.h
install_header oObject.h
install_header oOniria.h
install_header oConfig.h
install_header oPlugin.h
install_header oTabs.h
install_header oResources.h
install_header oEvent.h
install_header oEventTarget.h
install_header oEventHandler.h
install_header oEventForwarder.h
install_header oEventQueue.h

install_header utils/uBuffer.h
install_header utils/uException.h
install_header utils/uListDirTraverser.h
install_header utils/dconv.h
install_header utils/uBase16.h
install_header utils/uBase64.h
install_header utils/uDraw.h

install_header xml/xmlAttribute.h
install_header xml/xmlElement.h
install_header xml/xmlStanza.h
install_header xml/xmlStream.h
install_header xml/xmlParser.h

install_header crypt/cptHash.h
install_header crypt/cptMD5.h
install_header crypt/cptHMAC.h

install_header sasl/saslSASL.h
install_header sasl/saslMechanism.h
install_header sasl/saslCallback.h

install_header io/ioException.h
install_header io/ioSocketStream.h
install_header io/ioStream.h

install_header im/imProtocol.h
install_header im/imSession.h
install_header im/imStatus.h
install_header im/imRoster.h
install_header im/imRosterEntry.h
install_header im/imRosterItem.h
install_header im/imRosterGroup.h
install_header im/imPeer.h
install_header im/imMessageQueue.h
install_header im/imMessageThread.h
install_header im/imMessageThreadUI.h
install_header im/imMessage.h

install_header rc/rcResource.h
install_header rc/rcPack.h
install_header rc/rcFileResource.h
install_header rc/rcImage.h
install_header rc/rcSkin.h

install_header gui/guiPopupWindow.h
install_header gui/guiButton.h
install_header gui/guiAnimate.h

install_header decoders/decoderBase.h
install_header decoders/decoderGIF.h

install_lib onir.dll
install_lib libonir.a
install -Dv ./onir.dll ../win32-build/oniria/onir.dll
install -Dv src/xrc/onir.xrc ../win32-build/oniria/data/onir.xrc

