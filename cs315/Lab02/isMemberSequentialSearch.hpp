//////////////////////////////////////////////
// Author:     Dr. Kooshesh                 //
// Student:    Juan Martinez                //
// Term:       Fall 2017                    //
// Course:     CS 315                       //
// Assignment: Lab 02                       //
// Date:       9/25/17                      //
// Professor:  Dr. Kooshesh                 //
// File:       isMemberSequentialSearch.hpp //
//////////////////////////////////////////////

#ifndef _isMemberSequentialSearch_hpp
#define _isMemberSequentialSearch_hpp

#include<iostream>
#include<cstdlib>

bool isMemberSequentialSearchIterative(int list[], int n, int key);
// list contains n unordered elements. The function uses an iterative
// solution to determine if key is a member of the list or not. That is,
// it returns true if there is an i, 0 < i < n,
// and list[i] == key. Otherwise, the function returns false.

bool isMemberSequentialSearchRecursive(int list[], int n, int key);
// list contains n unordered elements. The function uses a recursive
// solution to determine if key is a member of the list or not. That is,
// it returns true if there is an i, 0 < i < n,
// and list[i] == key. Otherwise, the function returns false.

#endif
