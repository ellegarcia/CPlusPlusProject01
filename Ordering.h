/* Citation and Sources...
Final Project Milestone 4
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
2025/3/30	File Created			4
-----------------------------------------------------------
No copied codes here. I did all the codes here on my own.
-----------------------------------------------------------*/
#ifndef SENECA_ORDERING_H
#define SENECA_OREDRING_H
#include <iostream>
#include <fstream>
#include "constants.h"
#include "Food.h"
#include "Drink.h"
#include "Menu.h"

namespace seneca {

	class Ordering {
		unsigned int m_foodCount;
		unsigned int m_drinkCount;
		unsigned int m_billCount;
		unsigned int m_billNumber;

		Food* m_food;
		Drink* m_drink;
		Billable* m_items[MaximumNumberOfBillItems]{};

		//This method prints a header for a bill.
		std::ostream& printBillTitle(std::ostream& ostr = std::cout) const;

		//This method prints the footer for a bill.
		std::ostream& printTotal(std::ostream& ostr, double totalAmount) const;

		//This function calculates the number of records in a file by counting the newline characters.
		size_t countRecords(const char* file) const;

	public:
		
		Ordering(const char* foodFile, const char* drinkFile);
		virtual ~Ordering();
		
		operator bool() const;
		int noOfBillItems() const;
		bool hasUnsavedBill() const;
		void listFoods() const;
		void listDrinks() const;
		void orderFood();
		void orderDrink();

		std::ostream& printBill(std::ostream& ostr) const;
		void resetBill();
	};
}
#endif // !SENECA_ORDERING_H
