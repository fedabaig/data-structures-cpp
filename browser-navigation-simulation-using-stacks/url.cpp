/* Program name: url.cpp
 * Author: Feda Bigzad
 * Date last updated: 11/17/2025
 * Purpose: Implement URL fetch and display
 */

#include "url.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

// use the HTTP request library header from the starter code
#include "HTTPRequest.hpp"

url::url(std::string urlString, std::string filename)
    : filename(filename), urlString(urlString)
{
    try
    {
        http::Request request(urlString);
        const auto response = request.send("GET");

        std::string body(response.body.begin(), response.body.end());

        std::ofstream outFile(filename);
        if (!outFile)
        {
            throw std::runtime_error("Could not open output file.");
        }

        outFile << body;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error getting URL: " << e.what() << std::endl;
    }
}

// note the const here to match url.h
void url::displayFile(int maxLines) const
{
    std::ifstream inFile(filename);
    if (!inFile)
    {
        std::cout << "Could not open file: " << filename << std::endl;
        return;
    }

    std::string line;
    int lineCount = 0;

    while (std::getline(inFile, line))
    {
        std::cout << line << std::endl;

        if (maxLines >= 0)
        {
            ++lineCount;
            if (lineCount >= maxLines)
            {
                break;
            }
        }
    }
}
