
#include "snack.h"

snack::snack(std::string name, std::string locCode, double price, int quantity)
{
    this->name = name;
    this->locCode = locCode;
    this->price = price;
    this->quantity = quantity;
}

snack::snack(std::string locCode)
{
    name = "";
    price = 0;
    quantity = 0;
    setLocation(locCode);
}

void snack::setLocation(std::string locCode)
{
    this->locCode = locCode;
}

void snack::decreaseQuantity()
{
    quantity--;
}

int snack::getQuantity() const
{
    return quantity;
}

double snack::getPrice() const
{
    return price;
}

std::string snack::getLocation() const
{
    return locCode;
}

std::string snack::getName() const
{
    return name;
}

bool snack::operator<(const snack &rightOP) const
{
    return this->locCode < rightOP.locCode;
}

bool snack::operator>(const snack &rightOP) const
{
    return this->locCode > rightOP.locCode;
}

bool snack::operator<=(const snack &rightOP) const
{
    return this->locCode <= rightOP.locCode;
}

bool snack::operator>=(const snack &rightOP) const
{
    return this->locCode >= rightOP.locCode;
}

bool snack::operator==(const snack &rightOP) const
{
    return this->locCode == rightOP.locCode;
}

std::ostream &operator<<(std::ostream &outputStream, const snack &snackToOutput)
{
    outputStream << std::setprecision(2) << std::fixed << std::showpoint;
    outputStream << snackToOutput.name << " - " << snackToOutput.locCode << " $" << snackToOutput.price;
    return outputStream;
}
