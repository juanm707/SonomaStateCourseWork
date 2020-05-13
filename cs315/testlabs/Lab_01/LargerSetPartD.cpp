////////////////////////////////////
// Author:     Juan Martinez      //
// Student:    Juan Martinez      //
// Term:       Fall 2017          //
// Course:     CS 315             //
// Assignment: Lab 01             //
// Date:       9/11/17            //
// Professor:  Dr. Kooshesh       //
// File:       LargerSetPartD.cpp //
////////////////////////////////////

//READ README.txt

#include <iostream>
#include "LargerSetPartD.hpp"

LargerSetPartD::LargerSetPartD(unsigned maxValue) {

    maxElementValue = maxValue;
    numBuckets = (maxElementValue / 64) + 1; //array elements and add one extra element so maxElementValue - 1 fits.
    set = new unsigned long [numBuckets];
    for (int i = 0; i < numBuckets; i++) { //initialize to 0 (not sure if by default already)
        set[i] = 0;
    }
}

LargerSetPartD::LargerSetPartD(const LargerSetPartD & other) {
  //copy the other type's data and set it in this
    set = other.set;
    maxElementValue = other.maxElementValue;
    numBuckets = other.numBuckets;
    elemCount = other.elemCount;
}

LargerSetPartD::~LargerSetPartD() {

  //std::cout << "Deleting\n";
    delete [] set;
}

bool LargerSetPartD::addElement(unsigned int num) {

    if (num >= maxElementValue) {
        //std::cout << num << " NOT IN RANGE!\n"; //no values greater than or equal to MAX VALUE ex: 10,000 or less than zero (it is unsigned).
        return false;
    }

    if (isMember(num)) {
        //std::cout << num << " is already in set!\n";
        return false;
    }


    unsigned long block = 1;
    block = block << (num - (64 * (num / 64))); // shift to correct position, if over 63, figures out correct position of next array element
    set[num / 64] = set[num/64] | block; //select right array element
    //std::cout << num << " is in range! ADDING!\n";
    elemCount++;
    return true;
}

bool LargerSetPartD::deleteElement(unsigned int num) {
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

bool LargerSetPartD::isMember(unsigned int num) {

    unsigned long block = 1;
    block = block << (num - (64 * (num/64)));
    if (set[num/64] & block) {
        //std::cout << num << " is member!\n";
        return true;
    }
    //std::cout << num << " is not a member" << std::endl;
    return false;

}

unsigned int LargerSetPartD::numElements() {
    return unsigned(elemCount);
}

void LargerSetPartD::printElements() {
    for (int i = 0; i < maxElementValue; i++)
        if (isMember(i))
            std::cout << i << std::endl;
}

void LargerSetPartD::set_union(const LargerSetPartD & other) {

  int count = 0; //for element count
  
  if (other.maxElementValue >= this->maxElementValue) { //if other >

        LargerSetPartD *newSet = new LargerSetPartD(other.maxElementValue);
        for (int i = 0; i < other.numBuckets; i++) {
	  while (i < numBuckets) { //add the smaller array first

                newSet->set[i] = newSet->set[i] | other.set[i];
                newSet->set[i] = newSet->set[i] | this->set[i];
                i++;
	  }

	  if (i < other.numBuckets) //finish adding rest of bigger array
                newSet->set[i] = newSet->set[i] | other.set[i];

        }

	for (int i = 0; i < newSet->maxElementValue; i++)
	  if(newSet->isMember(i))
	    count++; //count the elements, excluding duplicates

        elemCount = count;
        delete[] this->set;
        this->set = newSet->set;
        this->maxElementValue = newSet->maxElementValue;
        this->numBuckets = newSet->numBuckets;
        //delete newSet;
    }
    else { //if this mEV is bigger than other mEV

        for (int i = 0; i < other.numBuckets; i++) {

	  set[i] = set[i] | other.set[i]; //add the other array elements
        }

	for (int i = 0; i < maxElementValue; i++)
	  if(isMember(i))
	    count++;
	
        elemCount = count;

    }

}

void LargerSetPartD::intersection(const LargerSetPartD &other) {

    int count = 0; // for common items
    
    if (other.maxElementValue <= this->maxElementValue) {

        LargerSetPartD *newSet = new LargerSetPartD(other.maxElementValue);
        for (int i = 0; i < other.numBuckets; i++) {
            newSet->set[i] = newSet->set[i] | other.set[i];
            newSet->set[i] = newSet->set[i] & this->set[i];
        }

        for (int i = 0; i < newSet->maxElementValue; i++) {
            if (newSet->isMember(i))
                count++;
        }

        elemCount = count;
        delete[] this->set;
        this->set = newSet->set;
        this->maxElementValue = newSet->maxElementValue;
        this->numBuckets = newSet->numBuckets;
        //delete newSet;
    }

    else { //if this mEV is smaller than mEV

        for (int i = 0; i < numBuckets; i++) {

            set[i] = set[i] & other.set[i];
        }

        for (int i = 0; i < this->maxElementValue; i++) {
            if (this->isMember(i))
                count++;
        }

        elemCount = count;

    }
}

void LargerSetPartD::difference(const LargerSetPartD &other) {

    int count = 0; // for elemcount
    if (this->maxElementValue <= other.maxElementValue) { // if THIS is smaller or equal

        LargerSetPartD *newSet = new LargerSetPartD(maxElementValue);
        for (int i = 0; i < numBuckets; i++) {

            newSet->set[i] = newSet->set[i] | ~other.set[i];
            newSet->set[i] = newSet->set[i] & this->set[i];
        }

        for (int i = 0; i < newSet->maxElementValue; i++) {
            if (newSet->isMember(i))
                count++;
        }

        elemCount = count;
        delete[] this->set;
        this->set = newSet->set;
        this->maxElementValue = newSet->maxElementValue;
        this->numBuckets = newSet->numBuckets;

    } else { //if this EV is bigger than other mEV

        LargerSetPartD *newSet = new LargerSetPartD(maxElementValue);
        for (int i = 0; i < this->numBuckets; i++) {

            while (i < other.numBuckets) { //gets other since its smaller we dont check all of this->set buckets

                newSet->set[i] = newSet->set[i] | ~other.set[i];
                newSet->set[i] = newSet->set[i] & this->set[i];
                i++;
            }

            newSet->set[i] = newSet->set[i] | this->set[i]; //get rest of this set since its bigger than other
        }
        for (int i = 0; i < newSet->maxElementValue; i++) {
            if (newSet->isMember(i))
                count++;
        }

        elemCount = count;
        delete[] this->set;
        this->set = newSet->set;
        this->maxElementValue = newSet->maxElementValue;
        this->numBuckets = newSet->numBuckets;
    }
}

void LargerSetPartD::complement() {

    int count = 0;
    LargerSetPartD * newSet = new LargerSetPartD(maxElementValue);
    for (int i = 0; i < numBuckets; i++) {
      newSet->set[i] = newSet->set[i] | this->set[i]; //set values
      newSet->set[i] = ~newSet->set[i]; //negate values
    }

    for (int i = 0; i < newSet->maxElementValue; i++) {
        if (newSet->isMember(i))
            count++;
    }

    elemCount = count;
    delete[] this->set;
    this->set = newSet->set;
    this->maxElementValue = newSet->maxElementValue;
    this->numBuckets = newSet->numBuckets;

}
