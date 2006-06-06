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
#ifndef _XMLSTANZA_H
#define _XMLSTANZA_H

#include "oxml_dll.h"
#include <QObject>

class QXmlAttributes;

namespace onirXML {

class xmlElement;

/*!\class xmlStanza
 * \brief Class representing XML stanza as defined in 
 * <a href="http://www.xmpp.org/specs/rfc3920.html#streams">RFC 3920</a>.
 * \sa xmlStream
 */
class LIBOXML_API xmlStanza : public QObject {

		Q_OBJECT

	public:

		/*!\name Constructors and destructor.
		 */
		//@{

		/*!\fn xmlStanza()
		 * \brief Constructor.
		 */
		xmlStanza();

		/*!\fn virtual ~xmlStanza()
		 * \brief Destructor.
		 */
		virtual ~xmlStanza();
		//@}


		/*!\fn inline xmlElement * element() const
		 * \brief Returns stanzas element.
		 * \return Stanzas element.
		 */
		inline xmlElement * element() const { return _element; };
		
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

		/*!\fn inline bool valid() const
		 * \brief Checks if stanza is valid.
		 * \return true if stanza is valid.
		 */
		inline bool valid() const { return _valid; };

		/*!\fn QString format(bool one_line = true, bool force_non_empty = false) const
		 * \brief Formats stanza into QString, that could be written into XML stream.
		 * \param one_line true if output should be unformated.
		 * \param force_non_empty If false, when element contains no content it will be formated as <element />
		 * \return Formated stanza.
		 */
		QString format(bool one_line = true, bool force_non_empty = false) const;

	protected:

		/*!\name Parse functions.
		 */
		//@{

		/*!\fn bool parseStartTag(const QString& el, const QXmlAttributes& attrs)
		 * \brief Parses openning tag.
		 * \param el Element.
		 * \param attrs Attributes.
		 * \return true if stream should enter or belong in stanza state.
		 */
		bool parseStartTag(const QString& el, const QXmlAttributes& attrs);
		
		/*!\fn bool parseEndTag(const QString& el)
		 * \brief Parses openning tag.
		 * \param el Element.
		 * \return true if stream should belong in stanza state.
		 */
		bool parseEndTag(const QString& el);

		/*!\fn void parseCharacterData(const QString& s)
		 * \brief Parse element data.
		 * \param s Element data.
		 *
		 * \attention This method may be called multiple times for the same element.
		 */
		void parseCharacterData(const QString& s);
		//@}

	private:
		xmlElement * _element;
		xmlElement * _active;

		int _level;
		bool _valid;
		QString _encoding;

		friend class xmlStream;
};

};

#endif
