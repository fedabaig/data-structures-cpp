/* Program name: main.cpp
 * Author: Feda Bigzad
 * Date last updated: 11/10/2025
 * Purpose: Read 5 snack objects, insert them into an ordered linked list,
 *          and display the list in sorted order before the program exits.
 */

#include <iostream>
#include <string>
#include "snack.h"
#include "orderedLinkedList.h"   // or "ollist.h" if that's what you named it

int main()
{
    using namespace std;

    // Make an ordered linked list that stores snacks.
    // The snacks will be ordered using snack's comparison operators
    // (your snack class compares by locCode).
    orderedLinkedList<snack> snackList;

    cout << "Enter 5 snacks in the format:\n";
    cout << "name locationCode price quantity\n";
    cout << "Example: Chips A1 1.50 10\n\n";

    // Read 5 snacks from the user (or from a file using input redirection).
    for (int i = 0; i < 5; ++i)
    {
        string name;
        string locCode;
        double price;
        int quantity;

        cout << "Snack " << (i + 1) << ": ";

        // Read one line of snack data
        if (!(cin >> name >> locCode >> price >> quantity))
        {
            cout << "Error reading input. Exiting.\n";
            return 1;
        }

        // Make a snack object with the data we just read
        snack s(name, locCode, price, quantity);

        // Insert it into the ordered list (it will go in the right position)
        snackList.insert(s);
    }

    // After all 5 snacks are inserted, print them in order.
    cout << "\nSnacks in order (by location code):\n";
    snackList.print(cout);   // linkedList::print uses snack::operator<< to print each snack

    return 0;
}
