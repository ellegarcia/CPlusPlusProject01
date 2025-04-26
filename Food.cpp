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

//Derived Class: Inherits from Billable and represents a food item. This class should allow for different portion sizes, such as:
//Child portion
//Adult portion
#include "Utils.h"
#include "Food.h"
#include <iomanip>

using namespace std;

namespace seneca {

	Food::Food() {
		m_ordered = false;
		m_child = false;
		m_customize = nullptr;
	}

	Food::Food(const Food& F) : Billable(F) {
		m_ordered = F.m_ordered;
		m_child = F.m_child;
		m_customize = ut.alocpy(F.m_customize);
	}

	Food& Food::operator=(const Food& F) {

		if (this != &F) {
			Billable::operator=(F);
			m_ordered = F.m_ordered;
			m_child = F.m_child;
			ut.alocpy(m_customize, F.m_customize);
		}

		return *this;
	}

	Food::~Food() {
		delete[] m_customize;
	}

	ostream& Food::print(ostream& ostr) const {
		ostr << left << setw(28) << setfill('.') << (const char*)(*this);

		if (m_ordered) {
			if (m_child) {
				ostr << "Child";
			}
			else {
				ostr << "Adult";
			}
		}
		else {
			ostr << ".....";
		}

		ostr << right << setw(7) << setfill(' ') << fixed << setprecision(2) << price();

		if (m_customize && &ostr == &cout) {
			ostr << " >> ";
			for (int i = 0; m_customize[i] != '\0' && i < 30; i++) {
				ostr << m_customize[i];
			}
		}

		return ostr;
	}

	bool Food::order() {
		int selected = -1;
		bool isValid = false;

		cout << "         Food Size Selection\n";
		cout << "          1- Adult\n";
		cout << "          2- Child\n";
		cout << "          0- Back\n";
		cout << "         > ";

		selected = ut.getInt(0, 2);

		if (selected == 1 || selected == 2) {
			if (selected == 2) {
				m_child = true;
			}
			m_ordered = true;
			isValid = true;
		}
		else {
			m_ordered = false;
			delete[] m_customize;
			m_customize = nullptr;
		}

		if (isValid) {
			cout << "Special instructions\n";
			cout << "> ";
			//cin.ignore();
			char temp[201]{};
			cin.getline(temp, 200);

			if (ut.isspace(temp)) {
				delete[] m_customize;
				m_customize = nullptr;
			}
			else {
				ut.alocpy(m_customize, temp);
			}
		}

		return isValid;
	}

	bool Food::ordered() const {
		return m_ordered;
	}

	ifstream& Food::read(ifstream& file) {
		//set foodName to 100 characters - assuming no drink name is going to exceed 100 char
		char foodName[100]{};
		double foodPrice = 0.0;

		file.getline(foodName, 100, ',');
		file >> foodPrice;

		if (file) {
			file.ignore(1000, '\n');
			Billable::name(foodName);
			Billable::price(foodPrice);
			m_child = false;
			m_ordered = false;
			delete[] m_customize;
			m_customize = nullptr;
		}

		return file;
	}

	double Food::price() const {
		double basePrice = Billable::price();

		if (m_ordered && m_child) {
			basePrice = basePrice * 0.5;
		}

		return basePrice;
	}


}