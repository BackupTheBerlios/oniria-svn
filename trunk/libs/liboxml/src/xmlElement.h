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
#ifndef _XMLELEMENT_H
#define _XMLELEMENT_H

#include <QString>
#include <QMap>
#include <QMultiMap>
#include <QList>
#include "dll.h"
#include "xmlAttribute.h"

namespace onirXML {

/*!\class xmlElement
 * \brief Represents XML element
 */
class LIBOXML_API xmlElement : public QObject {

		Q_OBJECT

	public:

		/*!\name Constructors and destructor.
		 */
		//@{

		/*!\fn xmlElement(const QString& name = "", const QString& value = "")
		 * \brief Constructor.
		 * \param name Element name.
		 * \param value Element value.
		 */
		xmlElement(const QString& name = "", const QString& value = "");

		/*!\overload xmlElement(const QString& name = "", const QString& value = "")
		 */
		xmlElement(const QString& name, int value);

		/*!\fn virtual ~xmlElement()
		 * \brief Destructor.
		 */
		virtual ~xmlElement();
		//@}

		/*!\name Basic methods.
		 */
		//@{

		/*!\fn bool valid() const
		 * \brief Checks element validity.
		 * \return true if element is valid.
		 */
		bool valid() const;

		/*!\fn bool empty() const
		 * \brief Checks if element is an empty element.
		 * \return true if element is empty.
		 *
		 * Element is empy if it has no children and no value.
		 */
		bool empty() const;

		/*!\fn inline void name(const QString& aname)
		 * \brief Sets element name.
		 * \param aname Element name.
		 */
		inline void name(const QString& aname) { _name = aname; };

		/*!\fn void value(const QString& avalue)
		 * \brief Sets element value.
		 * \param avalue Element value.
		 */
		void value(const QString& avalue);

		/*!\overload void value(int avalue)
		 */
		void value(int avalue);

		/*!\fn inline void order(int aorder)
		 * \brief Sets element order.
		 * \param aorder Element order.
		 */
		inline void order(int aorder) { _order = aorder; };

		/*!\fn inline const QString& name() const
		 * \brief Returns element name.
		 * \return Element name.
		 */
		inline const QString& name() const { return _name; };

		/*!\fn inline const QString& value() const
		 * \brief Returns element value.
		 * \return Element value.
		 */
		inline const QString& value() const { return _value; };

		/*!\fn inline int order() const
		 * \brief Returns element order.
		 * \return Element order.
		 */
		inline int order() const { return _order; };

		/*!\fn inline xmlElement * parent() const
		 * \brief Returns parent element.
		 * \return Parent element.
		 */
		inline xmlElement * parent() const { return _parent; };

		/*!\fn inline const QString& encoding() const
		 * \brief Returns XML encoding.
		 * \return Encoding.
		 */
		inline const QString& encoding() const { return _encoding; };

		/*!\fn inline void encoding(const QString& aencoding)
		 * \brief Sets XML encoding.
		 * \param aencoding Encoding.
		 */
		inline void encoding(const QString& aencoding) { _encoding = aencoding; };
		//@}

		/*!\name Attributes methods.
		 */
		//@{

		/*!\fn xmlAttribute * addAttribute(const QString& name, const QString& value)
		 * \brief Adds element attribute.
		 * \param name Name of attribute.
		 * \param value Value of attribute.
		 * \return Pointer to newly added attribute.
		 */
		xmlAttribute * addAttribute(const QString& name, const QString& value);

		/*!\overload xmlAttribute * addAttribute(const QString& name, int value)
		 */
		xmlAttribute * addAttribute(const QString& name, int value);

		/*!\fn xmlAttribute * addAttribute(xmlAttribute * attrib)
		 * \brief Adds element attribute.
		 * \param attrib Attribute to add.
		 * \return Pointer to newly added attribute.
		 */
		xmlAttribute * addAttribute(xmlAttribute * attrib);

		/*!\fn xmlAttribute * attribute(const QString& name) const
		 * \brief Returns pointer to attribute with given name.
		 * \param name Name of attribute.
		 * \return Pointer to attribute or NULL if attribute not found.
		 */
		xmlAttribute * attribute(const QString& name) const;

		/*!\fn const QString& attributeValue(const QString& name, const QString& def = "") const
		 * \brief Returns attribute value.
		 * \param name Name of attribute.
		 * \param def Default value to be returned when attribute not found.
		 * \return Attribute value or default.
		 */
		const QString& attributeValue(const QString& name, const QString& def = "") const;

		/*!\fn inline const QMap<QString, xmlAttribute *>& attributes() const
		 * \brief Returns attributes.
		 * \return Attribute map (name, xmlAttribute *)
		 */
		inline const QMap<QString, xmlAttribute *>& attributes() const { return _attributes; };

		/*!\overload inline void attributes(map<QString, xmlAttribute *>& dst) const
		 */
		inline void attributes(QMap<QString, xmlAttribute *>& dst) const { dst = _attributes; };
		//@}

		/*!\name Child elements methods.
		 */
		//@{

		/*!\fn xmlElement * addChild(const QString& name, const QString& value)
		 * \brief Adds child element.
		 * \param name Child name.
		 * \param value Child value.
		 * \return Pointer to newly added element.
		 */
		xmlElement * addChild(const QString& name, const QString& value);

		/*!\overload xmlElement * addChild(const QString& name, int value)
		 */
		xmlElement * addChild(const QString& name, int value);

		/*!\fn xmlElement * addChild(xmlElement * elem)
		 * \brief Adds child element.
		 * \param elem Element to add.
		 * \return Pointer to newly added element.
		 */
		xmlElement * addChild(xmlElement * elem);

		/*!\fn inline const QMultiMap<QString, xmlElement *>& children() const
		 * \brief Returns children elements.
		 * \return Map of children elements (name, xmlElement *>.
		 */
		inline const QMultiMap<QString, xmlElement *>& children() const { return _children; };

		/*!\overload inline void children(QMultiMap<QString, xmlElement *>& dst) const
		 */
		inline void children(QMultiMap<QString, xmlElement *>& dst) const { dst = _children; };

		/*!\fn void children(const QString& name, QList<xmlElement *>& dst) const
		 * \brief Returns list of children elements with given name only.
		 * \param name Name of elements.
		 * \param dst List which will be filled with elements.
		 */
		int children(const QString& name, QList<xmlElement *>& dst) const;

		/*!\fn xmlElement * child(const QString& name) const
		 * \brief Returns pointer to child element with given name.
		 * \param name Name of element.
		 * \return Pointer to child element or NULL if attribute not found.
		 *
		 * If there's more than one child element with given name, this method
		 * returns pointer to one of them, possibly first, but this is not a rule.
		 */
		xmlElement * child(const QString& name) const;

		/*!\fn const QString& childValue(const QString& name, const QString& def = "") const
		 * \brief Returns child element value.
		 * \param name Name of child element.
		 * \param def Default value to be returned when child element not found.
		 * \return Child element value or default.
		 *
		 * If there's more than one child element with given name, this method
		 * returns value of one of them, possibly first, but this is not a rule.
		 */
		const QString& childValue(const QString& name, const QString& def = "") const;

		/*!\fn QMultiMap<QString, xmlElement *> Detach()
		 * \brief Returns and detach children elements.
		 * \return Map of children elements (name, xmlElement *>.
		 */
		QMultiMap<QString, xmlElement *> detach();

		/*!\overload void detach(QMultiMap<QString, xmlElement *>& dst)
		 */
		void detach(QMultiMap<QString, xmlElement *>& dst);

		/*!\fn void detach(const QString& name, QList<xmlElement *>& dst)
		 * \brief Returns and detach list of children elements with given name only.
		 * \param name Name of elements.
		 * \param dst List which will be filled with elements.
		 */
		int detach(const QString& name, QList<xmlElement *>& dst);

		/*!\fn xmlElement * detach(const QString& name)
		 * \brief Returns pointer to child element with given name and detach.
		 * \param name Name of element.
		 * \return Pointer to child element or NULL if attribute not found.
		 *
		 * If there's more than one child element with given name, this method
		 * returns pointer to one of them, possibly first, but this is not a rule.
		 */
		xmlElement * detach(const QString& name);

		//@}

		/*!\name Formating methods.
		 */
		//@{

		/*!\fn QString formatOpening(bool one_line = true, bool force_non_empty = false, const QString& indent_string = "\t", unsigned int indent_level = 0) const
		 * \brief Formats opening tag of element into QString, that could be written into XML stream.
		 * \param one_line true if output should be unformated.
		 * \param force_non_empty If false, when element contains no content it will be formated as <element />
		 * \param indent_string QString used for indentation.
		 * \param indent_level Indentation level. Used in formatting.
		 * \return Formated opening tag.
		 * \sa formatClosing(), formatContent(), format()
		 */
		QString formatOpening(bool one_line = true, bool force_non_empty = false, const QString& indent_string = "\t", unsigned int indent_level = 0) const;

		/*!\fn QString formatContent(bool one_line = true, const QString& indent_string = "\t", unsigned int indent_level = 0) const
		 * \brief Formats content of element into QString, that could be written into XML stream.
		 * \param one_line true if output should be unformated.
		 * \param indent_string QString used for indentation.
		 * \param indent_level Indentation level. Used in formatting.
		 * \return Formated content.
		 */
		QString formatContent(bool one_line = true, const QString& indent_string = "\t", unsigned int indent_level = 0) const;

		/*!\fn QString formatClosing(bool one_line = true, bool force = false, const QString& indent_string = "\t", unsigned int indent_level = 0) const
		 * \brief Formats closing tag of element into QString, that could be written into XML stream.
		 * \param one_line true if output should be unformated.
		 * \param force true if closing tag should be always formated, even if element is empty.
		 * \param indent_string QString used for indentation.
		 * \param indent_level Indentation level. Used in formatting.
		 * \return Formated closing tag.
		 */
		QString formatClosing(bool one_line = true, bool force = false, const QString& indent_string = "\t", unsigned int indent_level = 0) const;

		/*!\fn QString format(bool one_line = true, bool force_non_empty = false, const QString& indent_string = "\t", unsigned int indent_level = 0) const
		 * \brief Formats element into QString, that could be written into XML stream.
		 * \param one_line true if output should be unformated.
		 * \param force_non_empty If false, when element contains no content it will be formated as <element />
		 * \param indent_string QString used for indentation.
		 * \param indent_level Indentation level. Used in formatting.
		 * \return Formated element.
		 */
		QString format(bool one_line = true, bool force_non_empty = false, const QString& indent_string = "\t", unsigned int indent_level = 0) const;
		//@}

	protected:

		/*!\fn inline void parent(xmlElement * parent)
		 * \brief Sets parent element.
		 * \param parent Parent element.
		 */
		inline void parent(xmlElement * parent) { _parent = parent; };

	private:
		xmlElement * _parent;

		QString _name;
		QString _value;
		int _order;
		QString _encoding;

		QMultiMap<QString, xmlElement *> _children;
		QMap<QString, xmlAttribute *> _attributes;

		QMap<int, xmlElement *> _child_order;
		QMap<int, xmlAttribute *> _attr_order;
		int _last_child;
		int _last_attr;
};

};

#endif
