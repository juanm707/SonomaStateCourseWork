////////////////////////////////////
// Author:     Dr. Kooshesh       //
// Student:    Juan Martinez      //
// Term:       Fall 2017          //
// Course:     CS 315             //
// Assignment: Project 1          //
// Date:       9/8/17             //
// Professor:  Dr. Kooshesh       //
// File:       TokenIterator.hpp  //
////////////////////////////////////

#ifndef __TokenIterator
#define __TokenIterator

#include<vector>
#include "Token.hpp"

class TokenIterator {  

public:
    TokenIterator( std::vector<Token *> &tokens, int n  );
    Token  *next();   // provides access to the next token. 
    void put_back();  // At times, we will have to look at the next token 
                      // to know if we can process it or it should be put
                      // back so that another entity would use it.

    void printProcessedTokens(); // Prints tokens in orders
    bool hasMoreTokens();  // Do we have at least one more token to dispense?
    ~TokenIterator();

private:
    std::vector<Token  *> tokens;
    int cur, numTokens;
};

#endif
