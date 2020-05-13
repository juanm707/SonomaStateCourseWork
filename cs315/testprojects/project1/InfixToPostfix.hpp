////////////////////////////////////
// Author:     Dr. Kooshesh       //
// Student:    Juan Martinez      //
// Term:       Fall 2017          //
// Course:     CS 315             //
// Assignment: Project 1          //
// Date:       9/8/17             //
// Professor:  Dr. Kooshesh       //
// File:       InfixToPostfix.hpp //
////////////////////////////////////

#ifndef __InfxiToPostfix
#define __InfxiToPostfix

#include "Token.hpp"
#include "TokenIterator.hpp"
#include<vector>

class ExprNode {  // An expression tree node. 

public:
    ExprNode(Token *tk);
    ExprNode *&left();
    ExprNode *&right();
    Token *getToken();

private:
    ExprNode *_left, *_right;
    Token *token;
};

// Given an infix expression in a tokenized form, this class converts it
// to its corresponding postfix expression. 

// IMPORTANT: The input expression has to end with an EOL token.

class InfixToPostfix {
public:
    void convert( std::vector<Token *> &tokens, int numTokens, std::vector<Token *> &postfix);
    void print( ExprNode *root );

private:
    ExprNode *expr();
    ExprNode *term();
    ExprNode *primary();
    void flatten( ExprNode *root, std::vector<Token *> & );

    ExprNode *root;
    TokenIterator *lex;
    std::vector<Token *> tokens;
};

#endif

