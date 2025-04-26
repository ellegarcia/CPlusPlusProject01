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
-----------------------------------------------------------
A lot of my codes are copied or based from Professor Fardad's codes during classes.
-----------------------------------------------------------*/
#ifndef SENECA_MENU_H
#define SENECA_MENU_H
#include <iostream>
#include "constants.h"

namespace seneca {

	class Menu;

	class MenuItem {
	private:
		char* m_menuItemName;
		unsigned int m_menuItemIndentLevel;
		unsigned int m_menuItemIndentsize;
		int m_numberingMenuItems;

		MenuItem(const char* menuItemName, unsigned int menuItemIndentLevel, unsigned int menuItemIndentsize, int numberingMenuItems);
		virtual ~MenuItem();

		MenuItem() = delete;
		MenuItem& operator=(const MenuItem& item) = delete;
		
		operator bool() const;

		// The following code is copied from Professor Fardad's class notes.
		/// <summary>
		/// Display's the output.
		/// </summary>
		std::ostream& display(std::ostream& ostr = std::cout) const;

		friend class Menu;
	};

	class Menu {
		unsigned int m_menuIndentlevel;
		unsigned int m_menuIndentSize;
		unsigned int m_menuNumOfMenuItems;

		//These attributes must be initialized in the member initializer list
		MenuItem m_menuTitle;
		MenuItem m_menuExitOption;
		MenuItem m_menuEntryPrompt;

		// When adding MenuItem objects, they should be dynamically allocated and stored in this array.
		// Ensure that the number of MenuItem objects does not exceed the size of the array.
		MenuItem* m_menuItemsArr[MaximumNumberOfMenuItems];

	public:
		Menu(const char* menuTitle, const char* menuExitOption = "Exit", unsigned int menuIndentlevel = 0, unsigned int menuIndentSize = 3);
		Menu(Menu& menu) = delete;
		Menu& operator=(Menu& menu) = delete;

		Menu& operator<<(const char* menuMenuItems);

		virtual ~Menu();

		size_t select() const;
	};

	size_t operator<<(std::ostream& ostr, const Menu& m);
}
#endif

