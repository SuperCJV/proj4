#ifndef BET_H
#define BET_H

#include <iostream>
#include <string>
class BET {
    public:
        // Constructors and Destructors
        BET();  // default zero-parameter constructor
        BET(const std::string postfix);  // one-parameter constructor
        BET(const BET& rhs); //copy constructor
        ~BET(); // destructor

        // Public member functions
        bool buildFromPostfix(const std::string postfix);   // return true if the new tree is built successfully, false if error encountered
        const BET & operator=(const BET& rhs);   // assignment operator
        void printInfixExpression();    // call the private vesrion of the printInfixExpression function
        void printPostfixExpression();    // call the private version of the printPostfixExpression function
        size_t size();  // return the number of nodes in the tree
        size_t leaf_nodes();    // return the numnber of leaf nodes in the tree
        bool empty();   // return true if the tree is empty, false if otherwise

    private:
        struct BinaryNode{
            std::string element;
            BinaryNode* left;
            BinaryNode* right;
            BinaryNode(const std::string& el, BinaryNode* l = nullptr, BinaryNode* r = nullptr)
                : element(el), left(l), right(r) {}
        };
        BinaryNode* root;

        // Private Member Functions
        void printInfixExpression(BinaryNode *n);   // Print to the standard output the corresponding infix expression
        void makeEmpty(BinaryNode* &t); // delete all nodes in the subtree pointed to by t
        BinaryNode * clone(BinaryNode* t) const;  // clone all nores in the subtree pointed to by t
        void printPostfixExpression(BinaryNode *n); // print to the standard output the corresponsiding postfix expression
        size_t size(BinaryNode *t); // return the number of nodes in the subtree pointed to by t
        size_t leaf_nodes(BinaryNode *t);   // return the number of leaf nodes in the subtree pointed to by t
};
    
#include "bet.hpp"

#endif