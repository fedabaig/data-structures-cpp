/* Program name: hashTable.h
 * Author: Feda Bigzad
 * Date last updated: 12/13/2025
 * Purpose: Define two hash table classes:
 *          1) HashTableQP - open addressing with quadratic probing
 *          2) HashTableChaining - separate chaining with linked lists
 */

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <vector>
#include <list>
#include <cstddef>
#include <cstdlib>

// You can change this if you want a different table size.
const std::size_t DEFAULT_TABLE_SIZE = 2000003; // ~2 million, prime-ish

// ---------- Hash table with quadratic probing ----------
class HashTableQP
{
public:
    HashTableQP(std::size_t size = DEFAULT_TABLE_SIZE)
        : tableSize(size),
          table(size),
          occupied(size, false)
    {
    }

    // Insert a key into the table
    void insert(int key)
    {
        std::size_t h = hash(key);
        std::size_t i = 0;

        while (i < tableSize)
        {
            std::size_t idx = (h + i * i) % tableSize;
            if (!occupied[idx])
            {
                table[idx] = key;
                occupied[idx] = true;
                return;
            }
            else if (table[idx] == key)
            {
                // already in table, do nothing
                return;
            }
            ++i;
        }
        // If we get here, table is full – for this assignment we can ignore it
    }

    // Search for a key in the table
    bool search(int key) const
    {
        std::size_t h = hash(key);
        std::size_t i = 0;

        while (i < tableSize)
        {
            std::size_t idx = (h + i * i) % tableSize;

            if (!occupied[idx])
            {
                // Empty slot with no key ever placed here , not found
                return false;
            }
            if (table[idx] == key)
            {
                return true;
            }
            ++i;
        }
        return false;
    }

private:
    std::size_t tableSize;
    std::vector<int> table;
    std::vector<bool> occupied;

    std::size_t hash(int key) const
    {
        // Handle possible negative numbers: map to non-negative
        long long k = static_cast<long long>(key);
        if (k < 0) k = -k;
        return static_cast<std::size_t>(k) % tableSize;
    }
};


// ---------- Hash table with separate chaining ----------
class HashTableChaining
{
public:
    HashTableChaining(std::size_t size = DEFAULT_TABLE_SIZE)
        : tableSize(size),
          table(size)
    {
    }

    // Insert a key into the table
    void insert(int key)
    {
        std::size_t idx = hash(key);
        // Check if key already exists in this bucket
        for (int value : table[idx])
        {
            if (value == key)
                return; // already there
        }
        table[idx].push_back(key);
    }

    // Search for a key in the table
    bool search(int key) const
    {
        std::size_t idx = hash(key);
        for (int value : table[idx])
        {
            if (value == key)
                return true;
        }
        return false;
    }

private:
    std::size_t tableSize;
    std::vector<std::list<int>> table;

    std::size_t hash(int key) const
    {
        long long k = static_cast<long long>(key);
        if (k < 0) k = -k;
        return static_cast<std::size_t>(k) % tableSize;
    }
};

#endif 
