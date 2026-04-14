// Snack class by Angela Venable
#ifndef SNACK_H
#define SNACK_H

#include <string>
#include <iostream>
#include <iomanip>
class snack
{
public:
    snack(std::string name, std::string locCode, double price, int quantity);
    snack(std::string locCode);
    void setLocation(std::string);
    void decreaseQuantity();
    int getQuantity() const;
    double getPrice() const;
    std::string getLocation() const;
    std::string getName() const;
    bool operator<(const snack &rightOP) const;
    bool operator>(const snack &rightOP) const;
    bool operator<=(const snack &rightOP) const;
    bool operator>=(const snack &rightOP) const;
    bool operator==(const snack &rightOP) const;
    friend std::ostream &operator<<(std::ostream &outputStream, const snack &snackToOutput);

private:
    std::string name;
    std::string locCode;
    double price;
    int quantity;
};

#endif