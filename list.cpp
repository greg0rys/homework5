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
    delete[] paramWord;
}

int list::getSize() const { return size; }

void list::printList() {
    node *curr;

    for (curr = index; curr; curr = curr->next) {
        curr->data->printData();
    }
}

// helper method of the list, used to get input from the user.
void list::updateNode() {
    // I want to get a menu number from the user
    // perform the delete associated with that menu number

    int option = -1;

    while(option != 0)
    {
        cout << "Please select an option " << endl;
        cout.width(15);
        cout << "1 - update item(s) by name " << endl;
        cout.width(15);
        cout << "2 - update item(s) by quantity" << endl;
        cout.width(15);
        cout << "3 - update item(s) by price " << endl;
        cin >> option;
        cin.ignore(101, '\n');

        switch(option)
        {
            case 1:
                updateByName(new char );
                break;
            case 2:
                updateByPrice();
                break;
            case 3:
                updateByQuantity();
                break;
            default:
                cout << option << " is not a valid choice, please try again " << endl;
                cin >> option;
                cin.ignore(101, '\n');

        }
    }
}
