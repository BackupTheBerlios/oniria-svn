/* $Id$ */
/*
 * Copyright (C) 2005-2006 Michal Wysoczanski <choman@foto-koszalin.pl>
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
#ifndef __OONIRIA_H
#define __OONIRIA_H

#include "onir_dll.h"

#include <QString>

namespace onirIM {
	class imProtocol;
};
using onirIM::imProtocol;

namespace onir {

class oConfig;
class oTabs;
class oResources;
class oEventQueue;

/*!\class oOniria
 * \brief Interface between Oniria and plugins.
 *
 * This is abstract class, implemented by oOniriaImpl. Plugins use this class
 * to communicate with Oniria.
 */
class LIBONIR_API oOniria {

	public:
		/*!\name Contructors and destructor
		 * @{
		 */

		/*!\fn oOniria()
		 * \brief Constructor
		 */
		oOniria();

		/*!\fn virtual ~oOniria()
		 * \brief Destructor.
		 */
		virtual ~oOniria();
		/* @} */

		/*!\name Registration
		 * @{
		 */

		/*!\fn virtual bool registerProtocol(imProtocol * hnd) = 0
		 * \brief Register new IM protocol
		 * \param hnd Pointer to protocol object.
		 * \return true if new protocol is registered, false otherwise
		 * \sa onirIM::imProtocol
		 *
		 * Plugins should call this method to register new protocol.
		 * ID of registered protocol is obtained by calling
		 * onirIM::imProtocol::protocolId(). Only one protocol with
		 * given id can be registered. Further attempts with this id will fail.
		 */
		virtual bool registerProtocol(imProtocol * hnd) = 0;
		/* @} */



		/*!\name Infomational methods
		 * @{
		 */

		/*!\fn virtual const QString& programName() const = 0
		 * \brief Returns program name ("Oniria")
		 * \return Program name.
		 */
		virtual const QString& programName() const = 0;

		/*!\fn virtual const QString& programVersion() const = 0
		 * \brief Returns program version.
		 * \return Program version.
		 */
		virtual const QString& programVersion() const = 0;

		/*!\fn virtual const QString& programString() const = 0
		 * \brief Returns string with program name and program version (for example "Oniria 0.1.0")
		 * \return Program name and version.
		 */
		virtual const QString& programString() const = 0;

		/*!\fn virtual const QString& OSDescription() const = 0
		 * \brief Returns OS description (for example "Windows XP", "Linux 2.4.20 i686")
		 * \return OS description.
		 */
		virtual const QString& OSDescription() const = 0;

		/* @} */



		/*!\name Subsystems accessors
		 * @{
		 */

		/*!\fn virtual oConfig * config() const  = 0
		 * \brief Returns pointer to oConfig object.
		 * \return Pointer to oConfig object.
		 * \sa oConfig
		 */
		virtual oConfig * config() const  = 0;

		/*!\fn virtual oConfig * log() const = 0
		 * \brief Returns pointer to log.
		 * \return Pointer to log
		 */
		//virtual wxLog * log() const = 0;

		/*!\fn virtual oTabs * tabs() const = 0
		 * \brief Returns pointer to oTabs.
		 * \return Pointer to oTabs
		 * \sa oTabs
		 */
		virtual oTabs * tabs() const = 0;

		/*!\fn virtual oResources * resources() const = 0
		 * \brief Returns pointer to resource manager interface.
		 * \return Pointer to oResources.
		 * \sa oResources
		 */
		virtual oResources * resources() const = 0;

		/*!\fn virtual oEventQueue * eventQueue() const = 0
		 */
		virtual oEventQueue * eventQueue() const = 0;
		/* @} */
};



};

#endif
