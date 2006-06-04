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
#ifndef __OPLUGIN_H
#define __OPLUGIN_H

#include <oxml/xmlElement.h>
#include "onir_dll.h"

using namespace std;

namespace onir {

class oOniria;

/*!\class oPlugin
 * \brief Base class for plugin classes
 *
 * All plugins should implement interface provided by this class.
 */
class LIBONIR_API oPlugin {

	public:
		/*!\name Constructor and destructor
		 */
		//@{
		/*!\fn oPlugin()
		 * \brief Constructor
		 */
		oPlugin();

		/*!\fn virtual ~oPlugin()
		 * \brief Destructor
		 */
		virtual ~oPlugin();
		//@}
		

		/**!\fn inline xmlElement * description() const;
		 * \brief Returns plugin XML description.
		 * \return Pointer to XML element containing plugin description.
		 */
		inline onirXML::xmlElement * description() const { return _description; };

		/*!\fn virtual bool create(oOniria * o) = 0
		 * \brief Method called by Oniria when plugins are loaded.
		 * \param o Pointer to oOniria interface. Plugin should store
		 * this pointer for further use.
		 * \return true if plugin initialization was successful, false
		 * otherwise.
		 *
		 * You should register your handlers, protocols, etc,, and perform
		 * plugin initialization in this method. When this method is called
		 * by Oniria, all main subsystems are already created, so you can
		 * use these through pointer passed as parameter.
		 * 
		 * \warning If your create() returns false, there should be no 
		 * handlers, protocols, etc. registered by your plugin.
		 * It's possible that if create() returns false, the plugin
		 * will be immediatelly unloaded.
		 */
		virtual bool create(oOniria * o) = 0;

	protected:
		onirXML::xmlElement * _description;
};



};

#endif
