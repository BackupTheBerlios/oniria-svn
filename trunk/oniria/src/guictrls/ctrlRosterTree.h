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

#ifndef __CTRL_ROSTER_TREE__
#define __CTRL_ROSTER_TREE__

#include <string>
#include <vector>
#include <list>

using std::string;
using std::vector;
using std::list;

struct customData
{
	int number;
	string str;
};

class wxImage;
class scrollCanvas;

/*!\class ctrlRosterTreeItem
 * \brief Single item window
 * This class represents individual element on tree
*/
class ctrlRosterTreeItem: public wxPanel {

	public:
		
		/*!\enum clickPlace
		 * \brief After click event you can get info at cursor pos
		 */
		enum clickPlace { 
			unknown, //!< undefined item place
			image,  //!< on icon on left site
			title,  //!< on item title
			description //!< in item description
		};
		
		/*!\name Constructors and destructor
		 */
		//@{

		/*!\fn ctrlRosterTreeItem(wxWindow * parent)
		 * \brief Constructor
		 */
		ctrlRosterTreeItem(wxWindow * parent);
		
		/*!\fn ~ctrlRosterTreeItem()
		 * \brief Destructor
		 */
		~ctrlRosterTreeItem();
		
		//@}
		
		
		void Title(const string & s);
		inline const string & Title() const { return _title; };

		void Description(const string & s);
		inline const string & Description() const { return _description; };

		inline void Id(const string & s){ _id = s; };
		inline const string& Id() const { return _id; };

		inline vector<ctrlRosterTreeItem *> * Items() { return &_items; };

		inline void Expanded(bool e) { _expanded = e; };
		inline bool Expanded() const { return _expanded; };

		inline void Selected(bool s) { _selected = s; };
		inline bool Selected() const { return _selected; };
		
		inline void Group(bool b) { _group = b; };
		inline bool Group() const { return _group; };
		
		inline customData Data() { return _itemData; };
		inline void Data(const customData &data) { _itemData = data; };

		inline void Parent(ctrlRosterTreeItem * p) { _parent = p; };
		inline ctrlRosterTreeItem * Parent() { return _parent; };

		void NormalIcon(wxImage * i);
		void ExpandedIcon(wxImage * i);

		inline wxImage *NormalIcon() { return _normal_i; };
		inline wxImage *ExpandedIcon() { return _expanded_i; };
		
		void SkinRoot(const string& s);
		string Skin() const;
		string Skin(const string& id) const;
		
		clickPlace ClickPlace();

		inline void Hidden(bool b) { _hidden = b; };
		inline bool Hidden() const { return _hidden; };
		inline void SetOwner(wxScrolledWindow * w) { _owner = w; }
		wxSize Draw(bool draw = true);
		void SetupFonts();

	protected:
		void OnPaint(wxPaintEvent& event);
		void OnMouseDown(wxMouseEvent &event);
		void OnTimer(wxTimerEvent& event);
	private:		
		void DrawBkGround(wxDC & dc);		
		wxSize DrawImage(wxDC & dc,const wxPoint & p, bool draw = true);		
		vector<ctrlRosterTreeItem *> _items;
		ctrlRosterTreeItem * _parent;
		wxImage * _normal_i;
		wxImage * _expanded_i;
		wxScrolledWindow * _owner;		
		bool _hidden;
		bool _expanded;
		bool _selected;
		bool _group;
		string _skin;
		wxTimer _timer;
		string _id;
		string _title;
		string _description;
		wxFont _title_fnt;
		wxFont _desc_fnt;
		wxPoint _lastClick;
		wxRect _imageRect;
		wxRect _titleRect;
		wxRect _descriptionRect;
		customData _itemData;
		DECLARE_EVENT_TABLE();
};

/*!\class ctrlRosterTree
 * \brief Control to represent roster
 */
class ctrlRosterTree : public wxScrolledWindow {

	public:
	
		/*!\name Constructors and destructor
		 */
		//@{

		/*!\fn ctrlRosterTree(wxWindow * parent, wxWindowID id = -1)
		 * \brief Constructor
		 */
		ctrlRosterTree(wxWindow * parent, wxWindowID id = -1);
		
		/*!\fn ~ctrlRosterTree()
		 *\brief Destructor
		 */
		~ctrlRosterTree();
		
		//@}

		/*!\fn void AddItem(const string & root, const string & id, const string & name, const string & desc = "", bool groupitem = false, wxImage * normal = NULL, wxImage * expanded = NULL, bool redraw = false)
		 * \brief Function add item to tree
		 * \param root id of parent item, if "" then item is in root node
		 * \param id item identifier MUST BE UNIQUE IN WHOLE TREE
		 * \param name display name
		 * \param desc display description
		 * \param groupitem this flag tell is item will be paren for a few items
		 * \param normal pointer on normal image
		 * \param expanded pointer to image will be displayed when item is expand
		 * \param redraw if true then tree will be redraw after add  item
		 */		
		void AddItem(const string & root, const string & id, const string & name, const string & desc = "", bool groupitem = false, wxImage * normal = NULL, wxImage * expanded = NULL, bool redraw = false);
		
		/*!\fn void RemoveItem(const string & id, bool children_only = false, bool redraw = false)
		 * \brief remove item from tree
		 * \param id identifier item to remove
		 * \param children_only if true then only subitems will be removed
		 * \param redraw if true then tree will be redraw after remove item
		 */		 
		void RemoveItem(const string & id, bool children_only = false, bool redraw = false);

		/*!\class void Title(const string & id, const string & title, bool redraw = false)
		 * \brief Set title for item
		 * \param id identifier item witch title has to be change
		 * \param title title
		 * \param redraw if true item will be redraw after change
		 */
		void Title(const string & id, const string & title, bool redraw = false);
		
		/*!\class void Description(const string & id, const string & desc, bool redraw = false)
		 * \brief Set description for item
		 * \param id identifier item witch description has to be change
		 * \param desc title
		 * \param redraw if true item will be redraw after change
		 */
		void Description(const string & id, const string & desc, bool redraw = false);
		wxImage *NormalIcon(const string & id, wxImage * image, bool delete_old = true, bool redraw = false);
		wxImage *ExpandedIcon(const string & id, wxImage * image, bool delete_old = true, bool redraw = false);
		vector<ctrlRosterTreeItem *> & Selected();
		
		void Redraw(const string &from_item);
		bool Order(const string& id, const vector<string>& order, bool redraw = false);
		
		void BackgroundColour(const wxColour& colour);

		ctrlRosterTreeItem * FindItem(const string & id);

	protected:
		void EventFunc(wxCommandEvent & event);
		void OnMouseDown(wxMouseEvent &event);
	private:
		ctrlRosterTreeItem * FindItemHelper(ctrlRosterTreeItem * root, const string & id);
		void DrawItems(ctrlRosterTreeItem * root, wxRect & rc, bool show, ctrlRosterTreeItem * from = NULL);
		void DrawItems(ctrlRosterTreeItem * from = NULL);
		void DisableSelections(ctrlRosterTreeItem * root);
		void RemoveItems(ctrlRosterTreeItem * root);
		bool _candraw;
		ctrlRosterTreeItem * _root;
		scrollCanvas * _canvas;
		vector<ctrlRosterTreeItem *> _selected;
		/*
		wxImage *_toggleNormalIcon;
		wxImage *_toggleExpandIcon;
		*/

		DECLARE_EVENT_TABLE();
};

DECLARE_LOCAL_EVENT_TYPE(wxEVT_MOUSE_DB_CLICK, -1)

#endif /* __CTRL_ROSTER_TREE__ */
