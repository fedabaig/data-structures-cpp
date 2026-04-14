/* Program name: unorderedLinkedList.h
 * Author: Feda Bigzad
 * Date last updated: 11/24/2025
 * Purpose: Unordered linked list with merge sort using a comparison function pointer.
 */

#ifndef UNORDERED_H
#define UNORDERED_H

#include "linkedList.h"

template <class type>
class unorderedLinkedList : public linkedListType<type>
{
public:
    void insert(const type &newdata);
    void deleteNode(const type &deleteItem);
    bool search(const type &searchItem) const;

    // NEW: merge sort with comparison function
    void mergeSort(int (*func)(type &, type &));

private:
    // helpers for merge sort
    node<type> *mergeSortRec(node<type> *head, int (*func)(type &, type &));
    node<type> *mergeLists(node<type> *a, node<type> *b, int (*func)(type &, type &));
};

template <class type>
inline void unorderedLinkedList<type>::insert(const type &newdata)
{
    node<type> *newNode;
    newNode = new node<type>;
    newNode->data = new type(newdata);
    newNode->link = nullptr;

    if (this->isEmptyList())
    {
        this->head = newNode;
        this->tail = newNode;
        this->count++;
    }
    else
    {
        this->tail->link = newNode;
        this->tail = newNode;
        this->count++;
    }
}

template <class type>
inline void unorderedLinkedList<type>::deleteNode(const type &deleteItem)
{
    node<type> *current;
    node<type> *trailCurrent;
    bool found;
    if (this->isEmptyList())
        throw std::out_of_range("Cannot delete from empty list.");
    else
    {
        if (*(this->head->data) == deleteItem)
        {
            current = this->head;
            this->head = this->head->link;
            this->count--;
            if (this->head == nullptr)
                this->tail = nullptr;
            delete current;
        }
        else
        {
            found = false;
            trailCurrent = this->head;
            current = this->head->link;
            while (current != nullptr && !found)
            {
                if (*(current->data) != deleteItem)
                {
                    trailCurrent = current;
                    current = current->link;
                }
                else
                    found = true;
            }
            if (found)
            {
                trailCurrent->link = current->link;
                this->count--;
                if (this->tail == current)
                    this->tail = trailCurrent;
                delete current;
            }
            else
                throw std::out_of_range("Item not found in list. Cannot delete.");
        }
    }
}

template <class type>
inline bool unorderedLinkedList<type>::search(const type &searchItem) const
{
    node<type> *current;
    bool found = false;
    current = this->head;
    while (current != nullptr && !found)
    {
        if (*(current->data) == searchItem)
        {
            found = true;
        }
        else
        {
            current = current->link;
        }
    }
    return found;
}

// ======================= MERGE SORT PART =======================

template <class type>
void unorderedLinkedList<type>::mergeSort(int (*func)(type &, type &))
{
    if (this->head == nullptr || this->head->link == nullptr)
        return; // 0 or 1 element → already sorted

    this->head = mergeSortRec(this->head, func);

    // reset tail after sorting
    node<type> *current = this->head;
    while (current->link != nullptr)
        current = current->link;
    this->tail = current;
}

// recursive merge sort on node<type>* list
template <class type>
node<type> *unorderedLinkedList<type>::mergeSortRec(
    node<type> *head,
    int (*func)(type &, type &))
{
    if (head == nullptr || head->link == nullptr)
        return head;

    // split list into two halves (slow/fast pointer)
    node<type> *slow = head;
    node<type> *fast = head->link;

    while (fast != nullptr && fast->link != nullptr)
    {
        slow = slow->link;
        fast = fast->link->link;
    }

    node<type> *mid = slow->link;
    slow->link = nullptr; // cut in half

    node<type> *left = mergeSortRec(head, func);
    node<type> *right = mergeSortRec(mid, func);

    return mergeLists(left, right, func);
}

// merge two sorted lists using func (returns -1, 0, 1)
template <class type>
node<type> *unorderedLinkedList<type>::mergeLists(
    node<type> *a,
    node<type> *b,
    int (*func)(type &, type &))
{
    if (a == nullptr)
        return b;
    if (b == nullptr)
        return a;

    node<type> *result = nullptr;

    // remember: node stores pointers, so use *(a->data)
    if (func(*(a->data), *(b->data)) <= 0)
    {
        result = a;
        result->link = mergeLists(a->link, b, func);
    }
    else
    {
        result = b;
        result->link = mergeLists(a, b->link, func);
    }

    return result;
}

#endif
