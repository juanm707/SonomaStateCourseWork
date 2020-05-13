////////////////////////////////////
// Author:     Dr. Kooshesh       //
// Student:    Juan Martinez      //
// Term:       Fall 2017          //
// Course:     CS 315             //
// Assignment: Lab 01             //
// Date:       9/11/17            //
// Professor:  Dr. Kooshesh       //
// File:       InvertedList.hpp   //
////////////////////////////////////

#include<cstdlib>

class InvertedList
{
public:
  InvertedList(unsigned size);
  ~InvertedList();

  bool member(unsigned v) const;
  bool member(unsigned v);
  void insert(unsigned v);
  void print();
  void remove(unsigned v);
  int randomElement();
  unsigned card();
  void complement();
  void intersection(const InvertedList &other );
  void difference(const InvertedList &other);
  void set_union(const InvertedList &other);
  unsigned maxElementValue();

private:
  unsigned numElements, maxValue;
  unsigned *randomList;
  unsigned *verifier;
  void initWithMaxValue(unsigned size);
};
