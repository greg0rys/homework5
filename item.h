#pragma once
#include <iostream>
#include <cstring>
#include <cctype>
#include <fstream>

using namespace std;

class item
{
	public:
		item();
		item(const char *, unsigned int, float); // setup an item with a name
		item(const item &);
		item & operator=(const item &);
		~item();
		void setName(const char *);
		void getName(char *) const;
		void setQuantity(unsigned int);
		unsigned int getQuantity() const;
		void setPrice(float); 
		float getPrice() const;
	private:
		char * data;
		unsigned int quantity;
		float price;
};
