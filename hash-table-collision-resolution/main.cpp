/* Program name: main.cpp
 * Author: Feda Bigzad
 * Date last updated: 12/15/2025
 * Purpose: Read 1,000,000 numbers from nums.txt, insert them into two
 *          hash tables (quadratic probing and chaining), and let the
 *          user search for a value in both tables and compare speed.
 */

#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

#include "hashTable.h"

int main()
{
    using namespace std;
    using namespace std::chrono;

    HashTableQP qpTable;
    HashTableChaining chainTable;

    ifstream in("nums.txt");
    if (!in)
    {
        cerr << "Could not open nums.txt" << endl;
        return 1;
    }

    cout << "Reading numbers from nums.txt and inserting into hash tables...\n";

    int value;
    std::size_t count = 0;
    while (in >> value)
    {
        qpTable.insert(value);
        chainTable.insert(value);
        ++count;
    }
    in.close();

    cout << "Inserted " << count << " numbers into both hash tables.\n\n";

    int target;
    cout << "Enter a number to search for: ";
    cin >> target;
    cout << "\n";

    // --- Search in quadratic probing table ---
    auto startQP = high_resolution_clock::now();
    bool foundQP = qpTable.search(target);
    auto endQP = high_resolution_clock::now();
    auto timeQP = duration_cast<microseconds>(endQP - startQP).count();

    // --- Search in chaining table ---
    auto startCH = high_resolution_clock::now();
    bool foundCH = chainTable.search(target);
    auto endCH = high_resolution_clock::now();
    auto timeCH = duration_cast<microseconds>(endCH - startCH).count();

    cout << "Quadratic probing table:\n";
    cout << "  Found? " << (foundQP ? "Yes" : "No") << "\n";
    cout << "  Time:  " << timeQP << " microseconds\n\n";

    cout << "Chaining table:\n";
    cout << "  Found? " << (foundCH ? "Yes" : "No") << "\n";
    cout << "  Time:  " << timeCH << " microseconds\n\n";

    cout << "You can run the program a few times with different numbers\n"
         << "to see which table *feels* faster on your machine.\n";

    return 0;
}
