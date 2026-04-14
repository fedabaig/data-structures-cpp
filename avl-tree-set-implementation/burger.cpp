/* Program name: burger.cpp
 * Author: Feda Bigzad
 * Date last updated: 12/08/2025
 * Purpose: Implement the burger class using a custom set of toppings.
 */

#include "burger.h"

burger::burger(int numPatties)
{
    setNumPatties(numPatties);
}

std::string burger::getToppings()
{
    // If there are no toppings, say "None"
    if (toppings.size() == 0)
    {
        return "None";
    }

    // Use the AVLTree iterator (via our set) to build the string
    set<toppingType>::Iterator it = toppings.begin();

    std::string result;
    if (it.hasNext())
    {
        toppingType first = it.next();
        result = toppingStr[first];
    }

    while (it.hasNext())
    {
        toppingType t = it.next();
        result += ", " + toppingStr[t];
    }

    return result;
}

void burger::addTopping(toppingType t)
{
    // If user chooses NOTOP, we don't need to add more
    if (t == NOTOP)
        return;

    toppings.insert(t);
}

void burger::setNumPatties(int num)
{
    if (num > 0)
        numPatties = num;
    else
    {
        std::cout << "The number of patties should be greater than 0." << std::endl;
        numPatties = 1;
    }
}

std::string burger::tostring()
{
    std::ostringstream out;
    out << std::setprecision(2) << std::fixed << std::showpoint;
    out << "Number of patties: " << numPatties << std::endl;
    out << "Toppings: " << getToppings();
    return out.str();
}
