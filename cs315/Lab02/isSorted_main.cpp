//////////////////////////////////////////
// Author:     Dr. Kooshesh             //
// Student:    Juan Martinez            //
// Term:       Fall 2017                //
// Course:     CS 315                   //
// Assignment: Lab 02                   //
// Date:       9/25/17                  //
// Professor:  Dr. Kooshesh             //
// File:       isSorted_main.cpp        //
//////////////////////////////////////////

#include <iostream>
#include "isSorted.hpp"

int main()
{
    int numInputValues;
    std::cin >> numInputValues;
    if( ! std::cin.good() )
        return 1;
    int *numbers = new int[numInputValues];
    int numRead = 0;
    for( int i = 0; i < numInputValues && std::cin >> numbers[numRead++]; i++ )
        ;
    if( numInputValues != numRead ) {
        std::cerr << "Wasn't able to read " << numInputValues << " values; read only " << numRead << " Terminating...\n";
        return 1;
    }
    if( isSortedIterative(numbers, numInputValues) )
        std::cout << "Iterative version: numbers are sorted.\n";
    else
        std::cout << "Iterative version: numbers are not sorted.\n";

    if( isSortedRecursive(numbers, numInputValues) )
        std::cout << "Recursive version: numbers are sorted.\n";
    else
        std::cout << "Recursive version: numbers are not sorted.\n";

    delete [] numbers;
    return 0;
}
