/* Citation and Sources...
Final Project Milestone 2
Module: Menu
Filename: Menu.cpp
Version 1.0
Author: April Roxelle Garcia
Revision History
-----------------------------------------------------------
Date		Reason				Milestone 
2025/3/8	File created			1
2025/3/16   File created			2
-----------------------------------------------------------*/

//MenuItem Class: Represents individual items on the menu.
//Menu Class: Manages a collection of MenuItem objects and allows the user to select items from the menu.
//MenuItem and Menu. The Menu class owns a series of MenuItem objects and provides selection facilities for the user.
//You will implement member functions and operators that handle adding, removing, and displaying MenuItem objects and facilitate user interaction for selection.
#include <iostream>
#include "Menu.h"
#include "Utils.h"
using namespace std;
namespace seneca {

	MenuItem::MenuItem(const char* menuItemName, unsigned int menuItemIndentLevel, unsigned int menuItemIndentsize, int numberingMenuItems) {

		if (menuItemName == nullptr || ut.isspace(menuItemName) || menuItemIndentLevel > 4 || menuItemIndentsize > 4 || numberingMenuItems > int(MaximumNumberOfMenuItems)) {
			m_menuItemName = nullptr;
			m_menuItemIndentLevel = 0;
			m_menuItemIndentsize = 0;
			m_numberingMenuItems = 0;
		}
		else {
			m_menuItemName = new char[ut.strlen(menuItemName) + 1];
			ut.strcpy(m_menuItemName, menuItemName);
			m_menuItemIndentLevel = menuItemIndentLevel;
			m_menuItemIndentsize = menuItemIndentsize;
			m_numberingMenuItems = numberingMenuItems;
		}
	}

	MenuItem::~MenuItem() {
		delete[] m_menuItemName;
	}

	MenuItem::operator bool() const {
		return (m_menuItemName != nullptr && !ut.isspace(m_menuItemName));
	}

	ostream& MenuItem::display(ostream& ostr)const {
		if (m_menuItemName) {
			for (unsigned int i = 0; i < m_menuItemIndentLevel; i++) {
				for (unsigned int j = 0; j < m_menuItemIndentsize; j++) {
					ostr << " ";
				}
			}

			if (m_numberingMenuItems < 0) {
				ostr << "";
			}

			if (m_numberingMenuItems >= 0) {
				if (m_numberingMenuItems < 10) {
					ostr << " ";
				}
				ostr << m_numberingMenuItems << "- ";
			}

			char* temp = m_menuItemName;
			while (*temp != '\0' && ut.isspace(*temp)) {
				temp++;
			}
			ostr << temp;
		}
		else {
			ostr << "??????????";
		}

		return ostr;
	}

	Menu::Menu(const char* menuTitle, const char* menuExitOption, unsigned int menuIndentlevel, unsigned int menuIndentSize)
		: m_menuTitle(menuTitle, menuIndentlevel, menuIndentSize, -1), m_menuExitOption(menuExitOption, menuIndentlevel, menuIndentSize, 0), m_menuEntryPrompt("> ", menuIndentlevel, menuIndentSize, -1)
	{
		m_menuIndentlevel = menuIndentlevel;
		m_menuIndentSize = menuIndentSize;
		m_menuNumOfMenuItems = 0;

		for (size_t i = 0; i < MaximumNumberOfMenuItems; i++) {
			m_menuItemsArr[i] = nullptr;
		}

	}

	Menu& Menu::operator<<(const char* menuMenuItems) {

		if (m_menuNumOfMenuItems < MaximumNumberOfMenuItems) {
			m_menuItemsArr[m_menuNumOfMenuItems] = new MenuItem(menuMenuItems, m_menuIndentlevel, m_menuIndentSize, m_menuNumOfMenuItems + 1);
			m_menuNumOfMenuItems++;
		}

		return *this;
	}

	Menu::~Menu() {

		for (size_t i = 0; i < m_menuNumOfMenuItems; i++) {
			delete m_menuItemsArr[i];
			m_menuItemsArr[i] = nullptr;
		}
	}

	size_t Menu::select() const {

		int userInput = 0;
		
		if (m_menuTitle) {
			m_menuTitle.display(cout);
			cout << endl;
		}

		if (m_menuNumOfMenuItems > 0) {
			for (size_t i = 0; i < m_menuNumOfMenuItems; i++) {
				m_menuItemsArr[i]->display(cout);
				cout << endl;
			}
		}

		m_menuExitOption.display(cout);
		cout << endl;
		m_menuEntryPrompt.display(cout);

		userInput = ut.getInt(0, m_menuNumOfMenuItems);

		return userInput;
	}

	// helper function below copied or based from Professor Fardad's codes in class
	size_t operator<<(std::ostream& ostr, const Menu& m) {
		if (&ostr == &std::cout) {
			return m.select();
		}
		else {
			return 0;
		}
	}

}