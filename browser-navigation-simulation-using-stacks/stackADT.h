/* Program name: stackADT.h
 * Author: Feda Bigzad
 * Date last updated: 11/17/2025
 * Purpose: Stack abstract base class
 */

#ifndef STACKADT_H
#define STACKADT_H

template <class t>
class stackADT
{
public:
    virtual bool isEmptyStack() const = 0;
    virtual bool isFullStack() const = 0;
    virtual void initializeStack() = 0;
    virtual void push(const t &newItem) = 0;
    virtual t pop() = 0;
    virtual t top() const = 0;
    virtual ~stackADT() {}
};

#endif
