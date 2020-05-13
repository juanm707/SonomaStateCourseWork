//////////////////////////////////////////
// Author:     Dr. Kooshesh             //
// Student:    Juan Martinez            //
// Term:       Fall 2017                //
// Course:     CS 315                   //
// Assignment: Lab 02                   //
// Date:       9/25/17                  //
// Professor:  Dr. Kooshesh             //
// File:       isPal.hpp                //
//////////////////////////////////////////

#ifndef _isPal_hpp
#define _isPal_hpp

#include<iostream>
#include<cstdlib>

bool isPalIterative(const char *s, int n);
// s contains n characters. The function uses an iterative
// algorithm to determine if s contains a string that is a palindrome or
// not.

bool isPalRecursive(const char *s, int start, int n);
// s contains n characters. The function uses a recursive
// algorithm to determine if s contains a string that is a palindrome or
// not. When the function is called for the first time,  start will
// contain zero, the index of the first element of s.

#endif
