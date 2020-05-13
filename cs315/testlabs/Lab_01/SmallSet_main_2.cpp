/////////////////////////////////////
// Author:     Dr. Kooshesh        //
// Student:    Juan Martinez       //
// Term:       Fall 2017           //
// Course:     CS 315              //
// Assignment: Lab 01              //
// Date:       9/11/17             //
// Professor:  Dr. Kooshesh        //
// File:       SmallSet_main_2.cpp //
/////////////////////////////////////

#include<iostream>
#include<fstream>
#include<unistd.h>
#include<stdlib.h>
#include "SmallSet.hpp"
#include "LargerSet.hpp"
#include "LargerSetPartD.hpp"

class LazySet 
{
public:
    LazySet(unsigned numElmnts): numElements(numElmnts), set(new bool[numElmnts]) {
        for( int i = 0; i < numElmnts; i++ )
            set[i] = false;
    }

    void insert(unsigned v) { v < numElements && (set[v] = true);  }
    void remove(unsigned v) { v < numElements && (set[v] = false); }
    bool member(unsigned v) { return v < numElements && set[v];  }
    unsigned card() {
        unsigned count = 0;
        for( int i = 0; i < numElements; i++ )
            count += set[i] ? 1 : 0;
        return count;
    }

private:
    unsigned numElements;
    bool *set;
};

const int numBits = sizeof(long) * 8;
const bool debug = false;

bool areTheSame(LargerSet *sm, LazySet *l_set)
{
    if( sm->numElements() != l_set->card() ) {
        if( debug ) 
            std::cout << "Your set has " << sm->numElements() << " members but the reference set has " << l_set->card() << std::endl;

        std::cout << "Test failed; the set doesn't have the correct number of elements...\n";
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

void testInsertsAndDeletes(LargerSet *sm, LazySet *l_set, int numOps) {
    if( debug )
        std::cout << "Starting the test.\n";
    for( int i = 0; i < numOps; i++ ) {
        int op = rand() % 11;
        if( op <= 6 ) { // 60 % of the times insert a random value
            int v = rand() % numBits;
            if( debug ) 
                std::cout << "inserting " << v << std::endl;

            sm->addElement(v);
            l_set->insert(v);
        } else { // 40% of the times delete a value
            int v = rand() % numBits;
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


int main()
{
    const int numOps = 200;

    pid_t pid = getpid();
    srand(pid);   // initialize using process id.
    
    std::cout << "Creating and testing a SmallSet\n";
    LargerSet *sm = new LargerSet(10000);
    LazySet *l_set = new LazySet(numBits);
    testInsertsAndDeletes(sm, l_set, numOps);
    
    std::cout << "Creating and testing another SmallSet\n";
    LargerSet *sm2 = new LargerSet(10000);
    LazySet *l_set2 = new LazySet(numBits);
    testInsertsAndDeletes(sm2, l_set2, numOps);

    std::cout << "Creating and testing another SmallSet\n";    
    LargerSet *sm3 = new LargerSet(10000);
    LazySet *l_set3 = new LazySet(numBits);
    testInsertsAndDeletes(sm2, l_set2, numOps);

    delete sm;
    delete l_set;

    delete sm2;
    delete l_set2;

    delete sm3;
    delete l_set3;

    std::cout << "All okay!\n";

    /*SmallSet * testset = new SmallSet();
    for (int i = 0; i < 20; i++)
        testset->addElement(i);
    testset->printElements();
    for (int e = 0; e < 20; e++)
    {
        if ((e % 2) == 0)
            testset->deleteElement(e);
    }
    testset->printElements();
    testset->addElement(0);
    testset->printElements();*/

    LargerSet * larger = new LargerSet(10000);
    larger->addElement(5);       // add 5 to the set.
    larger->addElement(20);
    larger->addElement(19500);   // out-of-bounds; should be ignored!
    larger->addElement(100000);  // out-of-bounds; should be ignored!
    larger->addElement(1950);
    larger->addElement(100);
    std::cout << "Num elements for larger: " << larger->numElements() << std::endl;
    larger->printElements();

    delete larger;

    /*LargerSetPartD * original = new LargerSetPartD(1000);
    original->addElement(0);
    original->addElement(1);
    original->addElement(2);
    original->addElement(3);
    original->addElement(4);
    original->addElement(69);
    original->addElement(43);
    original->addElement(5);
    original->addElement(80);
    original->addElement(789);
    original->addElement(571);
    original->addElement(809);
    original->addElement(367);
    std::cout << "original contains \n";
    original->printElements();

    LargerSetPartD * other = new LargerSetPartD(1000);
    other->addElement(1);
    other->addElement(6);
    other->addElement(7);
    other->addElement(8);
    other->addElement(9);
    other->addElement(10);
    other->addElement(11);
    other->addElement(12);
    other->addElement(13);
    other->addElement(14);
    other->addElement(15);
    other->addElement(999);
    std::cout << "other contains \n";
    other->printElements();
    other->set_union(*original);
    std::cout << "other now contains \n";
    other->printElements();

    LargerSetPartD * in = new LargerSetPartD(1000);
    in->addElement(7);
    in->addElement(4);
    in->addElement(3);
    in->addElement(5);
    in->addElement(23);
    in->addElement(54);
    in->addElement(345);
    std::cout << "in has:\n";
    in->printElements();

    LargerSetPartD * in2 = new LargerSetPartD(100);
    in2->addElement(0);
    in2->addElement(1);
    in2->addElement(3);
    in2->addElement(4);
    in2->addElement(5);
    std::cout << "in2 has:\n";
    in2->printElements();

    in2->intersection(*in);
    std::cout << "after in2 and in intersection, in2 should have 1\n";
    in2->printElements();

    delete original;
    delete other;

    delete in;
    delete in2;

    LargerSetPartD * dif1 = new LargerSetPartD(1000);
    dif1->addElement(0);
    dif1->addElement(1);
    dif1->addElement(2);
    dif1->addElement(3);
    dif1->addElement(99);
    dif1->addElement(999);
    std::cout << "Dif1 contains:\n";
    dif1->printElements();

    LargerSetPartD * dif2 = new LargerSetPartD(10000);
    dif2->addElement(0);
    dif2->addElement(1);
    dif2->addElement(5);
    dif2->addElement(99);
    dif2->addElement(69);
    dif2->addElement(999);
    dif2->addElement(9999);
    std::cout << "Dif2 contains:\n";
    dif2->printElements();

    dif2->difference(*dif1);
    std::cout << "Dif2 should contain: 5, 69, 9999\n";
    dif2->printElements();



    delete dif1;
    delete dif2;

    LargerSetPartD * comSet = new LargerSetPartD(6);
    comSet->addElement(5);
    comSet->printElements();
    comSet->complement();
    comSet->printElements();

    delete comSet;*/

    return 0;
}
