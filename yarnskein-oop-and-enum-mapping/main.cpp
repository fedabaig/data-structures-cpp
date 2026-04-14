/* Program name: YarnSkein.cpp
* Author: Feda Bigzad
* Date last updated: 11/2/2025
* Purpose: Implements the YarnSkein class following UML, with enums, static maps, and single fiber
*/

#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include <stdexcept>

using namespace std;

class YarnSkein {
public:
    // Enums
    enum fiberType { ACRYLIC, BAMBOO, COTTON, SILK, WOOL };
    enum weightType { LACE, SUPERFINE, FINE, MEDIUM, BULKY, SUPERBULKY, JUMBO, LIGHT };

    // Static maps
    static const map<fiberType, string> fiberToStr;
    static const map<string, fiberType> strToFiber;
    static const map<string, weightType> strToWeight;
    static const map<weightType, string> weightToStr;

private:
    double hookSize;
    double length;
    double needleSize;
    double skeinWeight;
    weightType strandWeight;
    fiberType fiber;        
    int numFiberType;       
    string color;

    // Private function to set fiber
    void setFiber(const string& fiberStr) {
        string f = fiberStr;
        f.erase(remove(f.begin(), f.end(), ' '), f.end()); // remove spaces
        transform(f.begin(), f.end(), f.begin(), ::toupper); // convert to uppercase

        auto it = strToFiber.find(f);
        if (it == strToFiber.end()) {
            throw invalid_argument("Invalid fiber type: " + fiberStr);
        }
        fiber = it->second;
        numFiberType = 1;
    }

public:
    // Constructor
    YarnSkein(string strandWeightStr, string color, double length, string fiberStr,
              double skeinWeight, double needleSize, double hookSize) {
        auto wIt = strToWeight.find(strandWeightStr);
        if (wIt == strToWeight.end())
            throw invalid_argument("Invalid strand weight: " + strandWeightStr);
        strandWeight = wIt->second;

        if (length <= 0 || skeinWeight <= 0 || needleSize <= 0 || hookSize <= 0)
            throw invalid_argument("Numeric values must be positive");

        this->length = length;
        this->skeinWeight = skeinWeight;
        this->needleSize = needleSize;
        this->hookSize = hookSize;
        this->color = color;

        setFiber(fiberStr);
    }

    // Copy constructor
    YarnSkein(const YarnSkein& other) {
        copyYarn(other);
    }

    // Destructor
    ~YarnSkein() {}

    // Assignment operator
    YarnSkein& operator=(const YarnSkein& other) {
        if (this != &other) copyYarn(other);
        return *this;
    }

    // Helper to copy data
    void copyYarn(const YarnSkein& other) {
        hookSize = other.hookSize;
        length = other.length;
        needleSize = other.needleSize;
        skeinWeight = other.skeinWeight;
        strandWeight = other.strandWeight;
        fiber = other.fiber;
        numFiberType = other.numFiberType;
        color = other.color;
    }

    // Getters
    double getHookSize() const { return hookSize; }
    double getLength() const { return length; }
    double getNeedleSize() const { return needleSize; }
    double getSkeinWeight() const { return skeinWeight; }
    int getStrandWeight() const { return strandWeight; }
    string getColor() const { return color; }
    string getFiberList() const { return fiberToStr.at(fiber); }
    string getStrandWeightName() const { return weightToStr.at(strandWeight); }

    // Setters
    void setColor(string c) { color = c; }
    void setLength(double l) { 
        if (l <= 0) throw invalid_argument("Length must be positive"); 
        length = l; 
    }
};

// Static maps initialization
const map<YarnSkein::fiberType, string> YarnSkein::fiberToStr = {
    {WOOL, "Wool"}, {ACRYLIC, "Acrylic"}, {COTTON, "Cotton"}, {BAMBOO, "Bamboo"}, {SILK, "Silk"}
};
const map<string, YarnSkein::fiberType> YarnSkein::strToFiber = {
    {"WOOL", WOOL}, {"ACRYLIC", ACRYLIC}, {"COTTON", COTTON}, {"BAMBOO", BAMBOO}, {"SILK", SILK}
};
const map<string, YarnSkein::weightType> YarnSkein::strToWeight = {
    {"Lace", LACE}, {"Super Fine", SUPERFINE}, {"Fine", FINE}, {"Medium", MEDIUM},
    {"Bulky", BULKY}, {"Super Bulky", SUPERBULKY}, {"Jumbo", JUMBO}, {"Light", LIGHT}
};
const map<YarnSkein::weightType, string> YarnSkein::weightToStr = {
    {LACE, "Lace"}, {SUPERFINE, "Super Fine"}, {FINE, "Fine"}, {MEDIUM, "Medium"},
    {BULKY, "Bulky"}, {SUPERBULKY, "Super Bulky"}, {JUMBO, "Jumbo"}, {LIGHT, "Light"}
};
