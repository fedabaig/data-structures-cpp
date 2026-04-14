/* Program name: url.h
 * Author: Feda Bigzad
 * Date last updated: 11/17/2025
 * Purpose: URL class that fetches a page and can show its file
 */
#ifndef URL_H
#define URL_H
#include <string>
#include <fstream>
#include <iostream>
#include "HTTPRequest.hpp"

class url {
public:
   
    // constructor
    url(std::string urlString, std::string filename);

    // display file contents, up to maxLines (-1 = all)
    void displayFile(int maxLines = -1) const;

private:
    std::string filename;
    std::string urlString;
};

#endif