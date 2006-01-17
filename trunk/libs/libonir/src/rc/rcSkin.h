/* $Id: rcSkin.h 608 2005-10-07 09:57:23Z choman $ */
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
#ifndef __RCSKIN_H
#define __RCSKIN_H

#include "../dll.h"
#include "rcFileResource.h"

using namespace std;
class wxFont;

namespace onirRC {

class LIBONIR_API rcSkin : public rcFileResource {
	public:

		/*!\name Constructors and destructor
		 * @{
		 */

		/*!\fn rcSkin(oOniria * o)
		 * \brief Constructor.
		 * \param o oOniria pointer.
		 */
		rcSkin(oOniria * o);

		/*!\fn virtual ~rcSkin()
		 * \brief Destructor.
		 */
		virtual ~rcSkin();
		/* @} */


		
		/*!\fn virtual bool Prepare(const string& file, rcPack * owner, xmlElement * xml)
		 * \brief Preloads resource.
		 * \param file Name of resource file.
		 * \param owner Owner of resource.
		 * \param xml Resource XML description.
		 * \return true if ok
		 */
		virtual bool Prepare(const string& file, rcPack * owner, xmlElement * xml);
		
		
		
		/*!\name Skin attribute methods.
		 * @{
		 */
		
		virtual xmlElement * XMLValue(const string& id);
		virtual xmlElement * XMLValue(xmlElement * parent, const string& pid, const string& id);
		virtual string StringValue(const string& id, const string&  def = "");
		virtual wxColour ColourValue(const string& id, const wxColour&  def = wxColour("BLACK"));
		virtual int IntValue(const string& id, int def = 0);
		virtual unsigned int UIntValue(const string& id, unsigned int def = 0);
		virtual bool BoolValue(const string& id, bool def = false);
		virtual void SetupFont(wxFont * font, const string& id);

		/* @} */
		
	protected:
		void PrepareElement(const string& file, xmlElement * el);

	private:
		xmlElement * _skin_xml;

		DECLARE_OOBJECT;
};

};

#endif

