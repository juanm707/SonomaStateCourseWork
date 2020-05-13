///////////////////////////////////////////////////
// Author:     Juan Martinez/Dr. Kooshesh        //
// Student:    Juan Martinez                     //
// Term:       Fall 2017                         //
// Course:     CS 315                            //
// Assignment: Lab 02                            //
// Date:       9/25/17                           //
// Professor:  Dr. Kooshesh                      //
// File:       isMemberSequentialSearch_main.cpp //
///////////////////////////////////////////////////

#include "isMemberSequentialSearch.hpp"
#include <iostream>

int *readNValues(int numInputValues)
{
    int *numbers = new int[numInputValues];
    int numRead = 0;
    for( int i = 0; i < numInputValues && std::cin >> numbers[numRead++]; i++ )
        ;
    if( numInputValues != numRead ) {
        std::cerr << "Wasn't able to read " << numInputValues << " values; read only " << numRead << " Terminating...\n";
        exit(1);
    }
    return numbers;
}


int main()
{
    int numInputValues;
    std::cin >> numInputValues;
    int *numbers = readNValues(numInputValues);

    int numMembers;
    std::cin >> numMembers;
    int *members = readNValues(numMembers);
    /*
      each of the values in "members" should be a member of "numbers"
     */

    for (int i = 0; i < numMembers; i++) {
      if (isMemberSequentialSearchIterative(numbers, numInputValues, members[i])) {
	std::cout << "Iterative search found " << members[i] << " is a member\n";
      }
      else
	std::cout << "Iterative search found " << members[i] << " as not a member\n";

      if (isMemberSequentialSearchRecursive(numbers, numInputValues, members[i])) {
	std::cout << "Recursive search found " << members[i] << " is a member\n";
      }
      else
	std::cout << "Recursive search found " << members[i] <<" as not a member\n";
      std::cout << std::endl;
    }

    std::cout << std::endl << "Done checking members" << std::endl << std::endl;
    
    int numNonMembers;
    std::cin >> numNonMembers;
    int *nonMembers = readNValues(numNonMembers);
    /*
      each of the values in "nonMembers" should not be a member of "numbers"
     */

    for (int i = 0; i < numNonMembers; i++) {
      if (isMemberSequentialSearchIterative(numbers, numInputValues,nonMembers[i])) {
	std::cout << "Iterative search found " << nonMembers[i] << " is a member\n";
      }
      else
	std::cout << "Iterative search found " << nonMembers[i] << " as not a member\n";

      if (isMemberSequentialSearchRecursive(numbers, numInputValues, nonMembers[i])) {
	std::cout << "Recursive search found " << nonMembers[i] << " is a member\n";
      }
      else
	std::cout << "Recursive search found " << nonMembers[i] <<" as not a member\n";
      std::cout << std::endl;
    }

    std::cout << std::endl << "Done checking non-members" << std::endl << std::endl;


    delete [] numbers;
    delete [] members;
    delete [] nonMembers;

    return 0;
}
