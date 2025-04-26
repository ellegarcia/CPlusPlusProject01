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
#ifndef SENECA_FOOD_H
#define SENECA_FOOD_H
#include <iostream>
#include <fstream>
#include "Billable.h"
#include "constants.h"

namespace seneca {
	class Food : public Billable {
		bool m_ordered;
		bool m_child;
		char* m_customize;

	public:
		Food();
		Food(const Food& F);
		Food& operator=(const Food& F);
		virtual ~Food();

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
#endif // !SENECA_FOOD_H
