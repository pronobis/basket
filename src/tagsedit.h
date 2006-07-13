/***************************************************************************
 *   Copyright (C) 2005 by S�bastien Lao�t                                 *
 *   slaout@linux62.org                                                    *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef TAGEDIT_H
#define TAGEDIT_H

#include <kdialogbase.h>
#include <kcombobox.h>
#include <qlistview.h>
#include <qvaluelist.h>

class QGroupBox;
class QLineEdit;
class QCheckBox;
class KKeyButton;
class KIconButton;
class KFontCombo;
class QLabel;

class KColorCombo2;

class Tag;
class State;

class FontSizeCombo : public KComboBox
{
  Q_OBJECT
  public:
	FontSizeCombo(bool rw, bool withDefault, QWidget *parent = 0, const char *name = 0);
	~FontSizeCombo();
  private:
	bool m_withDefault;
};

class StateCopy
{
  public:
	typedef QValueList<StateCopy*> List;
	StateCopy(State *old = 0);
	State *oldState;
	State *newState;
	void copyBack();
};

class TagCopy
{
  public:
	typedef QValueList<TagCopy*> List;
	TagCopy(Tag *old = 0);
	Tag *oldTag;
	Tag *newTag;
	QValueList<StateCopy*> states;
	void copyBack();
	bool isMultiState();
};

class TagListViewItem : public QListViewItem
{
  public:
	TagListViewItem(QListView     *parent, TagCopy *tagCopy);
	TagListViewItem(QListViewItem *parent, TagCopy *tagCopy);
	TagListViewItem(QListView     *parent, QListViewItem *after, TagCopy *tagCopy);
	TagListViewItem(QListViewItem *parent, QListViewItem *after, TagCopy *tagCopy);
	TagListViewItem(QListView     *parent, StateCopy *stateCopy);
	TagListViewItem(QListViewItem *parent, StateCopy *stateCopy);
	TagListViewItem(QListView     *parent, QListViewItem *after, StateCopy *stateCopy);
	TagListViewItem(QListViewItem *parent, QListViewItem *after, StateCopy *stateCopy);
	~TagListViewItem();
	TagCopy*   tagCopy()   { return m_tagCopy;   }
	StateCopy* stateCopy() { return m_stateCopy; }
  private:
	TagCopy   *m_tagCopy;
	StateCopy *m_stateCopy;
};

class TagListView : public QListView
{
  Q_OBJECT
  public:
	TagListView(QWidget *parent = 0, const char *name = 0, WFlags flags = 0);
	~TagListView();
	void keyPressEvent(QKeyEvent *event);
	void contentsMouseDoubleClickEvent(QMouseEvent*);
};

/**
  * @author S�bastien Lao�t
  */
class TagsEditDialog : public KDialogBase
{
  Q_OBJECT
  public:
	TagsEditDialog(QWidget *parent = 0, const char *name = 0);
	~TagsEditDialog();
	QValueList<Tag*>   deletedTags()   { return m_deletedTags;   }
	QValueList<State*> deletedStates() { return m_deletedStates; }
	QValueList<State*> addedStates()   { return m_addedStates;   }
  private slots:
	void newTag();
	void newState();
	void moveUp();
	void moveDown();
	void deleteTag();
	void modified();
	void currentItemChanged(QListViewItem *item);
  private:
	void loadBlankState();
	void loadStateFrom(State *state);
	void loadTagFrom(Tag *tag);
	void saveStateTo(State *state);
	void saveTagTo(Tag *tag);
	QListView     *m_tags;
	QLineEdit     *m_tagName;
	KKeyButton    *m_shortcut;
	QPushButton   *m_removeShortcut;
	QCheckBox     *m_inherit;
	QGroupBox     *m_stateBox;
	QLabel        *m_stateNameLabel;
	QLineEdit     *m_stateName;
	KIconButton   *m_emblem;
	QPushButton   *m_removeEmblem;
	QPushButton   *m_bold;
	QPushButton   *m_underline;
	QPushButton   *m_italic;
	QPushButton   *m_strike;
	KColorCombo2  *m_textColor;
	KFontCombo    *m_font;
	FontSizeCombo *m_fontSize;
	KColorCombo2  *m_backgroundColor;

	TagCopy::List      m_tagCopies;
	QValueList<Tag*>   m_deletedTags;
	QValueList<State*> m_deletedStates;
	QValueList<State*> m_addedStates;

	bool m_loading;
};

#endif // TAGEDIT_H
