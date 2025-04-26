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
-----------------------------------------------------------*/
#ifndef SENECA_BILLABLE_H
#define SENECA_BILLABLE_H
#include <iostream>
#include <fstream>
#include "constants.h"

namespace seneca {

	class Billable {
		char* m_name;
		double m_price;

	protected:
		void price(double value); //Sets the item's price
		void name(const char* name); //Sets the item's name, handling dynamic allocation

	public:
		Billable();
		Billable(const Billable& B);
		Billable& operator=(const Billable& B);
		virtual ~Billable();

		//Returns the item's price, allowing derived classes to override if needed.
		virtual double price() const;

		//Displays item information in a formatted way
		virtual std::ostream& print(std::ostream& ostr = std::cout) const = 0;

		//Takes customer order for details of the item (e.g., size, customizations)
		virtual bool order() = 0;

		//Returns true if details have been set, indicating the item is ordered.
		virtual bool ordered()const = 0;

		//Reads item details from an input file
		virtual std::ifstream& read(std::ifstream& file) = 0;

		operator const char* ()const;
	};

	double operator+(double money, const Billable& B);
	double& operator+=(double& money, const Billable& B);

}

#endif // !
