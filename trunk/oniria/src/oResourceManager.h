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
#ifndef __ORESOURCEMANAGER_H
#define __ORESOURCEMANAGER_H

#include <string>
#include <list>
#include <onir/oResources.h>
#include <onir/rc/rcPack.h>
#include <onir/oEventHandler.h>

class gApp;

using onirRC::rcPack;
using onir::oResources;


/*!\class oResourceManager
 * \brief Resource manager.
 */
class oResourceManager : public oResources {
	public:
		/*!\name Constructors and destructor
		 */
		//@{

		/*!\fn oResourceManager(gApp * app)
		 * \param all gApp pointer.
		 */
		oResourceManager(gApp * app);

		/*!\fn virtual ~oResourceManager()
		 * \brief Destructor.
		 */
		virtual ~oResourceManager();
		//@}

		/*!\fn int LoadResources()
		 * \brief Loads resource packs.
		 * \return Number of packs loaded.
		 */
		int LoadResources();

		/*!\fn void RegisterEventHandlers()
		 * \brief Registers resources event handlers. Mainly from oniria:resource namespace.
		 */
		void RegisterEventHandlers();

		/*!\fn virtual bool ProcessEvent(oEvent * event)
		 * \brief Handles event.
		 * \param event Event.
		 * \return true if event manager should call next handler in chain.
		 */
		virtual bool ProcessEvent(oEvent * event);

		/*!\fn virtual rcResource * Resource(const string& id, const string& type)
		 * \brief Finds resource with given id and type.
		 * \param id Resource id.
		 * \param type Resource type.
		 * \return Resource pointer or null if resource is not found.
		 */
		rcResource * Resource(const string& id, const string& type);

		/*!\fn virtual wxImage * Image(const string& id, const string& imageset = "")
		 * \brief Finds image.
		 * \param id Image id.
		 * \param imageset Imageset name.
		 * \return Pointer to image or null if resource is not found.
		 * \sa Resource(),
		 *
		 * If imageset is an empty string, id should be full resource id, otherwise
		 * id is relative to imageset resource id.
		 */
		virtual wxImage * Image(const string& id, const string& imageset = "");

		/*!\fn virtual rcSkin * Skin(const string& id)
		 * \brief Returns pointer to skin with given id.
		 * \param id Skin id.
		 * \return Skin pointer.
		 */
		virtual rcSkin * Skin(const string& id);

		/*!\fn virtual rcSkin * Skin()
		 * \brief Returns pointer to active skin.
		 * \param id Skin id.
		 * \return Skin pointer.
		 */
		virtual rcSkin * Skin();

	protected:
		
		bool ResourceAdded(oEvent * event);

	private:
	
		gApp * _app;
		rcPack * _root;
		map<string, string> _imagesets;
		map<string, string> _skins;
		
		DECLARE_OOBJECT;
};

#endif
