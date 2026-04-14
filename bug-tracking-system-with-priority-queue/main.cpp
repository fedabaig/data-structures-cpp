/* Program name: main.cpp
 * Author: Feda Bigzad
 * Date last updated: 11/17/2025
 * Purpose: Bug tracking system using a priority queue
 */

#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <limits>
#include <sstream>

#include "BugReport.h"
#include "priorityQueue.h"

// Check if the date is in the form yyyy-mm-dd
// and the month and day are in a simple valid range.
bool isValidDate(const std::string &date)
{
    // First check the basic pattern
    std::regex pattern(R"(^\d{4}-\d{1,2}-\d{1,2}$)");
    if (!std::regex_match(date, pattern))
    {
        return false;
    }

    int year = 0;
    int month = 0;
    int day = 0;
    char dash1 = '-';
    char dash2 = '-';

    std::stringstream ss(date);
    ss >> year >> dash1 >> month >> dash2 >> day;

    if (!ss || dash1 != '-' || dash2 != '-')
    {
        return false;
    }

    if (month < 1 || month > 12)
    {
        return false;
    }

    if (day < 1 || day > 31)
    {
        return false;
    }

    return true;
}

// Read an integer from the user and make sure it is in a range
int getIntInRange(int minValue, int maxValue)
{
    int value;
    while (true)
    {
        if (std::cin >> value)
        {
            if (value >= minValue && value <= maxValue)
            {
                // Clear the rest of the line
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return value;
            }
        }

        // If input is bad, clear and ask again
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Please enter a number between " << minValue << " and " << maxValue << "." << std::endl;
    }
}

int main()
{
    // Priority queue for new bug reports
    PriorityQueue<BugReport> bugQueue;

    // List of finished bug reports
    std::vector<BugReport> finishedBugs;

    // Next bug id
    int nextId = 1;
    bool done = false;

    while (!done)
    {
        // Show menu
        std::cout << "Please choose from the following menu: " << std::endl;
        std::cout << "1. Enter Bug Report" << std::endl;
        std::cout << "2. Distribute Bug Report" << std::endl;
        std::cout << "3. Quit" << std::endl;
        std::cout << std::endl;

        int choice = getIntInRange(1, 3);

        if (choice == 1)
        {
            // Enter a new bug report
            std::string date;

            // Ask for date until it is valid
            while (true)
            {
                std::cout << "Enter the date of the report (yyyy-mm-dd): " << std::endl;
                std::getline(std::cin, date);

                if (isValidDate(date))
                {
                    break;
                }

                std::cout << "The date entered is not valid. Please check that the date entered is in the correct format." << std::endl;
            }

            std::string reporter;
            std::cout << "Enter the name of the reporter: " << std::endl;
            std::getline(std::cin, reporter);

            std::string description;
            std::cout << "Describe the bug: " << std::endl;
            std::getline(std::cin, description);

            std::cout << "What is the priority 1 - 10 (1 is low, 10 is high): " << std::endl;
            int priority = getIntInRange(1, 10);

            // New bug report starts with status "new"
            BugReport report(nextId, description, reporter, "new", priority, date);
            ++nextId;

            // Add to priority queue
            bugQueue.enqueue(report);
        }
        else if (choice == 2)
        {
            // Give the highest priority bug to a developer
            if (bugQueue.isEmptyQueue())
            {
                std::cout << "There are no bug reports in the queue." << std::endl;
                std::cout << std::endl;
            }
            else
            {
                // Take the first (highest priority) bug
                BugReport report = bugQueue.dequeue();
                report.setStatus("In Progress");

                std::cout << "Bug Report:" << std::endl;
                std::cout << report << std::endl;

                // Save it as a finished bug (later status will be changed to "Finished")
                finishedBugs.push_back(report);
            }
        }
        else if (choice == 3)
        {
            // Quit and show results
            std::cout << "Quitting: " << std::endl;
            std::cout << std::endl;

            std::cout << "List of Finished Bug Reports: " << std::endl;
            std::cout << std::endl;

            // Print all finished bug reports
            for (auto &report : finishedBugs)
            {
                report.setStatus("Finished");
                std::cout << report << std::endl;
            }

            std::cout << "List of Unfinished Bug Reports: " << std::endl;
            std::cout << std::endl;

            // Print all remaining bug reports in the queue
            while (!bugQueue.isEmptyQueue())
            {
                BugReport report = bugQueue.dequeue();
                // These still have status "new"
                std::cout << report << std::endl;
                std::cout << std::endl;
            }

            done = true;
        }
    }

    return 0;
}
