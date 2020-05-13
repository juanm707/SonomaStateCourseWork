////////////////////////////////////
// Author:     Dr. Kooshesh       //
// Student:    Juan Martinez      //
// Term:       Fall 2017          //
// Course:     CS 315             //
// Assignment: Project 2          //
// Date:       9/28/17            //
// Professor:  Dr. Kooshesh       //
// File:       main.cpp           //
////////////////////////////////////

#include<iostream>
#include"reclists.hpp"
#include"solutions.hpp"

using namespace std;

int main()
{

    std::cout << "Starting main..." << std::endl;

    // Move the following pre-processor line down as you write a solution for each of
    // the functions.

     list p, q;

     cout << "Enter two lists for append: ";
     p = read_list();
     q = read_list();
     write_list( append(p, q) );

     cout << "Enter a list for reverse: ";
     p = read_list();
     write_list( reverse(p) );

    //is_lat
    cout << "Enter a list for is_lat: ";
    p = read_list();
    write_list(p);
    if (is_lat(p))
        cout << "TRUE is_lat:: The above list is an atomic list; a list of atoms.\n";
    else
        cout << "FALSE is_lat:: The above list is not an atomic list\n";

    // member
    cout << "Enter two lists for member (an atom followed by a list):\n";
    p = read_list();
    q = read_list();
    if( member(p, q) )
        cout << "Is a member\n";
    else
        cout << "Is not a member\n";

    // last
    cout << "Enter a list for last: ";
    p = read_list();
    //write_list( p );
    write_list( last( p ) );

    // list-pair
    cout << "Enter two lists for list-pair: ";
    p = read_list();
    q = read_list();
    write_list( list_pair(p, q) );

    // firsts
    cout << "Enter a list for firsts: ";
    p = read_list();
    write_list( firsts(p) );

    // flat
    cout << "Enter a list for flat: ";
    p = read_list();
    cout << "Output list for flat is: " << endl;
    write_list( flat( p ) );

    // two_the_same
    cout << "Enter two lists for two_the_same: ";
    p = read_list();
    q = read_list();
    if (two_the_same(p, q))
        cout << "They have an atom in common\n";
    else
        cout << "No common element\n";

    // equal
    cout << "Enter two lists for equal: ";
    p = read_list();
    q = read_list();

    if (equal(p,q))
        cout << "They are both equal!\n";
    else
        cout << "They are NOT equal!\n";

    // total_reverse
    cout << "Enter a list for total reverse: ";
    p = read_list();
    write_list( total_reverse(p) );

    // shape
    cout << "Enter a list for shape: ";
    write_list( shape( read_list() ) );

    //  Intersection
    cout << "Enter two lists for intersection: ";
    p = read_list();
    q = read_list();
    write_list( intersection(p, q) );

    //  List-Union
    cout << "Enter two lists for list_union: ";
    p = read_list();
    q = read_list();
    cout << "The union is: \n";
    write_list( list_union(p, q) );

    /* permute
    cout << "Enter a list for permute: ";
    p = read_list();
    write_list(permute(p));*/

     return 0;
}
