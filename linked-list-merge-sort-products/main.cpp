/* Program name: main.cpp
 * Author: Feda Bigzad
 * Date last updated: 11/24/2025
 * Purpose: Read products from products.txt, put them into three linked lists,
 *          sort them by description, price, and rating using merge sort with
 *          function pointers, and display each sorted list.
 */

#include <iostream>
#include <fstream>
#include <limits>

#include "unorderedLinkedList.h"
#include "product.h"

int compareDescription(product &item1, product &item2);
int comparePrice(product &item1, product &item2);
int compareRating(product &item1, product &item2);

int main()
{
    // three lists with the same products
    unorderedLinkedList<product> listByPrice;
    unorderedLinkedList<product> listByDescription;
    unorderedLinkedList<product> listByRating;

    std::ifstream inFile("products.txt");
    if (!inFile)
    {
        std::cerr << "Could not open products.txt" << std::endl;
        return 1;
    }

    double price;
    std::string description;
    std::string prodNum;
    double rating;

    // File format per product:
    // line 1: price
    // line 2: description
    // line 3: product number
    // line 4: rating
    while (inFile >> price)
    {
        inFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear end of price line

        std::getline(inFile, description);
        std::getline(inFile, prodNum);
        inFile >> rating;
        inFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear end of rating line

        product p(price, description, prodNum, rating);

        listByPrice.insert(p);
        listByDescription.insert(p);
        listByRating.insert(p);
    }

    inFile.close();

    // print original lists
    std::cout << std::endl;
    std::cout << "Original list for ordering by description:" << std::endl;
    listByDescription.print(std::cout, "\n");
    std::cout << std::endl
              << std::endl;

    std::cout << "Original list for ordering by price:" << std::endl;
    listByPrice.print(std::cout, "\n");
    std::cout << std::endl
              << std::endl;

    std::cout << "Original list for ordering by rating:" << std::endl;
    listByRating.print(std::cout, "\n");
    std::cout << std::endl
              << std::endl;

    // sort the 3 lists
    listByDescription.mergeSort(compareDescription);
    listByPrice.mergeSort(comparePrice);
    listByRating.mergeSort(compareRating);

    std::cout << "Merge sorted by description product list:" << std::endl;
    listByDescription.print(std::cout, "\n");
    std::cout << std::endl
              << std::endl;

    std::cout << "Merge sorted by price product list:" << std::endl;
    listByPrice.print(std::cout, "\n");
    std::cout << std::endl
              << std::endl;

    std::cout << "Merge sorted by rating product list:" << std::endl;
    listByRating.print(std::cout, "\n");
    std::cout << std::endl
              << std::endl;

    return 0;
}

// ================== comparison functions ==================

int compareDescription(product &item1, product &item2)
{
    if (item1.getDescription() < item2.getDescription())
        return -1;
    else if (item1.getDescription() > item2.getDescription())
        return 1;
    else
        return 0;
}

int comparePrice(product &item1, product &item2)
{
    if (item1.getPrice() < item2.getPrice())
        return -1;
    else if (item1.getPrice() > item2.getPrice())
        return 1;
    else
        return 0;
}

int compareRating(product &item1, product &item2)
{
    if (item1.getRating() < item2.getRating())
        return -1;
    else if (item1.getRating() > item2.getRating())
        return 1;
    else
        return 0;
}
