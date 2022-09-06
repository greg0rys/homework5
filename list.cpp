#include "list.h"

// default constructor
list::list() {
    index = nullptr;
    size = 0;
}

// copy constructor
list::list(const list &master) {
    index = nullptr;
    *this = master;
}

// overloaded copy assignment operator
list &list::operator=(const list &master) {
    if (this == &master) {
        return *this;
    }

    if (index) {
        delete index;
    }

    if (master.index) {
		
        index = master.index;
    } else {
        index = nullptr;
    }
    size = master.size;

    return *this;
}

// list destructor
list::~list() {

    node *curr = index;
    while (curr) {
        index = curr->next;
        delete curr;
        curr = index;
    }
}

// maintain a sorted linked list
void list::insertNode(item &aItem) {

    node *newNode = nullptr;
    node *prevNode = nullptr;
    node *curr = index;
    char *headWord = nullptr;
    char *paramWord = new char[aItem.getWordLength() + 1];
    aItem.getName(paramWord);

    // case 1 - inserting into an empty list.
    if (curr == nullptr) {
        newNode = new node(aItem);
        index = newNode;
    } else {

        // case 2 inserting into an already occupied list.

        while (curr) {
            // allocate data for the index of the list word and get the word each
            // iteration
            if (headWord != nullptr) {
                delete[] headWord;
                headWord = new char[curr->data->getWordLength() + 1];
                curr->data->getName(headWord);
            } else {
                headWord = new char[curr->data->getWordLength() + 1];
                curr->data->getName(headWord);
            }

            // case 3 - the words are the same, don't add anything to the list.
            if (strcmp(headWord, paramWord) == 0) {
                // since we will return from this function delete the char pointers
                // as we will never reach the end for the deletion statements.
                delete[] headWord;
                delete[] paramWord;
                return; // word is a duplicate do nothing.
            }

            // case 4 - the words are the same length, insert them via ascii order
            if (strlen(headWord) == strlen(paramWord)) {
                if (strcmp(headWord, paramWord) > 0) {
                    break;
                }
            }

			// case 5 - insert a node alphabetically 
            if (strcmp(headWord,paramWord) > 0) {
                break;
            }

			// if none of the cases are true, check the new word against the
			// next word in the list. 
            prevNode = curr;
            curr = curr->next;
        }

        // insert at front of the list?
        if (curr == index) {
            newNode = new node(aItem);
            newNode->next = index;
            index = newNode;
        }
            // inserting else where in the list
        else {
            newNode = new node(aItem);
            newNode->next = curr;
            prevNode->next = newNode;
        }
    }

    size++;

    if (headWord) {
        delete[] headWord;
    }
    delete []paramWord;
}

int list::getSize() const { return size; }

/**
 * print all of the items in our list, along with lists size, and total cost.
 */
void list::printList() {
    node *curr;
    if(index == nullptr)
    {
        cout << "List is empty, nothing to print!" << endl;
        return;
    }

    for (curr = index; curr; curr = curr->next) {
        curr->data->printData();
    }

    getTotalListCost();
}

/**
 * director function -> calls proper update method.
 */
void list::updateNode() {

    int option = -1;
    char * nameSearch = nullptr;

    while(option != 0)
    {
        cout << "Enter a match criterion: 1 for name, 2 for qty, 3 for price: ";
        cin >> option;
        cin.ignore(101, '\n');
        while(cin.fail())
        {
            cin.clear(); //clear input stream error state
            cin.ignore(101, '\n'); // throw out the bad input
            cout << "You have entered invalid input, please input a number choice" << endl;
            cout << "Enter Option: ";
            cin >> option;
            cin.ignore(101, '\n');
        }

        switch(option)
        {
            case 1:
                getChars(nameSearch);
                updateByName(nameSearch);
                option = 0;
                break;
            case 2:
                updateByQuantity();
                option = 0;
                break;
            case 3:
                updateByPrice();
                option = 0;
                break;
            default:
                cout << option << " is not a valid choice, please try again: " << endl;
                break;

        }
    }

    if(nameSearch)
    {
        delete []nameSearch;
    }
}

/**
 * erase all the items in our list, once erased set index to null pointer
 * to guard against double delete at class destruction
 */
void list::eraseList()
{
    node * curr = index;
    while(curr)
    {
        node * temp = curr->next;
        delete curr;
        curr = temp;
    }

    //set the head pointer of our list to nullptr so when its destructor is called
    // curr will be null, so it won't delete twice.
    index = nullptr;
    cout << "Shopping list has been erased!" << endl;
}

// update an item by name.
void list::updateByName(const char *name)
{
    node * curr = index;
    char * itemName = nullptr;
    int counter = 0;
    bool found = false;

    if(!curr)
    {
        cout << "List is empty! Please add some items" << endl;
        return;
    }
    while(curr)
    {
        if(itemName)
        {
            delete []itemName;
        }

        itemName = new char[curr->data->getWordLength() + 1];
        curr->data->getName(itemName);

        if(strcmp(itemName, name) == 0)
        {
            getChars(itemName);
            curr->data->setName(itemName);
            counter++;
            found = true;
        }

        curr = curr->next;
    }

    if(found)
    {
        cout << counter << " items had their name changed to: " << itemName << endl;
    }

    if(itemName)
    {
        delete []itemName;
    }



}

// update all items by a given price point.
void list::updateByPrice()
{
    float searchprice = 0.00;
    float newPrice = 0.00;

    int counter = 0;
    bool found = false;
    node * curr = index;

    cout << "Enter a search price: ";
    cin >> searchprice;
    cin.ignore(101,'\n');
    cout << "Enter a new price for the item(s): ";
    cin >> newPrice;
    cin.ignore(101,'\n');

    // gaurd against invalid input, if there is an error throw all the input away and start over.
    while(cin.fail())
    {
        cin.clear(); //clear input stream error state
        cin.ignore(101, '\n'); // throw out the bad input
        cout << "You have entered invalid input, please enter a price like (25.97)" << endl;
        cout << "Enter a search price: ";
        cin >> searchprice;
        cin.ignore(101, '\n');
        cout << "Enter a new price for the item(s): ";
        cin >> newPrice;
        cin.ignore(101,'\n');
    }

    if(!curr)
    {
        cout << "List is empty! Please add some items" << endl;
        return;
    }
    while(curr)
    {
        if(curr->data->getPrice() == searchprice)
        {
            curr->data->setPrice(newPrice);
            counter++;
            found = true;
        }

        curr = curr->next;
    }

    if(found)
    {
        cout << counter << " items had their price changed to: $" << newPrice << endl;
    }

}

// search the list for a quantity, and then update all items that match that qty.
void list::updateByQuantity()
{
    int searchQuantity = 0;
    int newQuantity = 0;
    int counter = 0;
    bool found = false;
    node * curr = index;

    cout << "Enter a search quantity: ";
    cin >> searchQuantity;
    cin.ignore(101, '\n');
    cout << "Enter a new quantity for the item(s): ";
    cin >> newQuantity;
    cin.ignore(101,'\n');
    while(cin.fail())
    {
        cin.clear(); //clear input stream error state
        cin.ignore(101, '\n'); // throw out the bad input
        cout << "You have entered invalid input, please enter a whole quantity" << endl;
        cout << "Enter Quantity: ";
        cin >> searchQuantity;
        cin.ignore(101, '\n');
    }

    if(!curr)
    {
        cout << "List is empty! Please add some items" << endl;
        return;
    }

    while(curr)
    {
        if(curr->data->getQuantity() == searchQuantity)
        {
            curr->data->setQuantity(newQuantity);
            counter++;
            found = true;
        }

        curr = curr->next;
    }

    if(found)
    {
        cout << counter << " items had their quantity changed to: " << newQuantity << endl;
    }
}

void list::deleteNode() {
    cout << "Delete";
}

// print the total cost and size of the list.
void list::getTotalListCost()
{

    float total = 0.00;

    node * curr;
    for(curr = index; curr; curr = curr->next)
    {
        int qty = 0;
        float itemCost = 0.00;
        qty = curr->data->getQuantity();
        itemCost = curr->data->getPrice();

        total += itemCost * qty;
    }

    cout << endl;
    cout << "list has " << size << " items with a total of: $" << total << endl;


}