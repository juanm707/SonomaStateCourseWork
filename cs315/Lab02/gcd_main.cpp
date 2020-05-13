////////////////////////////////////
// Author:     Juan Martinez      //
// Student:    Juan Martinez      //
// Term:       Fall 2017          //
// Course:     CS 315             //
// Assignment: Lab 02             //
// Date:       9/25/17            //
// Professor:  Dr. Kooshesh       //
// File:       gcd_main.cpp       //
////////////////////////////////////

#include <iostream>
#include "gcd.hpp"

int main () {

    int a = 230;
    int b = 400;
    std::cout << "GCD of " << a << " and " << b << " is: " << gcdIterative(a,b) << std::endl;
    std::cout << "Recursive - GCD of " << a << " and " << b << " is: " << gcdRecursive(a,b) << std::endl;
    a = 0;
    b = 20;
    std::cout << "GCD of " << a << " and " << b << " is: " << gcdIterative(a,b) << std::endl;
    std::cout << "Recursive - GCD of " << a << " and " << b << " is: " << gcdRecursive(a,b) << std::endl;
    a = 178;
    b = 0;
    std::cout << "GCD of " << a << " and " << b << " is: " << gcdIterative(a,b) << std::endl;
    std::cout << "Recursive - GCD of " << a << " and " << b << " is: " << gcdRecursive(a,b) << std::endl;
    a = 264;
    b = 342;
    std::cout << "GCD of " << a << " and " << b << " is: " << gcdIterative(a,b) << std::endl;
    std::cout << "Recursive - GCD of " << a << " and " << b << " is: " << gcdRecursive(a,b) << std::endl;
    a = 1000;
    b = 10000;
    std::cout << "GCD of " << a << " and " << b << " is: " << gcdIterative(a,b) << std::endl;
    std::cout << "Recursive - GCD of " << a << " and " << b << " is: " << gcdRecursive(a,b) << std::endl;

    return 0;
}

