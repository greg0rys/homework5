#include "item.h"

item::item()
{
	data = nullptr;
	quantity = 0;
	price = 0.00;

}
item::item(const char *name, unsigned int quantity, float price)
{
	if(data)
	{
		delete []data;
	}
	data = new char[strlen(name) + 1];
	strcpy(data,name);
	this->quantity = quantity;
	this->price = price;
}
item::item(const item &source)
{
	data = nullptr;
	*this = source;
}
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
item::~item()
{
	if(data)
	{
		delete []data;
	}
	data = nullptr;
}
