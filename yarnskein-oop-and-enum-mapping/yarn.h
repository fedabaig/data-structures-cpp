#ifndef YARN_H
#define YARN_H
#include <string>
#include <map>
#include <sstream>
#include <stdexcept>
#include <algorithm>

You should be using proper code organization.The class goes here.You will implement the methods(functions)
of the class in the yarn.cpp file.;

// helper function for removing leading and trailing whitespace from a string
std::string trim(const std::string &str,
                 const std::string &whitespace = " ");

#endif