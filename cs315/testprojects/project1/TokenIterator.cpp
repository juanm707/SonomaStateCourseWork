////////////////////////////////////
// Author:     Dr. Kooshesh       //
// Student:    Juan Martinez      //
// Term:       Fall 2017          //
// Course:     CS 315             //
// Assignment: Project 1          //
// Date:       9/8/17             //
// Professor:  Dr. Kooshesh       //
// File:       TokenIterator.cpp  //
////////////////////////////////////

#include "TokenIterator.hpp"

TokenIterator::TokenIterator( std::vector<Token *> &tokens, int n  ) 
{
    this->tokens = tokens;
    numTokens = n;
    cur = 0;
}
    
TokenIterator::~TokenIterator()
{
    // Do not delete tokens as it is a borrowed pointer!
}
    
Token  *TokenIterator::next() 
{
    return hasMoreTokens() ? tokens.at(cur++) : nullptr;
}

void TokenIterator::put_back() 
{ 
    --cur; 
}

void TokenIterator::printProcessedTokens() 
{
    for( int i = 0; i < cur; i++ ) 
        tokens.at(i)->print();
}

bool TokenIterator::hasMoreTokens() 
{
    return cur != numTokens;
}
