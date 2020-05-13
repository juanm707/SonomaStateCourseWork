////////////////////////////////////
// Author:     Dr. Kooshesh       //
// Student:    Juan Martinez      //
// Term:       Fall 2017          //
// Course:     CS 315             //
// Assignment: Project 1          //
// Date:       9/8/17             //
// Professor:  Dr. Kooshesh       //
// File:       Token.cpp          //
////////////////////////////////////

#include "Token.hpp"

void Token::print() const {
    if( eol() ) std::cout << "EOL" ;
    else if( eof()                      )  std::cout << "EOF" ;
    else if( isOpenParen()              )  std::cout << "(" ;
    else if( isCloseParen()            )  std::cout << ")" ;
    else if( isEqualSign()              )  std::cout << " = " ;
    else if( isMultiplicationOperator() )  std::cout << " * " ;
    else if( isAdditionOperator()       )  std::cout << " + " ;
    else if( isSubtractionOperator()    )  std::cout << " - " ;
    else if( isModuloOperator()         )  std::cout << " / " ;
    else if( isDivisionOperator()       )  std::cout << " % " ;
    else if( isRomanNumber()            )  std::cout << " " << romanNumber() << " ";
    else if( isAVariable()              )  std::cout << " " << getVariable() << " ";
}
