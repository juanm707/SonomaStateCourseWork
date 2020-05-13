////////////////////////////////////
// Author:     Juan Martinez      //
// Student:    Juan Martinez      //
// Term:       Fall 2017          //
// Course:     CS 315             //
// Assignment: Lab 01             //
// Date:       9/11/17            //
// Professor:  Dr. Kooshesh       //
// File:       SmallSet.cpp       //
////////////////////////////////////

#include <iostream>
#include "SmallSet.hpp"

bool SmallSet::addElement(unsigned long num) {

    if (num >= MAX) //no values greater than or equal to 64*2 = 128 or less than zero (it is unsigned).
        return false;

    if (isMember(num)) {
        //std::cout << "Member in list already!" << std::endl;
        return false;
    }

    unsigned long block = 1;
    block = block << num;
    set = set | block;
    elemCount++;
    return true;
}

bool SmallSet::deleteElement(unsigned long num) {

    if (!isMember(num))
        return false;
    unsigned long block = 1;
    block = block << num;

    set = set ^ block;
    //std::cout << "Deleted: " << num << std::endl;
    elemCount--;
    return true;

}

bool SmallSet::isMember(unsigned long num) {

    if (elemCount == 0)
        return false;

    unsigned long block = 1;
    block = block << num;
    if (set & block) {
        //std::cout << "True\n";
        return true;
    }
    //std::cout << "not member" << std::endl;
    return false;

}

unsigned SmallSet::numElements() {

    return unsigned(elemCount);
}

void SmallSet::printElements() {

    for (int i = 0; i < 64; i++)
        if (isMember(i))
            std::cout << i << std::endl;
}
