#pragma once
#include "item.h"
#include "main.h"
#include <iostream>
#include <cstring>
#include <cctype>

using namespace std;

class list
{
private:

    struct node
    {
        //because our node has a pointer data member we MUST use constructors to allocate its data and deallocate at
        // deletion

        //default node constructor
        node(){
            data = nullptr;
            next = nullptr;
        }

        // set up a node with a given word object.
        node(const item &aItem) {

            data = new item(aItem);
            next = nullptr;
        }

        // deallocate all of this node memory when the node is destroyed.
        ~node(){
            if(data != nullptr)
            {
                delete data;
            }

            data = nullptr;
            next = nullptr;
        }

        item * data;
        node * next;

    };
    int size;
    node * index;
public:
    list(); // default constructor
    list(const list &); // copy constructor
    list &operator=(const list &); // overrode copy assignment operator
    ~list(); // list deconstructor
    void insertNode(item &); // insert a word into a sorted list.
    void printList(); // print our linked list
    int getSize() const; // get the size of this linked list.
	void updateNode(); // helper for the menu delete options.
    void updateByName(const char * name);
    void updateByQuantity();
    void updateByPrice();
	void deleteNode();
	void deleteByName(const char *);
	void deleteByQuantity();
	void deleteByPrice();
    void eraseList();
    void getTotalListCost();



};
