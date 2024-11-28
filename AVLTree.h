#pragma once
#include <iostream>
#include <conio.h>

using namespace std;

class AVLTree;

class node
{
    int data;
    node *parent;
    node *left;
    node *right;
    friend class AVLTree;

public:
    node(int n)
    {
        data = n;
        parent = left = right = nullptr;
    }
};

class AVLTree
{
    node *root;
    void display(node *nodePtr)
    {
        if (nodePtr == nullptr)
        {
            return;
        }
        display(nodePtr->left);
        cout << nodePtr->data << " ";
        display(nodePtr->right);
    }
    node *findMin(node *nodePtr)
    {
        if (nodePtr)
        {
            if (nodePtr->left == nullptr)
            {
                return nodePtr;
            }
            return findMin(nodePtr->left);
        }
        return nullptr;
    }
    node *insert(node *nodePtr, int n)
    {
        if (nodePtr == nullptr)
        {
            nodePtr = new node(n);
            return nodePtr;
        }
        if (n < nodePtr->data)
        {
            node *ptr = insert(nodePtr->left, n);
            nodePtr->left = ptr;
            ptr->parent = nodePtr;
            return nodePtr;
        }
        if (n > nodePtr->data)
        {
            node *ptr = insert(nodePtr->right, n);
            nodePtr->right = ptr;
            ptr->parent = nodePtr;
            return nodePtr;
        }
        return nullptr;
    }
    node *searchNode(node *nodePtr, int n)
    {
        if (nodePtr == nullptr)
        {
            return nullptr;
        }
        if (nodePtr->data > n)
        {
            return searchNode(nodePtr->left, n);
        }
        if (nodePtr->data < n)
        {
            return searchNode(nodePtr->right, n);
        }
        else
        {
            return nodePtr;
        }
    }
    void deleteNode(node *del)
    {
        if (!del->left && !del->right)
        {
            if (!del->parent)
            {
                this->root = nullptr;
            }
            else
            {
                if (del->parent->right == del)
                {
                    del->parent->right = nullptr;
                }
                else
                {
                    del->parent->left = nullptr;
                }
            }
            delete del;
            return;
        }

        if (del->left && !del->right)
        {
            if (!del->parent)
            {
                this->root = del->left;
                del->left->parent = nullptr;
            }
            else if (del->parent->left == del)
            {
                del->parent->left = del->left;
                del->left->parent = del->parent;
            }
            else
            {
                del->parent->right = del->left;
                del->left->parent = del->parent;
            }
            delete del;
            return;
        }

        if (del->right && !del->left)
        {
            if (!del->parent)
            {
                this->root = del->right;
                del->right->parent = nullptr;
            }
            else if (del->parent->left == del)
            {
                del->parent->left = del->right;
                del->right->parent = del->parent;
            }
            else
            {
                del->parent->right = del->right;
                del->right->parent = del->parent;
            }
            delete del;
            return;
        }

        if (del->right && del->left)
        {
            node *temp = findMin(del->right);
            del->data = temp->data;
            deleteNode(temp);
        }
    }

public:
    AVLTree()
    {
        root = nullptr;
    }
    void insertNode(int n)
    {
        this->root = insert(this->root, n);
    }
    void deleteNode(int n)
    {
        node *del = searchNode(n);
        if (del)
        {
            deleteNode(del);
        }
    }
    node *searchNode(int n)
    {
        return searchNode(this->root, n);
    }
    int findMin()
    {
        node *nd = findMin(this->root);
        if (nd)
        {
            return nd->data;
        }
        return 0;
    }
    void display()
    {
        display(this->root);
    }
};
