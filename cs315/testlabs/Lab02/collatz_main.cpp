////////////////////////////////////
// Author:     Juan Martinez      //
// Student:    Juan Martinez      //
// Term:       Fall 2017          //
// Course:     CS 315             //
// Assignment: Lab 02             //
// Date:       9/25/17            //
// Professor:  Dr. Kooshesh       //
// File:       collatz_main.cpp   //
////////////////////////////////////

#include <iostream>
#include "collatz.hpp"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

int main () {

  srand (time(NULL));

  int collatzNum = rand() % 1000 + 1; //random number between 1 and 1000
  std::cout << "Iterative Collatz sequence of " << collatzNum << " is: ";
  collatzIterative(collatzNum);

  std::cout << std::endl;
  
  std::cout << "Recursive Collatz sequence of " << collatzNum << " is: ";
  collatzRecursive(collatzNum);
  
  return 0;
}

