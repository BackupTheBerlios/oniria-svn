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
#ifndef _XMLPARSER_H
#define _XMLPARSER_H

#include <QString>
#include <QByteArray>
#include <QObject>

#include "oxml_dll.h"

class QXmlAttributes;
class QIODevice;


namespace onirXML {

class xmlElement;
	
/*!\class xmlParser
 * \brief XML parser 
 */
class LIBOXML_API xmlParser : public QObject {

	Q_OBJECT

	public:

		/*!\enum parserState
		 * \brief XML parser state.
		 */
		enum parserState {
			unknown,	/*!< Unknown state. */
			ready,		/*!< Parser is ready for parsing. */
			parsing,	/*!< Parsing active. Possibly more data needed. */
			finished,	/*!< Parsing finished. */
			error		/*!< An error occured. */
		};
		

		/*!\name Constructors and destructor.
		 */
		//@{

		/*!\fn xmlParser()
		 * \brief Trivial constructor.
		 */
		xmlParser();

		/*!\fn virtual ~xmlParser()
		 * \brief Destructor.
		 */
		virtual ~xmlParser();
		//@}



		/*!\fn inline parserState state() const
		 * \brief Returns parser state.
		 * \return Parser state
		 * \sa parserState
		 */
		inline parserState state() const { return _state; };

		/*!\fn inline xmlElement * root() const
		 * \brief Returns root element.
		 * \return Root element.
		 */
		inline xmlElement * root() const { return _root; };

		/*!\fn inline xmlElement * detach()
		 * \brief Detaches root element from parser.
		 * \return Root element pointer.
		 *
		 * Detaching root element means, that XML tree will not be
		 * deleted when parser is destroyed. After detaching root
		 * element you should manually free XML tree. Only first call
		 * to detach() is valid. Any subsequent calls will return NULL,
		 * until next parsing proccess finished.
		 */
		inline xmlElement * detach() { xmlElement * o = _root; _root = NULL; return o; };

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

		//@}	

		/*!\name Parser methods.
		 */
		//@{
		
		/*!\fn bool prepare()
		 * \brief Prepares parser.
		 * \return true if success.
		 */
		bool prepare();

		/*!\fn void cleanup()
		 * \brief Cleanups internal state, for parser re-use.
		 */
		void cleanup();

		/*!\fn bool parse(const QByteArray& xml)
		 * \brief Parses input buffer.
		 * \param xml Input data.
		 * \return true if ok.
		 *
		 * You can call this method subsequently, providing more input data to
		 * parser.
		 */
		bool parse(const QByteArray& xml);
		bool parse(const QString& xml);

		/*!\fn bool parseFile(const QString& f)
		 * \brief Parses input file.
		 * \param f File name.
		 * \return true if ok.
		 */
		bool parseFile(const QString& fn);
		
		/*!\overload bool parseFile(QIODevice * f)
		 */
		bool parseFile(QIODevice * f);
		//@}
		//



	protected:

		/*!\name Parsing methods.
		 */
		//@{
		
		/*!\fn void parseStartTag(const QString& el, const QXmlAttributes& attrs)
		 * \brief Parse XML openning tag. Called internally by XML parser..
		 * \param el Element name.
		 * \param attr Attributes list.
		 */
		bool parseStartTag(const QString& el, const QXmlAttributes& attrs);

		/*!\fn void parseEndTag(const QString& el)
		 * \brief Parse XML openning tag. Called internally by XML parser.
		 * \param el Element name.
		 */
		bool parseEndTag(const QString& el);
		
		/*!\fn void parseCharacterData(const QString& s)
		 * \brief Parse element data.
		 * \param s Element data.
		 *
		 * \attention This method may be called multiple times for the same element.
		 */
		bool parseCharacterData(const QString& s);
		//@}

	private:
		parserState _state;

		xmlElement * _root;
		xmlElement * _active;
		
		QString _encoding;

		struct __private;
		struct __private * _private;

		friend class _xmlParserHandler;
};

};

#endif
