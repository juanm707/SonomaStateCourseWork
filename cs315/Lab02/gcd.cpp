////////////////////////////////////
// Author:     Juan Martinez      //
// Student:    Juan Martinez      //
// Term:       Fall 2017          //
// Course:     CS 315             //
// Assignment: Lab 02             //
// Date:       9/25/17            //
// Professor:  Dr. Kooshesh       //
// File:       gcd.cpp            //
////////////////////////////////////

#include <iostream>

int gcdIterative(int a, int b) {
// pre-condition: a < b is true.
// The function finds and returns the gcd of a and b using an
// iterative solution.
// -1 for failed
  
    if ( a > b )
        return -1;
    
    if ( a == 0 || b == 0 ) {
      std::cout << "No zero allowed\n";
      return -1;
    }
    
    if ((b % a) == 0)
        return a;

    while ( (b % a) != 0) {
        int temp = a;
        a = b % a;
        b = temp;
    }
    return a;
}

int gcdRecursive(int a, int b) {
// pre-condition: a < b is true.
// The function finds and returns the gcd of a and b using a
// recursive solution.
// -1 for failed

    if ( a > b )
        return -1;
    
    if ( a == 0 || b == 0 ) {
      std::cout<< "No zero allowed\n";
      return -1;
    }
    
    if ((b % a) == 0)
        return a;
    return gcdRecursive(b % a, a);
}
