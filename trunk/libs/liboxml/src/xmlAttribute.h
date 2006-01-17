/* $Id: xmlAttribute.h 639 2006-01-03 14:22:18Z choman $ */
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
#ifndef _XMLATTRIBUTE_H
#define _XMLATTRIBUTE_H

#include <QObject>
#include <QString>
#include "dll.h"

namespace onirXML {

/*!\class xmlAttribute
 * \brief Class representing XML element attribute
 */
class LIBOXML_API xmlAttribute : public QObject {

		Q_OBJECT

	public:
		/*!\name Constructors and destructor.
		 */
		//@{

		/*!\fn xmlAttribute(const QString& name = "", const QString& value = "")
		 * \brief Constructor.
		 * \param name Name of attribute.
		 * \param value Attribute value.
		 */
		xmlAttribute(const QString& name = "", const QString& value = "");

		/*!\overload xmlAttribute(const QString& name, int value)
		 */
		xmlAttribute(const QString& name, int value);
		//@}


		/*!\fn bool valid() const
		 * \brief Checks attribute validity.
		 * \return true if attribute is valid.
		 */
		bool valid() const;

		/*!\fn inline void name(const QString& name)
		 * \brief Sets attribute name.
		 * \param name Attribute name.
		 */
		inline void name(const QString& name) { _name = name; };

		/*!\fn void value(const QString& value)
		 * \brief Sets attribute value.
		 * \param value Attribute value.
		 */
		void value(const QString& value);

		/*!\overload void value(int value)
		 */
		void value(int value);

		/*!\fn inline void order(int order)
		 * \brief Sets attribute order.
		 * \param order Attribute order.
		 */
		inline void order(int order) { _order = order; };

		/*!\fn inline const QString& name() const
		 * \brief Returns attribute name.
		 * \return Attribute name.
		 */
		inline const QString& name() const { return _name; };

		/*!\fn inline const QString& value() const
		 * \brief Returns attribute value.
		 * \return Attribute value.
		 */
		inline const QString& value() const { return _value; };

		/*!\fn inline int order() const
		 * \brief Returns attribute order.
		 * \return Attribute order.
		 */
		inline int order() const { return _order; };

		/*!\fn inline const QString& encoding() const
		 * \brief Returns XML encoding.
		 * \return Encoding.
		 */
		inline const QString& encoding() const { return _encoding; };

		/*!\fn inline void encoding(const QString& encoding)
		 * \brief Sets XML encoding.
		 * \param encoding Encoding.
		 */
		inline void encoding(const QString& encoding) { _encoding = encoding; };

		/*!\fn QString format() const
		 * \brief Formats attribute into QString, that could be written into XML stream.
		 * \return Formated attribute.
		 */
		QString format() const;

	private:
		QString _name;
		QString _value;
		int _order;
		QString _encoding;
};

};

#endif
