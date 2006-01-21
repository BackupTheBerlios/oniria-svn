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
#ifndef _SASLSASL_H
#define _SASLSASL_H

#include <QString>
#include <QMap>
#include <QList>
#include <QObject>
#include <stdint.h>
#include "dll.h"

namespace onirSASL {

class saslMechanism;
class saslCallback;

/*!\class saslSASL
 * \brief Main SASL class.
 */
class LIBOSASL_API saslSASL : public QObject {

	Q_OBJECT

	public:
		/*!\name Constructors and destructor.
		 */
		//@{

		/*!\fn saslSASL()
		 * \brief Constructor.
		 */
		saslSASL();

		/*!\fn virtual ~saslSASL()
		 * \brief Destructor.
		 */
		virtual ~saslSASL();
		//@}



		/*!\name Mechanisms methods.
		 */
		//@{

		/*!\fn bool addMechanism(saslMechanism * mech)
		 * \brief Adds mechanism to the list of supported mechanisms.
		 * \param mech Mechanism to add.
		 * \return true if ok.
		 * \sa saslMechanism
		 */
		bool addMechanism(saslMechanism * mech);

		/*!\fn void callback(saslCallback * cb)
		 * \brief Installs new callback.
		 * \param cb Callback to install.
		 */
		void callback(saslCallback * cb);

		/*!\fn saslMechanism * findMechanism(const QString& name) const
		 * \brief Finds mechanism with given name.
		 * \param name Mechanism name.
		 * \return Pointer to mechanism or NULL if not found.
		 * \sa saslMechanism
		 */
		saslMechanism * findMechanism(const QString& name) const;

		/*!\fn saslMechanism * chooseMechanism(const QList<QString>& mechs)
		 * \brief Finds first supported mechanism from the given list.
		 * \param mechs List of searched mechanisms. This is possibly list
		 * of mechanisms supported by the server.
		 * \return Mechanism pointer or NULL if none of given mechanisms are
		 * supported.
		 * \sa findMechanism(), nextMechanism(), mechanism(), saslMechanism
		 *
		 * This method updates currently selected mechanism (mechanism returned
		 * by mechanism() method).
		 */
		saslMechanism * chooseMechanism(const QList<QString>& mechs);

		/*!\fn saslMechanism * nextMechanism()
		 * \brief Finds next supported mechanism from the list provided
		 * by ChooseMechanism()
		 * \return Mechanism pointer or NULL if no more supported mechanism
		 * are found.
		 * \sa findMechanism(), chooseMechanism(), mechanism(), saslMechanism
		 *
		 * This method updates currently selected mechanism (mechanism returned
		 * by mechanism() method).
		 */
		saslMechanism * nextMechanism();

		/*!\fn inline saslMechanism * mechanism() const
		 * \brief Returns currently selected mechanism.
		 * \return Currently selected mechanism.
		 */
		inline saslMechanism * mechanism() const { return _mechanism; };
		//@}

	private:

		QMap<QString, saslMechanism *> _mechs;
		QList<QString> _allowed_mechs;
		QList<QString>::iterator _i_mechanism;
		saslMechanism * _mechanism;
		saslCallback * _callback;
};

};

#endif
