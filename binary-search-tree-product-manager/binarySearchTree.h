

/* Program name: binarySearchTree.h
 * Author: Feda Bigzad
 * Date last updated: 11/29/2025
 * Purpose: Binary search tree based on binaryTreeType, with search, insert,
 *          and delete functionality for objects like product.
 */


#ifndef SEARCH_H
#define SEARCH_H
#include "binaryTree.h"


// Binary Search Tree 
template <class elemType>
class binarySearchTree : public binaryTreeType<elemType>
{
public:
    // bring root into scope so we can use it
    using binaryTreeType<elemType>::root;

    // required overrides
    bool search(const elemType &searchItem) const override;
    void insert(const elemType &insertItem) override;
    void deleteNode(const elemType &deleteItem) override;

    // optional helper: returns pointer to stored item, or nullptr if not found
    elemType *find(const elemType &searchItem) const;

private:
    void deleteFromTree(nodeType<elemType> *&p);
};

//  Implementation 

template <class elemType>
bool binarySearchTree<elemType>::search(const elemType &searchItem) const
{
    nodeType<elemType> *current = root;

    while (current != nullptr)
    {
        if (*(current->info) == searchItem)
            return true;
        else if (*(current->info) > searchItem)
            current = current->lLink;
        else
            current = current->rLink;
    }

    return false;
}

template <class elemType>
elemType *binarySearchTree<elemType>::find(const elemType &searchItem) const
{
    nodeType<elemType> *current = root;

    while (current != nullptr)
    {
        if (*(current->info) == searchItem)
            return current->info; // pointer to stored object
        else if (*(current->info) > searchItem)
            current = current->lLink;
        else
            current = current->rLink;
    }

    return nullptr;
}

template <class elemType>
void binarySearchTree<elemType>::insert(const elemType &insertItem)
{
    // create a new node with a *copy* of insertItem on the heap
    nodeType<elemType> *newNode = new nodeType<elemType>;
    newNode->info = new elemType(insertItem);
    newNode->lLink = nullptr;
    newNode->rLink = nullptr;

    if (root == nullptr)
    {
        root = newNode;
        return;
    }

    nodeType<elemType> *current = root;
    nodeType<elemType> *trailCurrent = nullptr;

    while (current != nullptr)
    {
        trailCurrent = current;

        if (*(current->info) == insertItem)
        {
            // already in tree – ignore duplicate and free new node
            delete newNode->info;
            delete newNode;
            return;
        }
        else if (*(current->info) > insertItem)
        {
            current = current->lLink;
        }
        else
        {
            current = current->rLink;
        }
    }

    if (*(trailCurrent->info) > insertItem)
        trailCurrent->lLink = newNode;
    else
        trailCurrent->rLink = newNode;
}

template <class elemType>
void binarySearchTree<elemType>::deleteNode(const elemType &deleteItem)
{
    if (root == nullptr)
    {
        std::cout << "Cannot delete from an empty tree." << std::endl;
        return;
    }

    nodeType<elemType> *current = root;
    nodeType<elemType> *trailCurrent = nullptr;
    bool found = false;

    while (current != nullptr && !found)
    {
        if (*(current->info) == deleteItem)
        {
            found = true;
        }
        else
        {
            trailCurrent = current;
            if (*(current->info) > deleteItem)
                current = current->lLink;
            else
                current = current->rLink;
        }
    }

    if (!found)
    {
        std::cout << "Item is not found in the tree." << std::endl;
        return;
    }

    // current is the node to delete
    if (current == root)
        deleteFromTree(root);
    else if (*(trailCurrent->info) > deleteItem)
        deleteFromTree(trailCurrent->lLink);
    else
        deleteFromTree(trailCurrent->rLink);
}

template <class elemType>
void binarySearchTree<elemType>::deleteFromTree(nodeType<elemType> *&p)
{
    if (p == nullptr)
        return;

    // Case 1: no children
    if (p->lLink == nullptr && p->rLink == nullptr)
    {
        delete p;
        p = nullptr;
    }
    // Case 2: only right child
    else if (p->lLink == nullptr)
    {
        nodeType<elemType> *temp = p;
        p = p->rLink;
        delete temp;
    }
    // Case 3: only left child
    else if (p->rLink == nullptr)
    {
        nodeType<elemType> *temp = p;
        p = p->lLink;
        delete temp;
    }
    // Case 4: two children
    else
    {
        // find inorder predecessor (max in left subtree)
        nodeType<elemType> *current = p->lLink;
        nodeType<elemType> *trailCurrent = nullptr;

        while (current->rLink != nullptr)
        {
            trailCurrent = current;
            current = current->rLink;
        }

        // copy the value from predecessor node into p
        *(p->info) = *(current->info);

        // remove the predecessor node
        if (trailCurrent == nullptr) // predecessor is direct left child
            p->lLink = current->lLink;
        else
            trailCurrent->rLink = current->lLink;

        delete current;
    }
}

#endif 
