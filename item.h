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
		item(const char *,  int, float); // setup an item with a name
		item(const item &);
		item & operator=(const item &);
        item( char *);
		~item();
		void setName(const char *);
		void getName(char *) const;
		void setQuantity(int);
        int getQuantity() const;
		void setPrice(float); 
		float getPrice() const;
        int getWordLength() const;
        void printData();
	private:
		char * data;
		 int quantity;
		float price;
};
