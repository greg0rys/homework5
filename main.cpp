#include "main.h"

int main()
{
    // set the precision and format the floats and the start of the program
    // this way floating point numbers are shown with 2 digits after the deci
    cout.setf( std::ios::fixed, std:: ios::floatfield );
    cout.precision(2);
    cout << "Welcome to Shopping List Maintenance!" << endl;
    menu();
    exitMessage();
	return 0;
}


// get user input dynamically.
void getChars(char *& text)
{
    char * input = nullptr;
    char * temp = nullptr;
	int wordSize = 0;
	cout << "Enter an item name: ";

	while(cin.good() && cin.peek() != EOF)
	{
		char letter = cin.get();

		if(letter == '\n')
		{
			break;
		}

		if(!input)
		{
			input = new char[2];
			input[0] = letter;
            input[1] = '\0';
			wordSize = 1;
		}
		else
		{
			wordSize = strlen(input);
            // +2 so we can get the letter plus have enough space to append
            // cstrings null node terminator to the end.
            temp = new char[wordSize + 2]{0};
			strcpy(temp, input);
			delete []input;
			input = temp;
			input[wordSize] = letter;
            input[wordSize + 1] = '\0';
		}




	}


    // manager the pointer passed in, if it isn't null
    // delete it and make enough room for the users input
    // if it is null make it big enough for user input.
    if(!text)
    {
        text = new char[strlen(input) + 1];

    }
    else
    {
        delete []text;
        text = new char[strlen(temp) + 1];
    }
    // copy the users input into the passed in pointer.
    strcpy(text, input);
    // get rid of our dynamic input pointer.
    delete []input;


}

// menu of choice for the user.
//
int menu()
{
    int choice = 0;
    list itemList;
    item  * newItem = nullptr;

    while(choice != 7)
    {
        cout << endl;
        cout << "Please select from one of the following options: " << endl;
        cout << "1-\tQuit the program" << endl;
        cout << "2-\tErase all items from the list (resulting in an empty list)"
             << endl;
        cout << "3-\tAdd an item to the list" << endl;
        cout << "4-\tRemove an item from the list" << endl;
        cout << "5-\tUpdate an item in the list" << endl;

        cout << "6-\tDisplay all items in the list" << endl;
        cout << "Enter Option: ";
        cin >> choice;
        cout << endl;
        cin.ignore(101, '\n');

        // gaurd against bad user input.
        while(cin.fail())
        {
            cin.clear(); //clear input stream error state
            cin.ignore(101, '\n'); // throw out the bad input
            cout << "You have entered invalid input, please input a number "
                 << "choice" << endl;
            cout << "Enter Option: ";
            cin >> choice;
        }

        switch(choice)
        {
            case 1:
                choice = 7;
                break;
            case 2:
                itemList.eraseList();
                break;
            case 3:
                if(!newItem)
                {
                    newItem = new item();
                }
                getItemInfo(newItem);
                itemList.insertNode(*newItem);
                break;
            case 4:
                itemList.deleteNode();
                break;
            case 5:
                itemList.updateNode();
                break;
            case 6:
                itemList.printList();
                break;
            default:
                cout << "?Invalid choice!" << endl;
                break;
        }
    }
    choice = 0;
    if(newItem)
    {
        delete newItem;
    }
    return choice;
}

// get info to create a new item
void getItemInfo(item *&newItem)
{
    char * itemName = nullptr;
    float itemPrice = 0.00;
    int itemCount = 0;
    getChars(itemName);
    cout << "Enter a price for the item: ";
    cin >> itemPrice;
    cin.ignore(101, '\n');
    cout << "Enter a quantity for the item: ";
    cin >> itemCount;
    cin.ignore(101, '\n');
    while(cin.fail())
    {
        cin.clear(); //clear input stream error state
        cin.ignore(101, '\n'); // throw out the bad input
        cout << "You have entered invalid input" << endl;
        cout << "Enter a price and quantity for the item: ";
        cin >> itemPrice;
        cin.ignore(101, '\n');
        cout << "Enter a quantity for the item: ";
        cin >> itemCount;
        cin.ignore(101, '\n');

    }

    newItem->setName(itemName);
    newItem->setPrice(itemPrice);
    newItem->setQuantity(itemCount);
    delete []itemName;

}

// tell the user goodbye
void exitMessage()
{

    cout.width(50);
    cout.fill('*');
    cout << " Thank you! for using me ";
    cout.width(50);
    cout.fill('*');
    cout << " ";
    cout << endl << "[ done ]" << endl;
}
