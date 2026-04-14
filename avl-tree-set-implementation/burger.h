/* Program name: burger.h
 * Author: Feda Bigzad
 * Date last updated: 12/08/2025
 * Purpose: Define the burger class, which stores the number of patties and
 *          a set of toppings using a custom set class backed by an AVLTree.
 */

#pragma once
#include <string>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cctype>

#include "set.h"

const int TOP_NUM = 8;

enum toppingType
{
    GRILLONION,
    RAWONION,
    TOMATO,
    LETTUCE,
    BACON,
    MUSHROOM,
    PICKLE,
    NOTOP
};

const std::string toppingStr[] = {
    "Grilled Onion",
    "Raw Onion",
    "Tomato",
    "Lettuce",
    "Bacon",
    "Grilled Mushroom",
    "Pickle",
    "None"};

const toppingType toppingList[] = {
    GRILLONION,
    RAWONION,
    TOMATO,
    LETTUCE,
    BACON,
    MUSHROOM,
    PICKLE,
    NOTOP};

class burger
{
public:
    burger(int numPatties);

    // Turn all toppings in the set into a comma-separated string
    std::string getToppings();

    // Add a topping to the burger (uses our custom set)
    void addTopping(toppingType t);

    std::string tostring();

    void setNumPatties(int num);
    int getNumPatties() const { return numPatties; }

private:
    set<toppingType> toppings;  // custom set of toppings (AVLTree inside)
    int numPatties;
};
