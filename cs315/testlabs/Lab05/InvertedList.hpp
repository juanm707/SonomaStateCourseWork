/*
  Author: Juan Martinez
  Course: CS 315
  Assignment: Lab 5
*/

#ifndef LAB05_INVERTEDLIST_H
#define LAB05_INVERTEDLIST_H

#include <vector>

class InvertedList {
public:
    InvertedList();
    void insert(int v); // inserts v in the inverted list.
    void remove(int v); // removes v from the inverted list.
    bool lookup(int v); // is v a member of the inverted list?
    void print(); // print the elements in increasing order!

private:
    std::vector<int> store;
    std::vector<int> verifier;
    int numElements;
};

#endif //LAB05_INVERTEDLIST_H
