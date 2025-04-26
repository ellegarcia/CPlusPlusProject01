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
-----------------------------------------------------------*/

//This module manages the ordering process and will include methods for:
//Loading available foods and drinks from data files.
//Displaying food and drink lists separately.
//Taking customer orders(interacting with the Menu class).
//Generating and printing the bill.
//Saving a copy of the bill to a file named after the bill number.
#include "Ordering.h"
#include "Utils.h"
#include <iostream>
#include <iomanip>
using namespace std;

namespace seneca {
	std::ostream& Ordering::printBillTitle(std::ostream& ostr) const
	{
		return ostr << "Bill # " << setfill('0') << setw(3) << m_billNumber << " " << "=============================" << endl;
	}

	std::ostream& Ordering::printTotal(std::ostream& ostr, double totalAmount) const
	{
		double totalAmountWithTax = totalAmount + (totalAmount * Tax);
		double computedTax = (totalAmount * Tax);

		ostr << fixed << setprecision(2);
		ostr << right << setw(27) << "Total:" << setw(13) << totalAmount << endl;
		ostr << right << setw(25) << "Tax:" << setw(15) << computedTax << endl;
		ostr << right << setw(31) << "Total+Tax:" << setw(9) << totalAmountWithTax << endl;
		ostr << "========================================" << endl;

		return ostr;
	}

	size_t Ordering::countRecords(const char* file) const
	{
		int counter = 0;
		char ch;
		ifstream fileName(file);

		while (!fileName.fail()) {
			fileName.get(ch);

			if (!fileName.fail() && ch == '\n') {
				++counter;
			}
		}

		return counter;
	}

	Ordering::Ordering(const char* drinkFile, const char* foodFile)
	{
		m_food = nullptr;
		m_drink = nullptr;
		m_billCount = 0;
		m_billNumber = 1;

		//count records
		int drinkCount = countRecords(drinkFile);
		int foodCount = countRecords(foodFile);

		//open files for reading
		ifstream drinkListInFile(drinkFile);
		ifstream foodListInFile(foodFile);

		if (drinkListInFile && foodListInFile) {

			// dynamic array allocation
			m_food = new Food[foodCount];
			m_drink = new Drink[drinkCount];

			m_foodCount = 0;
			m_drinkCount = 0;

			int successFoodRead = 0;
			int successDrinkRead = 0;
			int failFoodRead = 0;
			int failDrinkRead = 0;

			for (int i = 0; i < drinkCount && failDrinkRead == 0; i++) {
				if (m_drink[i].read(drinkListInFile)) {
					successDrinkRead++;
				}
				else {
					failDrinkRead = 1;
				}
			}

			for (int i = 0; i < foodCount && failFoodRead == 0; i++) {
				if (m_food[i].read(foodListInFile)) {
					successFoodRead++;
				}
				else {
					failFoodRead = 1;
				}
			}

			if (successFoodRead != foodCount) {
				delete[] m_food;
				m_food = nullptr;
			}
			else {
				m_foodCount = successFoodRead;
			}

			if (successDrinkRead != drinkCount) {
				delete[] m_drink;
				m_drink = nullptr;
			}
			else {
				m_drinkCount = successDrinkRead;
			}
		}
	}

	Ordering::~Ordering()
	{
		delete[] m_food;
		m_food = nullptr;

		delete[] m_drink;
		m_drink = nullptr;

		for (unsigned int i = 0; i < m_billCount; i++) {
			delete m_items[i];
			m_items[i] = nullptr;
		}
	}

	Ordering::operator bool() const
	{
		if (m_food != nullptr && m_drink != nullptr) {
			return true;
		}

		return false;
	}

	int Ordering::noOfBillItems() const
	{
		return m_billCount;
	}

	bool Ordering::hasUnsavedBill() const
	{
		if (m_billCount > 0) {
			return true;
		}

		return false;
	}

	void Ordering::listFoods() const
	{
		cout << "List Of Avaiable Meals" << endl;
		cout << "========================================" << endl;

		for (unsigned int i = 0; i < m_foodCount; i++) {
			m_food[i].print();
			cout << endl;
		}

		cout << "========================================" << endl;
	}

	void Ordering::listDrinks() const
	{
		cout << "List Of Avaiable Drinks" << endl;
		cout << "========================================" << endl;

		for (unsigned int i = 0; i < m_drinkCount; i++) {
			m_drink[i].print();
			cout << endl;
		}

		cout << "========================================" << endl;
	}

	void Ordering::orderFood()
	{
		Menu menuFood("Food Menu", "Back to Order", 2);

		for (unsigned int i = 0; i < m_foodCount; i++) {
			menuFood << (const char*)m_food[i];
		}

		int selectedItem = menuFood.select();

		if (selectedItem != 0) {
			Food* selected = new Food(m_food[selectedItem - 1]); 

			if (selected->order()) {
				m_items[m_billCount++] = selected;
			}
			else {
				delete selected;
			}
		}
		// End of code generated from chatGPT
	}

	// Copied from orderFood above - changed food to drink
	void Ordering::orderDrink()
	{
		Menu menuDrinks("Drink Menu", "Back to Order", 2);

		for (unsigned int i = 0; i < m_drinkCount; i++) {
			menuDrinks << (const char*)m_drink[i];
		}

		int selectedItem = menuDrinks.select();

		if (selectedItem != 0) {
			Drink* selected = new Drink(m_drink[selectedItem - 1]);

			if (selected->order()) {
				m_items[m_billCount++] = selected;
			}
			else {
				delete selected;
			}
		}
	}

	std::ostream& Ordering::printBill(std::ostream& ostr) const
	{
		double totalBill = 0.0;

		printBillTitle(ostr);

		for (unsigned int i = 0; i < m_billCount; i++) {
			m_items[i]->print(ostr);
			ostr << endl;
			totalBill += m_items[i]->price();
		}

		printTotal(ostr, totalBill);

		return ostr;
	}

	void Ordering::resetBill()
	{
		char billFile[100]{};
		ut.makeBillFileName(billFile, m_billNumber);

		ofstream outputFile(billFile);
		if (outputFile) {
			printBill(outputFile); 

			cout << "Saved bill number " << m_billNumber << endl;
			cout << "Starting bill number " << (m_billNumber + 1) << endl;
		}

		for (unsigned int i = 0; i < m_billCount; ++i) {
			delete m_items[i];
			m_items[i] = nullptr;
		}

		m_billNumber++;
		m_billCount = 0;
	}
}