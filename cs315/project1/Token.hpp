////////////////////////////////////
// Author:     Dr. Kooshesh       //
// Student:    Juan Martinez      //
// Term:       Fall 2017          //
// Course:     CS 315             //
// Assignment: Project 1          //
// Date:       9/8/17             //
// Professor:  Dr. Kooshesh       //
// File:       Token.hpp          //
////////////////////////////////////

#include<iostream>
#include<string>

#ifndef TOKEN_HPP
#define TOKEN_HPP

/*

 This class represents the notion of a token; the building blocks of
 Roman expressions. In this context, a token either represents an
 operator (the addition, subtraction, multiplication, division, or
 modulo arithmetic operators), open or close parentheses, or a Roman
 number.

 Currently, it doesn't support variables (single lower-case letters.)
 You will have to add code for that purpose.

 To create a token, you can do the following:

 Token *tok = new Token('+'); // create a token to represent the addition op.

 or

 Token tok('+');

 On the other hand, for certain tokens, you will have to create a token 
 first and set it later.

 Token *tok = new Token();  // an uninitialize token
 tok->eof(true);            // make it represent EOF token.

*/


class Token {

public:
    Token() { init(); }
    Token(char c) { init(); _symbol = c; }
    Token(const std::string s) { init(); _romanNumber = s; }

    std::string romanNumber() const     { return _romanNumber; }
    void romanNumber( std::string str ) { _romanNumber = str; }

    bool eof() const { return _eof; }
    void eof(bool v) { _eof = v;    }

    bool eol() const { return _eol; }
    void eol(bool v) { _eol = v;    }

    bool isOpenParen() const  { return _symbol == '('; }
    bool isCloseParen() const { return _symbol == ')'; }

    bool isEqualSign() const              { return _symbol == '='; }
    bool isMultiplicationOperator() const { return _symbol == '*'; } 
    bool isAdditionOperator() const       { return _symbol == '+'; }
    bool isSubtractionOperator() const    { return _symbol == '-'; } 
    bool isModuloOperator() const         { return _symbol == '%'; } 
    bool isDivisionOperator() const       { return _symbol == '/'; } 
    bool isAVariable() const              { return _symbol >= 'a' && _symbol <= 'z'; } 
    char getVariable() const              { return _symbol; }

    bool isRomanNumber() const { return _romanNumber.length() > 0; } 

    void print() const;

private:
    void init() {
        _romanNumber = "";
        _eof = _eol = false; 
        _symbol = '\0';
    }

    std::string _romanNumber;
    bool _eof, _eol;
    char _symbol;
};

#endif
