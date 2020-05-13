////////////////////////////////////
// Author:     Dr. Kooshesh       //
// Student:    Juan Martinez      //
// Term:       Fall 2017          //
// Course:     CS 315             //
// Assignment: Project 2          //
// Date:       9/28/17            //
// Professor:  Dr. Kooshesh       //
// File:       lex.hpp            //
////////////////////////////////////

#ifndef __LEX_HPP
#define __LEX_HPP

#include<iostream>

const int MAX_ATOM_LEN = 9;
enum tokens {LPAREN = '(', RPAREN = ')', ATOM, END_OF_TEXT};

void init_lex();
tokens get_token( char name[] );
void unget_token();

#endif
