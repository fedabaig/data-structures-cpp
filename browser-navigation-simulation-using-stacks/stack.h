/* Program name: stack.h
 * Author: Feda Bigzad
 * Date last updated: 11/17/2025
 * Purpose: Template stack class with array storage
 */

#ifndef STACK_H
#define STACK_H
#include "stackADT.h"
#include <stdexcept>

template <class t>
class stackType : public stackADT<t>
{
public:
    static const int DEFAULT_STACK_SIZE = 100;

    // constructor with optional size
    stackType(int size = DEFAULT_STACK_SIZE);

    // copy constructor
    stackType(const stackType<t> &other);

    // destructor
    ~stackType();

    // assignment operator
    const stackType<t> &operator=(const stackType<t> &other);

    // check if stack is empty
    bool isEmptyStack() const override;

    // check if stack is full
    bool isFullStack() const override;

    // reset the stack
    void initializeStack() override;

    // add item to top
    void push(const t &newItem) override;

    // remove and return top item
    t pop() override;

    // return top item without removing
    t top() const override;

private:
    int count;
    int maxStackSize;
    t **list;

    // copy another stack into this one
    void copyStack(const stackType<t> &other);
};

template <class t>
stackType<t>::stackType(int size)
{
    if (size <= 0)
    {
        throw std::invalid_argument("Stack size must be positive.");
    }

    maxStackSize = size;
    count = 0;
    list = new t *[maxStackSize];
    for (int i = 0; i < maxStackSize; ++i)
    {
        list[i] = nullptr;
    }
}

template <class t>
stackType<t>::stackType(const stackType<t> &other)
{
    list = nullptr;
    maxStackSize = 0;
    count = 0;
    copyStack(other);
}

template <class t>
stackType<t>::~stackType()
{
    if (list != nullptr)
    {
        for (int i = 0; i < count; ++i)
        {
            delete list[i];
        }
        delete[] list;
    }
    list = nullptr;
    maxStackSize = 0;
    count = 0;
}

template <class t>
const stackType<t> &stackType<t>::operator=(const stackType<t> &other)
{
    if (this != &other)
    {
        copyStack(other);
    }
    return *this;
}

template <class t>
bool stackType<t>::isEmptyStack() const
{
    return (count == 0);
}

template <class t>
bool stackType<t>::isFullStack() const
{
    return (count == maxStackSize);
}

template <class t>
void stackType<t>::initializeStack()
{
    for (int i = 0; i < count; ++i)
    {
        delete list[i];
        list[i] = nullptr;
    }
    count = 0;
}

template <class t>
void stackType<t>::push(const t &newItem)
{
    if (isFullStack())
    {
        throw std::overflow_error("Stack is full.");
    }

    list[count] = new t(newItem);
    ++count;
}

template <class t>
t stackType<t>::pop()
{
    if (isEmptyStack())
    {
        throw std::underflow_error("Stack is empty.");
    }

    --count;
    t value = *(list[count]);
    delete list[count];
    list[count] = nullptr;
    return value;
}

template <class t>
t stackType<t>::top() const
{
    if (isEmptyStack())
    {
        throw std::underflow_error("Stack is empty.");
    }

    return *(list[count - 1]);
}

template <class t>
void stackType<t>::copyStack(const stackType<t> &other)
{
    if (this == &other)
    {
        return;
    }

    if (list != nullptr)
    {
        for (int i = 0; i < count; ++i)
        {
            delete list[i];
        }
        delete[] list;
    }

    maxStackSize = other.maxStackSize;
    count = other.count;

    list = new t *[maxStackSize];
    for (int i = 0; i < maxStackSize; ++i)
    {
        list[i] = nullptr;
    }

    for (int i = 0; i < count; ++i)
    {
        list[i] = new t(*(other.list[i]));
    }
}

#endif
