/* Citation and Sources...
Final Project Milestone 3
Module: Menu
Filename: Menu.cpp
Version 1.0
Author: April Roxelle Garcia
Revision History
-----------------------------------------------------------
Date		Reason				Milestone
2025/3/8	File created			1
2025/3/16   File created			2
2025/3/23	File Created			3
-----------------------------------------------------------
No copied codes here. I did all the codes here on my own.
-----------------------------------------------------------*/
#ifndef SENECA_DRINK_H
#define SENECA_DRINK_H
#include <iostream>
#include <fstream>
#include "constants.h"
#include "Billable.h"

namespace seneca {
	class Drink : public Billable {
		char m_size;

	public:
		Drink();

		//Displays item information in a formatted way
		std::ostream& print(std::ostream& ostr = std::cout) const;

		//Takes customer order for details of the item (e.g., size, customizations)
		bool order();

		//Returns true if details have been set, indicating the item is ordered.
		bool ordered()const;

		//Reads item details from an input file
		std::ifstream& read(std::ifstream& file);

		double price() const;
	};
}

#endif // !SENECA_DRINK_H
