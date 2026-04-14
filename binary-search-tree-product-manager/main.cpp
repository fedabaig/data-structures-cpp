/* Program name: main.cpp
 * Author: Feda Bigzad
 * Date last updated: 12/01/2025
 * Purpose: Read products from products.txt into a binary search tree,
 *          let the user search for a product or delete a product by
 *          product number, and print all products in-order when quitting.
 */

#include <iostream>
#include <fstream>
#include <limits>
#include <string>

#include "binarySearchTree.h"
#include "product.h"

int main()
{
    using std::cin;
    using std::cout;
    using std::endl;
    using std::string;

    binarySearchTree<product> productTree;

    // Load products from products.txt
    std::ifstream inFile("products.txt");
    if (!inFile)
    {
        std::cerr << "Could not open products.txt" << endl;
        return 1;
    }

    double price;
    string description;
    string prodNum;
    double rating;

    // File format:
    // price
    // description
    // product number
    // rating
    while (inFile >> price)
    {
        // clear the rest of the price line
        inFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::getline(inFile, description);
        std::getline(inFile, prodNum);
        inFile >> rating;
        inFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        product p(price, description, prodNum, rating);
        productTree.insert(p);
    }

    inFile.close();

    // menu loop
    bool done = false;

    while (!done)
    {
        cout << "\nMenu:\n";
        cout << "1. Search for a product\n";
        cout << "2. Delete product\n";
        cout << "3. Quit\n";
        cout << "Enter your choice: ";

        int choice;
        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear newline

        if (choice == 1)
        {
            // Search for a product
            string id;
            cout << "Enter product number to search (e.g., P010): ";
            std::getline(cin, id);

            // Create a key product with that ID.
            // price > 0 and rating >= 0 to avoid exceptions.
            product key(1.0, "", id, 0.0);

            // We can use search() from the BST and, if true, walk again to get the node data.
            // But we added find() in binarySearchTree for convenience.
            auto *found = productTree.find(key);

            if (found != nullptr)
            {
                cout << "\nProduct found:\n";
                cout << *found << endl;
            }
            else
            {
                cout << id << " is not found in the tree." << endl;
            }
        }
        else if (choice == 2)
        {
            //Delete a product
            string id;
            cout << "Enter product number to delete (e.g., P010): ";
            std::getline(cin, id);

            product key(1.0, "", id, 0.0);

            if (!productTree.search(key))
            {
                cout << id << " is not found in the tree. Nothing deleted.\n";
            }
            else
            {
                productTree.deleteNode(key);
                cout << "Product " << id << " has been deleted.\n";
            }
        }
        else if (choice == 3)
        {
            // Quit: do in order traversal before exiting 
            cout << "\nProducts in-order before exiting:\n\n";
            productTree.inorderTraversal();
            done = true;
        }
        else
        {
            cout << "Invalid choice. Please enter 1, 2, or 3.\n";
        }
    }

    return 0;
}
