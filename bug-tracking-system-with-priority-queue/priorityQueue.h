/* Program name: priorityQueue.h
 * Author: Feda Bigzad
 * Date last updated: 11/17/2025
 * Purpose: Priority queue class for bug reports
 */

#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <list>
#include <stdexcept>
#include "queueADT.h"

// Priority queue that keeps items in order by priority.
// Higher priority items go closer to the front.
template <class Type>
class PriorityQueue : public queueADT<Type>
{
public:
    // Default constructor
    PriorityQueue() = default;

    // Default destructor
    ~PriorityQueue() = default;

    // Check if the queue is empty
    bool isEmptyQueue() const override
    {
        return data.empty();
    }

    // This queue has no fixed size, so it is never full
    bool isFullQueue() const override
    {
        return false;
    }

    // Remove all items from the queue
    void initializeQueue() override
    {
        data.clear();
    }

    // Return the first item (highest priority in front)
    Type front() const override
    {
        if (isEmptyQueue())
        {
            throw std::out_of_range("Queue is empty.");
        }
        return data.front();
    }

    // Return the last item in the queue
    Type back() const override
    {
        if (isEmptyQueue())
        {
            throw std::out_of_range("Queue is empty.");
        }
        return data.back();
    }

    // Add a new item in the correct place by priority
    void enqueue(const Type &queueElement) override
    {
        // If empty, just add the item
        if (data.empty())
        {
            data.push_back(queueElement);
            return;
        }

        // Go through the list and find where to put the new item
        // Items with higher priority go closer to the front.
        // If the priority is the same, older items stay in front.
        auto it = data.begin();
        for (; it != data.end(); ++it)
        {
            if (queueElement > *it)
            {
                break;
            }
        }
        data.insert(it, queueElement);
    }

    // Remove and return the first item in the queue
    Type dequeue() override
    {
        if (isEmptyQueue())
        {
            throw std::out_of_range("Queue is empty.");
        }

        Type value = data.front();
        data.pop_front();
        return value;
    }

private:
    // List that stores the items in order
    std::list<Type> data;
};

#endif // PRIORITYQUEUE_H
