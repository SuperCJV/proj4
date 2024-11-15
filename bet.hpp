#ifndef BET_HPP
#define BET_HPP

#include <iostream>
#include <stack>
#include <sstream>

#include "bet.h"

using namespace std;

//----------------------------------------
// ====== Constructors & Destructors =====
//----------------------------------------

// Default zero-parameter constructor
BET::BET() : root(nullptr) {}   

// One-parameter constructor
// Parameter "postfix" is string containing a postfix expression
// The tree should be built based on the postfix expression
// Tokens in the postfix expression are separated by space
BET::BET(const std::string postfix) : root(nullptr) {
    buildFromPostfix(postfix);
}

// Copy constructor
BET::BET(const BET& rhs) : root(clone(rhs.root)){}

// Destructor
BET::~BET(){
    makeEmpty(root);
}

//-----------------------------------------------
// =========== Public Member functions ==========
//-----------------------------------------------

bool BET::buildFromPostfix(const string postfix)   // return true if the new tree is built successfully, false if error encountered
{
    makeEmpty(root);    // clear existing tree
    stack<BinaryNode*> s;   // operand stack
    istringstream tokens(postfix);  // extracts tokens one at a time
    string token;

    while(tokens >> token){
        if(token == "+" || token == "-" || token == "*" || token == "/"){  // if its an operator...
            if(s.size() < 2){   // ensure there are at least 2 nodes in the stack
                return false;
            }
            // Pop the two nodes, right and left, from the stack
            BinaryNode* right = s.top();    
            s.pop();
            BinaryNode* left = s.top();
            s.pop();

            s.push(new BinaryNode(token, left, right)); // Create a new node for the operator with the two nodes as its children and push into stack
        } else {
            s.push(new BinaryNode(token));  // if its an operand, push it into the stack
        }
    }
    if (s.size() != 1){
        return false;   // return false for invalid postfix expression
    }
    root = s.top(); // set root to the final node in the stack

    return true;
}

const BET& BET::operator=(const BET& rhs)   // assignment operator
{
    if(this != &rhs){
        makeEmpty(root);
        root = clone(rhs.root);
    }
    return *this;
}

void BET::printInfixExpression()    // call the private vesrion of the printInfixExpression function
{
    if(root){
        printInfixExpression(root);
    }
    cout<<"\n";
}

void BET::printPostfixExpression()    // call the private version of the printPostfixExpression function
{
    if(root){
        printPostfixExpression(root);
    }
    cout<<"\n";
}

size_t BET::size() // return the number of nodes in the tree
{
    return size(root);
}


size_t BET::leaf_nodes() // return the numnber of leaf nodes in the tree
{
    return leaf_nodes(root);
}

bool BET::empty()
{
    return root == nullptr;
}

//-----------------------------------------------
// =========== Private Member functions ==========
//-----------------------------------------------

void BET::printInfixExpression(BinaryNode *n)   // Print to the standard output the corresponding infix expression
{
    if(!n){
        return;
    }
    if(n->left && n-> right){
        cout<<"(";
    }

    printInfixExpression(n->left);
    cout<<n->element;
    printInfixExpression(n->right);
    
    if(n->left && n->right){
        cout<<")";
    }
}

void BET::makeEmpty(BinaryNode* &t) // delete all nodes in the subtree pointed to by t
{
    if(t){
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
        t = nullptr;
    }
}

BET::BinaryNode* BET::clone(BinaryNode* t) const  // clone all nores in the subtree pointed to by t
{
    if(!t){
        return nullptr;
    }
    return new BinaryNode(t->element, clone(t->left), clone(t->right));
}

void BET::printPostfixExpression(BinaryNode *n) // print to the standard output the corresponsiding postfix expression
{
    if(!n){
        return;
    }

    printPostfixExpression(n->left);
    printPostfixExpression(n->right);
    cout<<n->element<<" ";
}

size_t BET::size(BinaryNode *t) // return the number of nodes in the subtree pointed to by t
{
    if(!t){
        return 0;
    }
    return 1 + size(t->left) + size(t->right);
}

size_t BET::leaf_nodes(BinaryNode *t)   // return the number of leaf nodes in the subtree pointed to by t
{
    if(!t){
        return 0;
    }
    if(!t->left && !t->right){
        return 1;
    }
    return leaf_nodes(t->left) + leaf_nodes(t->right);
}

#endif