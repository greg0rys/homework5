#include "item.h"

// default constructor
item::item()
{
	data = nullptr;
	quantity = 0;
	price = 0.00;

}

item::item(char * name)
{
    data = new char[strlen(name) + 1]{0};
    strcpy(data, name);
    quantity = 0;
    price = 0.00;

}

// custom constructor
item::item(const char *name,  int quantity, float price)
{
	this->data = new char[strlen(name) + 1];
	strcpy(data,name);
	this->quantity = quantity;
	this->price = price;
}

//copy constructor
item::item(const item &source)
{
	data = nullptr;
	*this = source;
}

//overloaded assignment operator
item&item::operator=(const item &source)
{
	if(this == &source)
	{
		return *this;
	}

	if(data)
	{
		delete []data;
	}
	if(source.data != nullptr)
	{
		data = new char[strlen(source.data) + 1];
		strcpy(data, source.data);
	}
	else
	{
		data = nullptr;
	}
	quantity = source.quantity;
	price = source.price;
	return *this;
}

// destructor
item::~item()
{
	if(data)
	{
		delete []data;
	}
	data = nullptr;
}

void item::setName( char *name)
{
    if(data)
    {
        delete []data;
    }
    // upcase the first letter of all the items in our list.
    name[0] = toupper(name[0]);

    data = new char[strlen(name) + 1];
    strcpy(data, name);
}

void item::getName(char * name) const
{
    // make sure that the param isn't null, if it is make it big enough.
    if(!name)
    {
        name = new char[strlen(data) + 1];
    }

    strcpy(name, data);
}

void item::setQuantity(int num)
{
    quantity = num;
}

 int item::getQuantity() const
{
    return quantity;
}

void item::setPrice(float cost)
{
    price = cost;
}

float item::getPrice() const
{
    return price;
}

int item::getWordLength() const
{
    return strlen(data);
}

void item::printData()
{

    cout << endl;
    cout  << data << " (" << quantity
    << " at " <<
    "$" << price
    << ") Total Cost: $";
    cout  <<
    (price *
    quantity)  << endl;
}
