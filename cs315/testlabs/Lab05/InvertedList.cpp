/*
  Author: Juan Martinez
  Course: CS 315
  Assignment: Lab 5
*/

#include <iostream>
#include "InvertedList.hpp"

InvertedList::InvertedList() {
    store.resize(5000);
    verifier.resize(5000);
    numElements = 0;
}

void InvertedList::insert(int v) { // inserts v in the inverted list.

    if ( v < 0 || v > 4999)
        return;
    if (lookup(v)) {
        //std::cout << v << " is already in!\n";
        return;
    }


    store[v] = numElements;
    verifier[numElements] = v;
    numElements++;
    //std::cout << "Added " << v << std::endl;
}


void InvertedList::remove(int v) { // removes v from the inverted list.

    if (!lookup(v)) {
        //std::cout << v << " is not in set!\n";
        return;
    }

    if (store.at(v) == numElements - 1) {
        verifier[store.at(v)] = 0;
        numElements--;
        //std::cout << "Removed " << v << std::endl;
        return;
    }

    int check = store.at(v);
    verifier[check] = verifier[numElements-1];
    numElements--;
    store.at(verifier[check]) = check;

    //std::cout << "Removed " << v << std::endl;
}

bool InvertedList::lookup(int v) { // is v a member of the inverted list?

    if (numElements == 0) {
        return false;
    }

    int check = store.at(v);

    if(verifier.at(check) == v) {
        return true;
    }
    else
        return false;
}


void InvertedList::print() { // print the elements in increasing order!

    for (int i = 0; i < 5000; i++)
        if (lookup(i))
            std::cout << i << std::endl;

}