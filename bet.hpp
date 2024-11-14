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

/*
void printInfixExpression() const;    // call the private vesrion of the printInfixExpression function
void printPostfixExpression() const;    // call the private version of the printPostfixExpression function
size_t size() const;  // return the number of nodes in the tree
size_t lead_nodes() const;    // return the numnber of leaf nodes in the tree
bool empty() const;
*/

//-----------------------------------------------
// =========== Private Member functions ==========
//-----------------------------------------------

#endif