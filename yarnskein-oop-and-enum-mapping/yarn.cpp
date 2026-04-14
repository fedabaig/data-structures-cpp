#include "yarn.h"

Your class functions should be implemented here. Your static maps should be initialized here also. This helps keep your code organzied and makes it easier to maintain.

// trim helper function from https://stackoverflow.com/questions/1798112/removing-leading-and-trailing-spaces-from-a-string to help remove whitespace from comma separated string
std::string trim(const std::string &str,
                 const std::string &whitespace)
{
    const auto strBegin = str.find_first_not_of(whitespace);
    if (strBegin == std::string::npos)
        return ""; // no content

    const auto strEnd = str.find_last_not_of(whitespace);
    const auto strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}