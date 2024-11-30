#pragma once
#include <iostream>
#include <conio.h>

using namespace std;

class AVLTree;

class node
{
    int data;
    short height;
    node *parent;
    node *left;
    node *right;
    int calculateHeight(node *nodePtr)
    {
        if (!nodePtr)
            return -1;
        int leftHeight = calculateHeight(nodePtr->left);
        int rightHeight = calculateHeight(nodePtr->right);
        return 1 + max(leftHeight, rightHeight);
    }
    int getBalance(node *nodePtr)
    {
        return calculateHeight(nodePtr->left) - calculateHeight(nodePtr->right);
    }
    friend class AVLTree;

public:
    node(int n)
    {
        data = n;
        parent = left = right = nullptr;
    }
    int calculateHeight()
    {
        this->height = calculateHeight(this);
        return this->height;
    }
    int getBalance()
    {
        return getBalance(this);
    }
};

class AVLTree
{
    node *root;
    // Helper function to visualize the tree
    void printTree(node *root, int space = 0, int levelSpace = 5)
    {
        if (root == nullptr)
            return;

        // Increase distance between levels
        space += levelSpace;

        // Print right child first
        printTree(root->right, space);

        // Print current node after spaces
        cout << endl;
        for (int i = levelSpace; i < space; i++)
            cout << " ";
        cout << root->data;

        // Print left child
        printTree(root->left, space);
    }
    void displayPreOrder(node *nodePtr)
    {
        if (nodePtr == nullptr)
        {
            return;
        }
        cout << nodePtr->data << " ";
        displayPreOrder(nodePtr->left);
        displayPreOrder(nodePtr->right);
    }
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
    int height(node *nodePTr)
    {
        if (nodePTr == nullptr)
            return -1;
        return 1 + max(height(nodePTr->right), height(nodePTr->left));
    }

    node *rotateRR(node *nodePtr)
    {
        node *x = nodePtr->right;
        node *y = x->left;

        x->left = nodePtr;
        nodePtr->right = y;

        x->parent = nodePtr->parent;
        nodePtr->parent = x;
        if (y)
            y->parent = nodePtr;

        x->height = 1 + max(height(x->left), height(x->right));
        nodePtr->height = 1 + max(height(nodePtr->left), height(nodePtr->right));
        // x->calculateHeight();

        return x;
    }
    node *rotateLL(node *nodePtr)
    {
        node *x = nodePtr->left;
        node *y = x->right;

        x->right = nodePtr;
        nodePtr->left = y;

        x->parent = nodePtr->parent;
        nodePtr->parent = x;
        if (y)
            y->parent = nodePtr;

        x->height = 1 + max(height(x->left), height(x->right));
        nodePtr->height = 1 + max(height(nodePtr->left), height(nodePtr->right));

        return x;
    }
    node *rotateRL(node *nodePtr)
    {
        nodePtr->right = rotateLL(nodePtr->right);
        return rotateRR(nodePtr);
    }
    node *rotateLR(node *nodePtr)
    {
        nodePtr->left = rotateRR(nodePtr->left);
        return rotateLL(nodePtr);
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
            // if(nodePtr->left->calculateHeight() - nodePtr->right->calculateHeight())
            // return nodePtr;
        }
        else if (n > nodePtr->data)
        {
            node *ptr = insert(nodePtr->right, n);
            nodePtr->right = ptr;
            ptr->parent = nodePtr;
            // return nodePtr;
        }
        else
        {
            return nodePtr;
        }

        int balance = nodePtr->getBalance();

        if (balance > 1 && n < nodePtr->left->data) // Left Left Case
        {
            return rotateLL(nodePtr);
        }
        if (balance < -1 && n > nodePtr->right->data) // Right Right Case
        {
            return rotateRR(nodePtr);
        }
        if (balance > 1 && n > nodePtr->left->data) // Left Right Case
        {
            return rotateLR(nodePtr);
        }
        if (balance < -1 && n < nodePtr->right->data) // Right Left Case
        {
            return rotateRL(nodePtr);
        }

        return nodePtr;
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
    void printTree()
    {
        printTree(this->root);
    }
    void displayPreOrder()
    {
        displayPreOrder(this->root);
    }
};
