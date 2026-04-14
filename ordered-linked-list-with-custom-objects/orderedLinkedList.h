/* Program name: orderedLinkedList.h
 * Author: Feda Bigzad
 * Date last updated: 11/10/2025
 * Purpose: A templated linked list that always keeps its items in order.
 */

#ifndef OLLIST_H
#define OLLIST_H

#include "linkedList.h"   // uses linkedList<Type> and node<Type>

// This class is a linked list that stays sorted.
// It uses the Type's comparison operators (<, ==, >) to decide the order.
template <class Type>
class orderedLinkedList : public linkedList<Type>
{
public:
    // Insert a new item into the list in the correct spot.
    void insert(const Type &newItem);

    // For an ordered list, adding at the front or end both just
    // mean "insert in order", so we call insert().
    virtual void insertFirst(const Type &newItem) override { insert(newItem); }
    virtual void insertLast(const Type &newItem) override { insert(newItem); }

    // Check if an item is in the list.
    virtual bool search(const Type &searchItem) const override;

    // Remove an item from the list if it is there.
    virtual void deleteNode(const Type &deleteItem) override;
};

// Insert newItem into the list so that the list stays sorted.
template <class Type>
void orderedLinkedList<Type>::insert(const Type &newItem)
{
    // Make a new node and store a copy of newItem in it.
    node<Type> *newNode = new node<Type>;
    newNode->info = new Type(newItem);
    newNode->link = nullptr;

    node<Type> *current = this->first;   // start at the first node
    node<Type> *trailCurrent = nullptr;  // node just behind current

    // Case 1: list is empty
    if (this->first == nullptr)
    {
        this->first = newNode;
        this->last = newNode;
        this->count = 1;
        return;
    }

    // Case 2: new item goes before the first node
    if (*(this->first->info) >= newItem)
    {
        newNode->link = this->first;
        this->first = newNode;
        this->count++;
        return;
    }

    // Case 3: find the place in the middle or at the end
    // Move forward until we find a node that is >= newItem,
    // or until we fall off the end (current == nullptr).
    while (current != nullptr && *(current->info) < newItem)
    {
        trailCurrent = current;
        current = current->link;
    }

    // Put newNode between trailCurrent and current.
    trailCurrent->link = newNode;
    newNode->link = current;

    // If current is nullptr, we added at the end, so update last.
    if (current == nullptr)
    {
        this->last = newNode;
    }

    this->count++;
}

// Look for searchItem in the list.
// Because the list is sorted, we can stop early if we go past it.
template <class Type>
bool orderedLinkedList<Type>::search(const Type &searchItem) const
{
    node<Type> *current = this->first;

    while (current != nullptr)
    {
        if (*(current->info) == searchItem)
        {
            return true;   // found it
        }
        else if (*(current->info) > searchItem)
        {
            // We passed where it should be in a sorted list.
            return false;
        }

        current = current->link;
    }

    return false;  // not in the list
}

// Delete the node that holds deleteItem, if it exists.
template <class Type>
void orderedLinkedList<Type>::deleteNode(const Type &deleteItem)
{
    if (this->first == nullptr)
    {
        std::cout << "Cannot delete from an empty list." << std::endl;
        return;
    }

    node<Type> *current = this->first;
    node<Type> *trailCurrent = nullptr;

    // Check if the first node is the one we want to delete.
    if (*(this->first->info) == deleteItem)
    {
        current = this->first;
        this->first = this->first->link;
        this->count--;

        // If the list is now empty, also reset last.
        if (this->first == nullptr)
            this->last = nullptr;

        delete current;   // node destructor will also delete info
        return;
    }

    // Otherwise, look through the rest of the list.
    bool found = false;
    while (current != nullptr && !found)
    {
        if (*(current->info) == deleteItem)
        {
            found = true;
        }
        else if (*(current->info) > deleteItem)
        {
            // We went past where it should be, so it's not here.
            break;
        }
        else
        {
            trailCurrent = current;
            current = current->link;
        }
    }

    if (found)
    {
        // current is the node we want to delete.
        trailCurrent->link = current->link;

        // If we deleted the last node, update last.
        if (current == this->last)
        {
            this->last = trailCurrent;
        }

        this->count--;
        delete current;
    }
    else
    {
        std::cout << "The item to be deleted is not in the list." << std::endl;
    }
}

#endif // OLLIST_H
