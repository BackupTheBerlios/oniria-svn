/* $Id: xmlStream.h 639 2006-01-03 14:22:18Z choman $ */
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
#ifndef _XMLSTREAM_H
#define _XMLSTREAM_H

#include <QIODevice>
#include <QString>
#include <QList>
#include "dll.h"

namespace onirXML {

class xmlElement;
class xmlStanza;
	
/*!\class xmlStream
 * \brief Class representing XML stream as defined in 
 * <a href="http://www.xmpp.org/specs/rfc3920.html#streams">RFC 3920</a>.
 * Mainly for XMPP stream.
 * \sa xmlStanza
 */
class LIBOXML_API xmlStream : public QObject {

		Q_OBJECT;

	public:

		/*!\enum streamState
		 * \brief XML stream state.
		 */
		enum streamState {
			unknown,	/*!< Unknown state, possibly uninitiated stream. */
			ready,		/*!< Stream is ready for use. */
			initiating,	/*!< Stream is establishing connection. */
			established,	/*!< Established stream, waiting for stanzas. */
			stanza,		/*!< Stream is currently receiving stanza. */
			closing,	/*!< Stream is in closing state. */
			error		/*!< Errorneus stream. */
		};
		


		/*!\name Constructors and destructor.
		 */
		//@{

		/*!\fn xmlStream()
		 * \brief Trivial constructor.
		 */
		xmlStream();

		/*!\fn xmlStream(QIODevice * istream, QIODevice * ostream)
		 * \brief Constructor.
		 * \param istream Input stream
		 * \param ostream Output stream. If NULL, input stream is used both
		 * as input and output stream.
		 */
		xmlStream(QIODevice * istream, QIODevice * ostream);

		/*!\fn virtual ~xmlStream()
		 * \brief Destructor.
		 */
		virtual ~xmlStream();
		//@}



		/*!\name Input/output stream methods.
		 */
		//@{
		
		/*!\fn QIODevice * input(QIODevice * istream)
		 * \brief Sets input stream pointer.
		 * \param istream Input stream
		 * \return Previous stream
		 */	
		QIODevice * input(QIODevice * istream);
		
		/*!\fn QIODevice * output(QIODevice * ostream)
		 * \brief Sets output stream pointer.
		 * \param ostream Output stream
		 * \return Previous stream
		 */	
		QIODevice * output(QIODevice * ostream);

		/*!\fn QIODevice * input() const
		 * \brief Returns input stream.
		 * \return Input stream.
		 */
		inline QIODevice * input() const { return _istream; };

		/*!\fn QIODevice * output() const
		 * \brief Returns output stream.
		 * \return Output stream.
		 */
		inline QIODevice * output() const { return _ostream; };
		//@}



		/*!\fn inline streamState state() const
		 * \brief Returns stream state.
		 * \return Stream state
		 * \sa streamState
		 */
		inline streamState state() const { return _state; };

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



		/*!\name Root elements methods.
		 */
		//@{
		/*!\fn inline xmlElement * inRoot() const
		 * \brief Returns input root element pointer.
		 * \return Input root element pointer.
		 */
		inline xmlElement * inRoot() const { return _in_root; };

		/*!\fn inline xmlElement * outRoot() const
		 * \brief Returns output root element pointer.
		 * \return Output root element pointer.
		 */
		inline xmlElement * outRoot() const { return _out_root; };
		//@}

	

		/*!\name Stanzas methods.
		 */
		//@{
		
		/*!\fn void addStanza(xmlStanza * stanza)
		 * \brief Adds stanza to output queue.
		 * \param stanza Stanza to add.
		 *
		 * Added stanza will be probably formated and sent in next Poll() call.
		 */
		void addStanza(xmlStanza * stanza);
		//@}


		//@}	

		/*!\name Stream methods.
		 */
		//@{
		
		/*!\fn bool prepare()
		 * \brief Prepares stream.
		 * \return true if success.
		 */
		bool prepare();

		/*!\fn void cleanup()
		 * \brief Cleanups internal state, for stream re-use.
		 */
		void cleanup();

		/*!\fn bool initiate()
		 * \brief Begins stream establishing.
		 * \return true if successfull.
		 * \sa prepare()
		 *
		 * You should set output root element attributes before calling this
		 * method. Don't set root element name, becaus it will be set by this
		 * method to stream:stream.
		 *
		 * \warning Even if initiate() returns \c true, it not means that stream
		 * is established. It only means, that stream establishing started.
		 * You should check stream state (see state()) to know whether stream
		 * is established.
		 */
		bool initiate();

		/*!\fn bool poll()
		 * \brief Does the main streaming stuff.
		 * \return true if something happen, otherwise false.
		 *
		 * This is main streaming method. It checks if there's any data
		 * to be send, receive new data, parse it, and whatever else
		 * is required. You should check return value to decide if any
		 * reaction is needed. If true, you can expect new stanzas, etc.
		 */
		bool poll();

		/*!\fn void close()
		 * \brief Begins stream closing.
		 * \return true if closing started and stream is now in closing state.
		 *
		 * You should call this method only when stream is in established state,
		 * or this method will fail.
		 */
		bool close();
		//@}
		//

	signals:

		void receivedStanza(xmlStanza * stanza);

	protected:

		/*!\name Parsing methods.
		 */
		//@{
		
		/*!\fn bool parse()
		 * \brief Parses input buffer.
		 * \return true if something happen, ie. new stanza(s) are available.
		 */
		bool parse();

		/*!\fn void parseStartTag(const char * el, const char ** attrs)
		 * \brief Parse XML openning tag. Called internally by expat handler.
		 * \param el Element name.
		 * \param attr Attributes list.
		 */
		void parseStartTag(const char * el, const char ** attrs);

		/*!\fn void parseEndTag(const char * el)
		 * \brief Parse XML openning tag. Called internally by expat handler.
		 * \param el Element name.
		 */
		void parseEndTag(const char * el);
		
		/*!\fn void parseCharacterData(const QString& s)
		 * \brief Parse element data.
		 * \param s Element data.
		 *
		 * \attention This method may be called multiple times for the same element.
		 */
		void parseCharacterData(const QString& s);
		//@}


	protected slots:

		void readyRead();

	private:
		QIODevice * _istream;
		QIODevice * _ostream;
		QString _encoding;

		QString _output;
		QString _input;

		streamState _state;

		xmlElement * _in_root;
		xmlElement * _out_root;

		xmlStanza * _active_stanza;

		QList<xmlStanza *> _out_stanzas;

		struct __private;
		struct __private * _private;

		friend class _xmlStreamHandler;
};

};

#endif
