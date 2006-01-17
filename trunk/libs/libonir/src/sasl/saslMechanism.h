/* $Id$ */
/*
 * Copyright (C) 2005
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */
#ifndef _SASLMECHANISM_H
#define _SASLMECHANISM_H

#include <QString>
#include <QMap>
#include <QMultiMap>
#include <QList>
#include <QByteArray>
#include <stdint.h>
#include "../dll.h"
#include "../oObject.h"

using onir::oObject;

namespace onirSASL {

class saslCallback;

/*!\class saslMechanism
 * \brief Base class for SASL mechanisms.
 */
class LIBONIR_API saslMechanism : public oObject {

	public:

		/*!\enum mechanismState
		 * \brief Mechanism state.
		 */
		enum mechanismState {
			not_implemented,	/*!< Some part or whole mechanism is not implemented. */
			unknown,		/*!< Unknown state. Possibly mechanism is not initialized. */
			ready,			/*!< Mechanism is ready for authenticating. */
			auth,			/*!< Mechanism is authenticating. More challenges and/or responses are needed. */
			auth_ok,		/*!< Authentication ok. */
			auth_fail,		/*!< Authentication failed. */
			error			/*!< An error occured. */
		};


		/*!\name Constructors and destructor.
		 */
		//@{

		/*!\fn saslMechanism()
		 * \brief Constructor.
		 */
		saslMechanism();

		/*!\fn virtual ~saslMechanism()
		 * \brief Destructor.
		 */
		virtual ~saslMechanism();
		//@}



		/*!\fn inline const QString& name() const
		 * \brief Returns mechanism name.
		 * \return Mechanism name.
		 */
		inline const QString& name() const { return _mech_name; };

		/*!\fn inline mechanismState state() const
		 * \brief Returns mechanism current state.
		 * \return Mechanism state.
		 * \sa mechanismState
		 */
		inline mechanismState state() const { return _state; };

		/*!\fn inline void callback(saslCallback * cb)
		 * \brief Installs new callback.
		 * \param cb Callback to install.
		 *
		 * \attention Old callback will not be deleted. You should
		 * manually delete old one. This is opposite to 
		 * saslSASL::Callback(), which delete old callback before
		 * installing new one.
		 */
		inline void callback(saslCallback * cb) { _callback = cb; };

		/*!\fn inline saslCallback * callback() const
		 * \brief Returns callback.
		 * \return Callback.
		 */
		inline saslCallback * callback() const { return _callback; };

		/*!\name Properties methods.
		 */
		//@{

		/*!\fn void addProperty(const QString& name, QByteArray * val)
		 * \brief Adds property to the list of propertied.
		 * \param name Property name.
		 * \param val Property value.
		 *
		 * Properties names and values are dependent on mechanism
		 * being used.
		 */
		void addProperty(const QString& name, QByteArray * val);

		/*!\overload void addProperty(const QString& name, const QString& val)
		 */
		void addProperty(const QString& name, const QString& val);

		/*!\fn inline const QMultiMap<QString, QByteArray *> properties() const
		 * \brief Return all properties.
		 * \return Properties.
		 */
		inline const QMultiMap<QString, QByteArray *> properties() const { return _properties; };

		/*!\fn void properties(const QString& name, QList<QByteArray *>& props) const
		 * \brief Gets properties with given name only.
		 * \param name Property name.
		 * \param props List which will contain properties.
		 */
		void properties(const QString& name, QList<QByteArray *>& props) const;

		/*!\fn QByteArray * property(const QString& name, bool use_cb = true) const
		 * \brief Gets property value.
		 * \param name Property name.
		 * \param use_cb If true, installed callback will be used when property is not found.
		 * \return Property value.
		 */
		QByteArray * property(const QString& name, bool use_cb = true) const;
		//@}



		/*!\fn virtual bool response(QByteArray * challenge, QByteArray * response)
		 * \brief Main client method.
		 * \param challenge Challenge obtained from server.
		 * \param response Generated response to be send to server.
		 * \return true if ok.
		 */
		virtual bool response(QByteArray * challenge, QByteArray * response);
		
		/*!\fn virtual bool challenge(QByteArray * response, QByteArray * challenge)
		 * \brief Main server method.
		 * \param challenge Generated challenge to be send to client.
		 * \param response Response obtained from client.
		 * \return true if ok.
		 */
		virtual bool challenge(QByteArray * response, QByteArray * challenge);
		
	protected:

		/*!\fn void name(const QString& name)
		 * \brief Sets mechanism name.
		 * \param name Mechanism name.
		 *
		 * This method should be only called by derrived classes, possibly in costructor,
		 * before mechanism is added to saslSASL.
		 */
		void name(const QString& name) { _mech_name = name; };

		/*!\fn inline void state(mechanismState state)
		 * \brief Sets mechanism state.
		 * \param state New mechanism state.
		 * \sa Mechanism state.
		 */
		inline void state(mechanismState state) { _state = state; };

	private:
		mechanismState _state;
		saslCallback * _callback;

		QString _mech_name;
		QMultiMap<QString, QByteArray *> _properties;

		DECLARE_OOBJECT;
};

};

#endif
