/* Program name: main.cpp
 * Author: Feda Bigzad
 * Date last updated: 12/08/2025
 * Purpose: Ask the user how many patties and which toppings they want on a
 *          burger, store toppings using a custom set (AVLTree), and display
 *          the final burger description.
 */

#include <iostream>
#include <string>
#include <limits>
#include <iomanip>
#include "burger.h"

void resetStream();
int promptNumPatties();
void promptToppings(toppingType top[], int &count);

int main()
{
    int pat = promptNumPatties();

    toppingType top[7];
    int topCount;
    promptToppings(top, topCount);

    burger myBurger(pat);

    // Add the chosen toppings to the burger's set
    for (int i = 0; i < topCount; ++i)
    {
        myBurger.addTopping(top[i]);
    }

    std::cout << std::endl;
    std::cout << myBurger.tostring() << std::endl;

    return 0;
}

void resetStream()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int promptNumPatties()
{
    int pat;
    std::cout << "How many patties do you want on your burger? ";
    std::cin >> pat;
    std::cout << std::endl;

    if (std::cin && pat > 0)
    {
        return pat;
    }
    else if (!std::cin)
    {
        resetStream();
    }

    std::cout << "You entered an invalid amount of patties. Please try again." << std::endl;
    return promptNumPatties();
}

void promptToppings(toppingType top[], int &count)
{
    int topInt;
    count = 0;

    for (int i = 0; i < 7; i++)
    {
        std::cout << "Please choose a topping from the list. Enter -1 to stop adding toppings." << std::endl;
        for (int j = 0; j < TOP_NUM; j++)
        {
            std::cout << j + 1 << ": " << toppingStr[j] << std::endl;
        }

        std::cin >> topInt;
        std::cout << std::endl;

        if (topInt == -1)
            break;

        while (!std::cin || topInt <= 0 || topInt > TOP_NUM)
        {
            if (!std::cin)
                resetStream();
            std::cout << "You did not choose a valid topping. Please try again." << std::endl;
            std::cin >> topInt;
            std::cout << std::endl;
        }

        top[count++] = toppingList[topInt - 1];

        // If user chose "None", stop asking for more toppings
        if (topInt == 8)
        {
            break;
        }
    }
}
