/* Program name: main.cpp
 * Author: Feda Bigzad
 * Date last updated: 11/09/2025
 * Purpose: Use regular expressions to read times from the user, validate them,
 *          create clockType objects, store them in a vector, and display all
 *          valid times when the user types 'quit'.
 */

#include <iostream>   
#include <string>   
#include <vector>     
#include <regex>      
#include "clock.h"    

int main()
{
    using namespace std;

    
    regex timeRegex(R"(^\d{1,2}:\d{2}(:\d{2})?( [AaPp][Mm])?$)");

    // Vector to store all valid clockType objects entered by the user.
    vector<clockType> times;

    // String to hold each line of user input.
    string input;

    // Main input loop: runs until the user types "quit" or input fails.
    while (true)
    {
        cout << "Enter a time (or 'quit' to finish): ";

        // Read a whole line from the user (e.g., "11:30 PM")
        if (!getline(cin, input))
        {
            // If reading fails (EOF or input error), exit the loop.
            break;
        }

        // If the user types exactly "quit", stop asking for more times.
        if (input == "quit")
        {
            break;
        }

        // First step: validate the *format* using the regular expression.
        // If this fails, the string does not look like any allowed time format.
        if (!regex_match(input, timeRegex))
        {
            cout << "Invalid time format. Please try again.\n";
            continue;   // Go back to the top of the loop and ask again.
        }

       
        string timePart = input;  // Will hold "h:mm" or "h:mm:ss"
        string ampmPart = "";     // Will hold "AM" or "PM" if present

        // Look for a space that separates the time from the AM/PM part.
        size_t spacePos = input.find(' ');
        if (spacePos != string::npos)
        {
            // Everything before the space is the time portion.
            timePart = input.substr(0, spacePos);

            // Everything after the space is the AM/PM portion.
            ampmPart = input.substr(spacePos + 1);
        }

        // Now we parse hour, minute, and second from timePart manually.
        int hour   = 0;
        int minute = 0;
        int second = 0;

        // Find the first colon in timePart.
        size_t firstColon = timePart.find(':');
        // Try to find a second colon *after* the first one.
        size_t secondColon = timePart.find(':', firstColon + 1);

        // The substring before the first colon is the hour.
        hour = stoi(timePart.substr(0, firstColon));

        if (secondColon == string::npos)
        {
            // Format: h:mm (no seconds)
            // The substring after the first colon is the minute.
            minute = stoi(timePart.substr(firstColon + 1));
        }
        else
        {
            // Format: h:mm:ss
            // From firstColon+1 up to secondColon-1 is the minute.
            minute = stoi(timePart.substr(firstColon + 1, secondColon - firstColon - 1));
            // The substring after the second colon is the second.
            second = stoi(timePart.substr(secondColon + 1));
        }

        /*
            Determine whether this is a 12-hour or 24-hour clock.

            - If an AM/PM part is present → 12-hour clock.
            - If there is no AM/PM → 24-hour clock.

            We also set timeOfDay (AM or PM) when needed.
        */
        hourType type;
        amPmType tod = AM;  // Default value; will be changed if PM is detected.

        if (!ampmPart.empty())
        {
            // We have some kind of AM/PM, so this is a 12-hour clock.
            type = TWELVE;

            // Check if string is one of the PM variants (case-insensitive by hand).
            if (ampmPart == "PM" || ampmPart == "pm" ||
                ampmPart == "Pm" || ampmPart == "pM")
            {
                tod = PM;
            }
            else
            {
                tod = AM;
            }
        }
        else
        {
            // No AM/PM part means this is a 24-hour clock.
            type = TWENTYFOUR;
        }

        /*
            Now we let clockType validate the numeric ranges for us.
            - setHour may throw hourException
            - setMinute may throw minuteException
            - setSecond may throw secondException

            If the values are valid, we store the clock in the vector.
        */
        try
        {
            // Construct a clockType object with the parsed values.
            clockType clk(hour, minute, second, type, tod);

            // Add this valid clock to the vector.
            times.push_back(clk);

            // Print feedback to the user using operator<< defined in clock.cpp.
            cout << "Time accepted: " << clk;
        }
        catch (hourException &e)
        {
            cout << e.what() << '\n';
        }
        catch (minuteException &e)
        {
            cout << e.what() << '\n';
        }
        catch (secondException &e)
        {
            cout << e.what() << '\n';
        }
    }

    /*
        When the user types "quit" (or input ends), we exit the loop.
        Now we display all valid times that were collected in the vector.
    */
    if (!times.empty())
    {
        cout << "\nValid times entered:\n";
        for (const auto &t : times)
        {
            // This uses the operator<< overload for clockType.
            cout << t;
        }
    }
    else
    {
        cout << "\nNo valid times were entered.\n";
    }

    return 0;   // Indicate successful program completion.
};
