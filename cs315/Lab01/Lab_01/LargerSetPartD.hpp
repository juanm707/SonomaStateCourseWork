////////////////////////////////////
// Author:     Dr. Kooshesh       //
// Student:    Juan Martinez      //
// Term:       Fall 2017          //
// Course:     CS 315             //
// Assignment: Lab 01             //
// Date:       9/11/17            //
// Professor:  Dr. Kooshesh       //
// File:       LargerSetPartD.hpp //
////////////////////////////////////

#ifndef LAB_01_LARGERSETPARTD_H
#define LAB_01_LARGERSETPARTD_H

//#include "lab01b_printBits_2.hpp"

class LargerSetPartD
{
public:
    // maxValue argument is the number of possible elements.
    // for example: maxValue is 100 for the range [0, 100)
    LargerSetPartD(unsigned maxValue);
    LargerSetPartD(const LargerSetPartD &);
    ~LargerSetPartD();
    bool addElement(unsigned int);      // add a new element to the set. No-op if input is invalid.
    bool deleteElement(unsigned int);   // delete an element from the set. No-op if not a member.
    bool isMember(unsigned int);        // is value a member
    unsigned int numElements();         // Number of elements in set
    void printElements();               // prints members from smallest to largest.

    void set_union(const LargerSetPartD &);
    void intersection(const LargerSetPartD &other);
    void difference(const LargerSetPartD &other);
    void complement();

private:
    unsigned long *set;                 // internal representation of our set.
    unsigned maxElementValue;
    unsigned numBuckets;
    int elemCount = 0;

    LargerSetPartD &operator=(const LargerSetPartD &);   // disallow assignment

};

#endif //LAB_01_LARGERSETPARTD_H
