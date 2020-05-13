////////////////////////////////////
// Author:     Juan Martinez      //
// Student:    Juan Martinez      //
// Term:       Fall 2017          //
// Course:     CS 315             //
// Assignment: Lab 01             //
// Date:       9/11/17            //
// Professor:  Dr. Kooshesh       //
// File:       LargerSet.cpp      //
////////////////////////////////////

#include <iostream>
#include "LargerSet.hpp"

LargerSet::LargerSet(unsigned maxValue) {
  
    maxElementValue = maxValue;
    numBuckets = (maxElementValue / 64) + 1;
    set = new unsigned long [numBuckets];
}

LargerSet::~LargerSet() {

    std::cout << "Deleting\n";
    delete [] set;
}

bool LargerSet::addElement(unsigned int num) {

    if (num >= maxElementValue) {
        //std::cout << num << " NOT IN RANGE!\n"; //no values greater than or equal to MAX VALUE ex: 10,000 or less than zero (it is unsigned).
        return false;
    }

    if (isMember(num)) {
        //std::cout << num << " is already in set!\n";
        return false;
    }


    unsigned long block = 1;
    block = block << (num - (64 * (num / 64)));
    set[num / 64] = set[num/64] | block;
    //std::cout << num << " is in range! ADDING!\n";
    elemCount++;
    return true;
}

bool LargerSet::deleteElement(unsigned int num) {

    if (!isMember(num)) {
        //std::cout << num << " is not in set!\n";
        return false;
    }

    unsigned long block = 1;
    block = block << (num - (64 * (num/64)));
    set[num/64] = set[num/64] ^ block;
    //std::cout << "Deleted: " << num << std::endl;
    elemCount--;
    return true;

}

bool LargerSet::isMember(unsigned int num) {

    unsigned long block = 1;
    block = block << (num - (64 * (num/64)));
    if (set[num/64] & block) {
        //std::cout << num << " is member!\n";
        return true;
    }
    //std::cout << num << " is not a member" << std::endl;
    return false;

}

unsigned int LargerSet::numElements() {
    return unsigned(elemCount);
}

void LargerSet::printElements() {
    for (int i = 0; i < maxElementValue; i++)
        if (isMember(i))
            std::cout << i << std::endl;
}

