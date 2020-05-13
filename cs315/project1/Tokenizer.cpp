////////////////////////////////////
// Author:     Juan Martinez      //
// Student:    Juan Martinez      //
// Term:       Fall 2017          //
// Course:     CS 315             //
// Assignment: Project 1          //
// Date:       9/8/17             //
// Professor:  Dr. Kooshesh       //
// File:       Tokenizer.cpp      //
////////////////////////////////////

#include "Tokenizer.h"
#include <sstream>

Tokenizer::Tokenizer(std::string expr) {
    expression = expr;
}

std::vector<Token* > & Tokenizer::tokenize() {

    std::string sym; //For any values from symbol map
    char cSym; //char value of sym
    std::istringstream strm;
    strm.str(expression);
    std::vector<std::string> stringexpr;
    std::string placeh;

    while(strm >> placeh)
      stringexpr.push_back(placeh); //stores in vector the items in expression, no spaces

    if (stringexpr[0] >= "a" && stringexpr[0] <= "z") { //Must begin with variable
        std::string letterVar = stringexpr[0];
        char variable = letterVar[0];
        tokens.push_back(new Token(variable));

        if (stringexpr[1] == "=") { //Second item must be an equal sign
            tokens.push_back(new Token('='));
        } else {
            std::cerr << "MUST HAVE EQUAL SIGN AFTER VARIABLE\n";
            exit(2);
        }
    }
    else {
        std::cerr << "MUST BEGIN WITH VARIABLE STARTING FROM a UNTIL z\n";
        exit(3);
    }

    for (int i = 2; unsigned(i) < stringexpr.size(); i++) { //add remaining items 
        if (stringexpr[i] == "+")
            tokens.push_back(new Token('+'));
        else if (stringexpr[i] == "-")
            tokens.push_back(new Token('-'));
        else if (stringexpr[i] == "*")
            tokens.push_back(new Token('*'));
        else if (stringexpr[i] == "/")
            tokens.push_back(new Token('/'));
        else if (stringexpr[i] == "%")
            tokens.push_back(new Token('%'));
        else if (stringexpr[i] == "(")
            tokens.push_back(new Token('('));
        else if (stringexpr[i] == ")")
            tokens.push_back(new Token(')'));
        else {
	  if (stringexpr[i] >= "a" && stringexpr[i] <= "z") { //add any variables used in expression
                sym = stringexpr[i];
                cSym = sym[0];
                tokens.push_back(new Token(cSym));
            } else
                tokens.push_back(new Token(stringexpr[i]));
        }
    }
    Token *token = new Token();
    token->eol(true);
    tokens.push_back(token);

    return tokens;
}
