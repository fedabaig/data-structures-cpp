/* Program name: main.cpp
 * Author: Feda Bigzad
 * Date last updated: 11/17/2025
 * Purpose: Simulate a web browser using stacks for back and forward
 */

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <limits>
#include "url.h"
#include "stack.h"

void resetStream();
void codeGradeLoopFix(std::string errLocation);

int main()
{
    std::ifstream navFile("navigation.txt");
    if (!navFile)
    {
        std::cout << "Could not open navigation.txt" << std::endl;
        return 1;
    }

    // Read first URL and file name in advance
    std::string nextUrlString;
    std::string nextFilename;
    bool hasMoreUrls = false;

    if (navFile >> nextUrlString >> nextFilename)
    {
        hasMoreUrls = true;
    }

    // Stacks for back and forward history
    stackType<url> backStack;
    stackType<url> forwardStack;

    // Current page (pointer so we do not need a default url constructor)
    url *current = nullptr;

    bool running = true;

    while (running)
    {
        std::cout << "What would you like to do?" << std::endl;

        if (hasMoreUrls)
        {
            std::cout << "1. Navigate to a new URL" << std::endl;
        }
        if (current != nullptr && !backStack.isEmptyStack())
        {
            std::cout << "2. Go Back to the previous URL" << std::endl;
        }
        if (current != nullptr && !forwardStack.isEmptyStack())
        {
            std::cout << "3. Go Forward to the next URL" << std::endl;
        }
        std::cout << "4. Exit Browser" << std::endl;

        int choice;
        if (!(std::cin >> choice))
        {
            if (std::cin.eof())
            {
                codeGradeLoopFix("menu choice");
                break;
            }
            resetStream();
            continue;
        }

        // clear the rest of the line
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice)
        {
        case 1:
            if (!hasMoreUrls)
            {
                std::cout << "No more URLs in the navigation file." << std::endl;
                break;
            }

            try
            {
                // move current page to back stack
                if (current != nullptr)
                {
                    backStack.push(*current);
                }

                // clear forward history
                forwardStack.initializeStack();

                // load new current page
                delete current;
                current = new url(nextUrlString, nextFilename);
                current->displayFile();

                // read next URL and filename for future
                if (navFile >> nextUrlString >> nextFilename)
                {
                    hasMoreUrls = true;
                }
                else
                {
                    hasMoreUrls = false;
                }
            }
            catch (const std::exception &e)
            {
                std::cout << "Error: " << e.what() << std::endl;
            }
            break;

        case 2:
            if (current == nullptr || backStack.isEmptyStack())
            {
                std::cout << "No previous URL to go back to." << std::endl;
                break;
            }

            try
            {
                // move current to forward stack
                forwardStack.push(*current);

                // pop from back stack to become current
                url previous = backStack.pop();

                delete current;
                current = new url(previous);
                current->displayFile();
            }
            catch (const std::exception &e)
            {
                std::cout << "Error: " << e.what() << std::endl;
            }
            break;

        case 3:
            if (current == nullptr || forwardStack.isEmptyStack())
            {
                std::cout << "No next URL to go forward to." << std::endl;
                break;
            }

            try
            {
                // move current to back stack
                backStack.push(*current);

                // pop from forward stack to become current
                url next = forwardStack.pop();

                delete current;
                current = new url(next);
                current->displayFile();
            }
            catch (const std::exception &e)
            {
                std::cout << "Error: " << e.what() << std::endl;
            }
            break;

        case 4:
            running = false;
            break;

        default:
            std::cout << "Please enter a valid option." << std::endl;
            break;
        }

        std::cout << std::endl;
    }

    delete current;
    return 0;
}

void resetStream()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "You did not enter a number." << std::endl;
}

void codeGradeLoopFix(std::string errLocation)
{
    if (std::cin.eof())
    {
        std::cout << "There was a problem and there is no more input! @" + errLocation << std::endl;
        throw std::invalid_argument(errLocation);
    }
}
