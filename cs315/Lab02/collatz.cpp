////////////////////////////////////
// Author:     Juan Martinez      //
// Student:    Juan Martinez      //
// Term:       Fall 2017          //
// Course:     CS 315             //
// Assignment: Lab 02             //
// Date:       9/25/17            //
// Professor:  Dr. Kooshesh       //
// File:       collatz.cpp        //
////////////////////////////////////

#include <iostream>

void collatzIterative(int n) {
// base-case: if n == 1, print 1 and stop the process.
// iteration: if n is even, print n and calculate the Collatz sequence of n/2.
//            if n is odd, print n and calculate the Collatz sequence of 3n + 1.
  
    std::cout << n << std::endl;
    
    if (n == 0) {
        std::cout << "0 never reaches one!\n";
        exit(2);
    }

    while (n != 1) {

        if (( n % 2 ) == 0) {

            n = n /2;
            std::cout << n << std::endl;
        }

        else {
            n = ( n * 3 ) + 1;
            std::cout << n << std::endl;
        }

    }
    std::cout << std::endl;
}

void collatzRecursive(int n) {
// base-case: if n == 1, print 1 and stop the process.
// iteration: if n is even, print n and calculate the Collatz sequence of n/2.
//            if n is odd, print n and calculate the Collatz sequence of 3n + 1.

    if (n == 0) {
        std::cout << "0 never reaches one!\n";
        exit(2);
    }

    if (n == 1)
        std::cout << n << std::endl;

    else if ((n % 2) == 0) {

      std::cout << n << std::endl;
        collatzRecursive(n/2);
    }

    else {

        std::cout << n << std::endl;
        collatzRecursive((3 * n) + 1);
    }
}
