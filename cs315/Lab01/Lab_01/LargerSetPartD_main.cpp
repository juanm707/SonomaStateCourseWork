/////////////////////////////////////////
// Author:     Dr. Kooshesh            //
// Student:    Juan Martinez           //
// Term:       Fall 2017               //
// Course:     CS 315                  //
// Assignment: Lab 01                  //
// Date:       9/11/17                 //
// Professor:  Dr. Kooshesh            //
// File:       LargerSetPartD_main.cpp //
/////////////////////////////////////////

#include<iostream>
#include<fstream>
#include<unistd.h>
#include<stdlib.h>
#include<cstring>

#include "LargerSetPartD.hpp"
#include "InvertedList.hpp"


const int numBits = sizeof(long) * 8;
const bool debug = false;

bool areTheSame(LargerSetPartD *sm, InvertedList *l_set)
{
  if( sm->numElements() != l_set->card() ) {
    if( debug )
      std::cout << "Your set has " << sm->numElements() << " members but the reference set has " << l_set->card() << std::endl;

    std::cout << "Test failed; set doesn't have the correct number of elements...\n";
    std::cout << "             set has " << sm->numElements() << " but the reference set has " << l_set->card() << std::endl;
    exit( 1 );
  }
  for( int k = 0; k < numBits; k++ )
    if( sm->isMember(k) && ! l_set->member(k) ) {
      std::cout << k << " is a member of your set but not a member of the reference set.\n";
      exit(1);
    } else if( ! sm->isMember(k) && l_set->member(k) ) {
      std::cout << k << " is a member of the reference set but not a member of your set.\n";
      exit(1);
    }
  return true;
}

void testInsertsAndDeletes(LargerSetPartD *sm, InvertedList *l_set, int numOps) {
  if( debug )
    std::cout << "Starting the test.\n";
  unsigned maxValue = l_set->maxElementValue();
  for( int i = 0; i < numOps; i++ ) {
    int op = rand() % 11;
    if( op <= 6 ) { // 60 % of the times insert a random value
      int v = rand() % maxValue;
      if( debug )
	std::cout << "inserting " << v << std::endl;

      sm->addElement(v);
      l_set->insert(v);
    } else if( op <= 8 ) { // 20% of the times delete a random value
      int v = rand() % maxValue;
      if( debug )
	std::cout << "deleting " << v << std::endl;

      sm->deleteElement(v);
      l_set->remove(v);
    } else if( l_set->card() != 0 ) {
      int v = l_set->randomElement();
      if( debug )
	std::cout << "deleting " << v << std::endl;
      sm->deleteElement(v);
      l_set->remove(v);
    }
    if( i % 10 == 0 )  // test set equality once per 10 iterations
      areTheSame(sm, l_set);
  }
  if( debug )
    std::cout << "Test ends.\n";

}

static int testNumber = 1;

void insertDeleteMembershipTest(unsigned range, unsigned numOps) {
  std::cout << "Creating and testing a LargerSetPartD: test number: " << testNumber++ << std::endl;
  LargerSetPartD *sm = new LargerSetPartD(range);
  InvertedList *l_set = new InvertedList(range);
  testInsertsAndDeletes(sm, l_set, numOps);

  delete sm;
  delete l_set;
}

void testComplement(unsigned range, unsigned numOps ) {
  std::cout << "Creating and testing a LargerSetPartD: test number: " << testNumber++ << std::endl;
  LargerSetPartD *sm = new LargerSetPartD(range);
  InvertedList *l_set = new InvertedList(range);
  testInsertsAndDeletes(sm, l_set, numOps);
  std::cout << "Testing complement: test number: " << testNumber++ << std::endl;
  sm->complement();
  l_set->complement();
  areTheSame(sm, l_set);
  delete sm;
  delete l_set;
}

void testBinarySetOperations(unsigned range1, unsigned range2, const char *op, unsigned numOps) {
  std::cout << "Testing " << op << std::endl;
  if( ! (strcmp(op, "union") == 0 || strcmp(op, "intersection") == 0 || strcmp(op, "difference") == 0 ) ) {
    std::cout << "Operation '" << op << "' not supported\n";
    return;
  }
  std::cout << "Testing set operation '" << op << "', test number: " << testNumber++ << std::endl;
  std::cout << "Creating and testing a LargerSetPartD: test number: " << testNumber++ << std::endl;
  LargerSetPartD *sm = new LargerSetPartD(range1);
  InvertedList *l_set = new InvertedList(range1);
  testInsertsAndDeletes(sm, l_set, numOps);

  std::cout << "Creating and testing a LargerSetPartD: test number: " << testNumber++ << std::endl;
  LargerSetPartD *sm2 = new LargerSetPartD(range2);
  InvertedList *l_set2 = new InvertedList(range2);
  testInsertsAndDeletes(sm2, l_set2, numOps);

  if( strcmp(op, "union") == 0  ) {
    sm->set_union(*sm2);
    l_set->set_union(*l_set2);
  } else if( strcmp(op, "intersection") == 0 ) {
    sm->intersection(*sm2);
    l_set->intersection(*l_set2);
  } else if( strcmp(op, "difference") == 0 ) {
    sm->difference(*sm2);
    l_set->difference(*l_set2);
  } else {
    std::cout << "We weren't supposed to get here. Did we add a new set operation?\n";
    return;
  }
  areTheSame(sm, l_set);

  delete sm;
  delete sm2;
  delete l_set;
  delete l_set2;
}

int main()
{
  const int numOps = 20000;

  pid_t pid = getpid();
  std::cout << "Using seed value " << pid << std::endl;
  srand(10941);   // initialize using process id.


  insertDeleteMembershipTest(64, numOps);
  insertDeleteMembershipTest(164, numOps);
  insertDeleteMembershipTest(7821950, numOps);

  testComplement(18464, numOps);
  testBinarySetOperations(2810, 2810,  "union", numOps);
  testBinarySetOperations(6810, 6400,  "union", numOps);
  testBinarySetOperations(2410, 8400,  "union", numOps);

  testBinarySetOperations(2810, 2810,  "intersection", numOps);
  testBinarySetOperations(6810, 6400,  "intersection", numOps);
  testBinarySetOperations(2410, 8400,  "intersection", numOps);

  testBinarySetOperations(2810, 2810,  "difference", numOps);
  testBinarySetOperations(6810, 6400,  "difference", numOps);
  testBinarySetOperations(2410, 8400,  "difference", numOps);

  std::cout << "All okay!\n";

  return 0;
}
