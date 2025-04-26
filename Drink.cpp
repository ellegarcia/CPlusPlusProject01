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

//Derived Class: Inherits from Billable and represents a drink item. It should support various sizes:
//Small
//Medium
//Large
//Extra Large
#include "Drink.h"
#include "Utils.h"
#include <iomanip>

using namespace std;

namespace seneca {

	seneca::Drink::Drink() {
		m_size = '\0';
	}

	ostream& seneca::Drink::print(ostream& ostr) const {

		ostr << left << setw(28) << setfill('.') << (const char*)(*this);

		if (m_size == 'S') {
			ostr << "SML..";
		}
		else if (m_size == 'M') {
			ostr << "MID..";
		}
		else if (m_size == 'L') {
			ostr << "LRG..";
		}
		else if (m_size == 'X') {
			ostr << "XLR..";
		}
		else {
			ostr << ".....";
		}

		ostr << right << setw(7) << setfill(' ') << fixed << setprecision(2) << price();

		return ostr;
		
	}

	bool Drink::order() { 
		int selected = -1;
		bool isValid = false;

		cout << "         Drink Size Selection\n";
		cout << "          1- Small\n";
		cout << "          2- Medium\n";
		cout << "          3- Larg\n";
		cout << "          4- Extra Large\n";
		cout << "          0- Back\n";
		cout << "         > ";

		selected = ut.getInt(0, 4);

		if (selected == 1) {
			m_size = 'S';
			isValid = true;
		} 
		else if (selected == 2) {
			m_size = 'M';
			isValid = true;
		}
		else if (selected == 3) {
			m_size = 'L';
			isValid = true;
		}
		else if (selected == 4) {
			m_size = 'X';
			isValid = true;
		}
		else {
			m_size = '\0';
			isValid = false;
		}

		return isValid;
	}

	bool Drink::ordered() const {
		bool isValid = false;

		if (m_size != '\0') {
			isValid = true;
		}

		return isValid;
	}

	ifstream& Drink::read(ifstream& file) {
		// read: name of drink,price
		// eg. Orange Juice,3.5<Newline>

		//set drinkName to 100 characters - assuming no drink name is going to exceed 100 char
		char drinkName[100]{};
		double drinkPrice = 0.0;

		file.getline(drinkName, 100, ',');
		file >> drinkPrice;

		if (file) {
			file.ignore(1000, '\n');
			Billable::name(drinkName);
			Billable::price(drinkPrice);
			m_size = '\0';
		}

		return file;
	}

	double Drink::price() const {
		double basePrice = Billable::price();
		//double price = 0.0;
		
		if (ordered()) {
			if (m_size == 'S') {
				basePrice *= 0.5;
			}
			else if (m_size == 'M') {
				basePrice *= 0.75;
			}
			else if (m_size == 'X') {
				basePrice *= 1.5;
			}
		}

		return basePrice;
	}
}
