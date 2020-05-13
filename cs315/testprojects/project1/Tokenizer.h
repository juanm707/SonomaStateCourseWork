////////////////////////////////////
// Author:     Juan Martinez      //
// Student:    Juan Martinez      //
// Term:       Fall 2017          //
// Course:     CS 315             //
// Assignment: Project 1          //
// Date:       9/8/17             //
// Professor:  Dr. Kooshesh       //
// File:       Tokenizer.h        //
////////////////////////////////////

#ifndef PROJECT1_TOKENIZER_H
#define PROJECT1_TOKENIZER_H

#include <string>
#include "Token.hpp"
#include "InfixToPostfix.hpp"
#include "TokenIterator.hpp"

class Tokenizer {

public:
    Tokenizer(std::string expr);

    // break up the string in "expression" into tokens and return them.
    std::vector<Token* > & tokenize();

private:
    std::string expression;
    std::vector<Token* > tokens;

};
#endif //PROJECT1_TOKENIZER_H
