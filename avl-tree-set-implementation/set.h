/* Program name: set.h
 * Author: Feda Bigzad
 * Date last updated: 12/08/2025
 * Purpose: Define a simple templated set class that stores unique items
 *          inside an AVLTree and provides an iterator for traversal.
 */

#ifndef SET_H
#define SET_H

#include "AVLTree.h"

template <class T>
class set
{
public:
    using Iterator = typename AVLTree<T>::Iterator;

    set() : itemCount(0) {}

    // Add an item to the set (no duplicates)
    void insert(const T &value)
    {
        // Only insert if it is not already in the tree
        if (!contains(value))
        {
            tree.insert(value);
            ++itemCount;
        }
    }

    // Check if an item is in the set
    bool contains(const T &value)
    {
        return tree.search(value);
    }

    // Number of items in the set
    int size() const
    {
        return itemCount;
    }

    bool empty() const
    {
        return itemCount == 0;
    }

    // Get an in-order iterator over the set
    Iterator begin()
    {
        return tree.begin();
    }

private:
    AVLTree<T> tree;
    int itemCount;
};

#endif
