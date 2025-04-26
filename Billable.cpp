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

//Abstract Base Class: This class serves as a foundation for all items that can be billed (e.g., food and drinks).
//It will define common interfaces (pure virtual functions) that derived classes must implement.
#include <iostream>
#include "Billable.h"
#include "Utils.h"
using namespace std;

namespace seneca {
	void Billable::price(double value) {
		m_price = value;
	}

	void Billable::name(const char* name) {
		ut.alocpy(m_name, name);
	}

	Billable::Billable() {
		m_name = nullptr;
		m_price = 0.0;
	}

	Billable::Billable(const Billable& B) {
		m_name = ut.alocpy(B.m_name);
		m_price = B.m_price;
	}

	Billable& Billable::operator=(const Billable& B)
	{
		if (this != &B) {
			ut.alocpy(m_name, B.m_name);
			m_price = B.m_price;
		}

		return *this;
	}

	Billable::~Billable()
	{
		delete[] m_name;
	}

	double Billable::price() const {
		return m_price;
	}

	Billable::operator const char* () const {
		return m_name;
	}

	//code based from Professor Fardad's class notes
	double operator+(double money, const Billable& B) {
		return money + B.price();
	}

	//code based from Professor Fardad's class notes
	double& operator+=(double& money, const Billable& B) {
		return money += B.price();
	}
}