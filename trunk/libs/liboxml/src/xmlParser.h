/* $Id: xmlParser.h 639 2006-01-03 14:22:18Z choman $ */
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
#ifndef _XMLPARSER_H
#define _XMLPARSER_H

#include "dll.h"


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



		/*!\fn inline parserState State() const
		 * \brief Returns parser state.
		 * \return Parser state
		 * \sa parserState
		 */
		inline parserState State() const { return _state; };

		/*!\fn inline xmlElement * Root() const
		 * \brief Returns root element.
		 * \return Root element.
		 */
		inline xmlElement * Root() const { return _root; };

		/*!\fn inline xmlElement * Detach()
		 * \brief Detaches root element from parser.
		 * \return Root element pointer.
		 *
		 * Detaching root element means, that XML tree will not be
		 * deleted when parser is destroyed. After detaching root
		 * element you should manually free XML tree. Only first call
		 * to Detach() is valid. Any subsequent calls will return NULL,
		 * until next parsing proccess finished.
		 */
		inline xmlElement * Detach() { xmlElement * o = _root; _root = NULL; return o; };

		/*!\fn inline const string& Encoding() const
		 * \brief Returns XML encoding.
		 * \return Encoding.
		 */
		inline const string& Encoding() const { return _encoding; };
		
		/*!\fn inline void Encoding(const string& encoding)
		 * \brief Sets XML encoding.
		 * \param encoding Encoding.
		 */
		inline void Encoding(const string& encoding) { _encoding = encoding; };

		//@}	

		/*!\name Parser methods.
		 */
		//@{
		
		/*!\fn bool Prepare()
		 * \brief Prepares parser.
		 * \return true if success.
		 */
		bool Prepare();

		/*!\fn void Cleanup()
		 * \brief Cleanups internal state, for parser re-use.
		 */
		void Cleanup();

		/*!\fn bool Parse(const string& xml)
		 * \brief Parses input buffer.
		 * \param xml Input data.
		 * \return true if ok.
		 *
		 * You can call this method subsequently, providing more input data to
		 * parser.
		 */
		bool Parse(const string& xml);

		/*!\overload bool Parse(const char * xml, size_t sz = 0)
		 */
		bool Parse(const char * xml, size_t sz = 0);

		/*!\fn bool ParseFile(const string& f)
		 * \brief Parses input file.
		 * \param f File name.
		 * \return true if ok.
		 */
		bool ParseFile(const string& fn);
		
		/*!\overload bool ParseFile(wxFSFile * f)
		 */
		bool ParseFile(wxFSFile * f);
		//@}
		//



	protected:

		/*!\name Parsing methods.
		 */
		//@{
		
		/*!\fn void ParseStartTag(const char * el, const char ** attrs)
		 * \brief Parse XML openning tag. Called internally by expat handler.
		 * \param el Element name.
		 * \param attr Attributes list.
		 */
		bool ParseStartTag(const char * el, const char ** attrs);

		/*!\fn void ParseEndTag(const char * el)
		 * \brief Parse XML openning tag. Called internally by expat handler.
		 * \param el Element name.
		 */
		bool ParseEndTag(const char * el);
		
		/*!\fn void ParseCharacterData(const string& s)
		 * \brief Parse element data.
		 * \param s Element data.
		 *
		 * \attention This method may be called multiple times for the same element.
		 */
		bool ParseCharacterData(const string& s);
		//@}

	private:
		parserState _state;

		xmlElement * _root;
		xmlElement * _active;
		
		string _encoding;

		struct __private;
		struct __private * _private;

		DECLARE_OOBJECT;

		friend void _xml_p_start_tag(void * data, const char * el, const char ** attr);
		friend void _xml_p_end_tag(void * data, const char * el);
		friend void _xml_p_character_data(void * data, const char * s, int len);
		friend void _xml_p_character_data(void * data, const wchar_t * s, int len);
		friend void _xml_p_decl(void * data, const char * version, const char * encoding, int standalone);
		friend void _xml_p_decl(void * data, const wchar_t * version, const wchar_t * encoding, int standalone);
};

};

#endif
