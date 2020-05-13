////////////////////////////////////
// Author:     Juan Martinez      //
// Student:    Juan Martinez      //
// Term:       Fall 2017          //
// Course:     CS 315             //
// Assignment: Project 2          //
// Date:       9/28/17            //
// Professor:  Dr. Kooshesh       //
// File:       solutions.hpp      //
////////////////////////////////////

#ifndef __MYSOLUTION_HPP
#define __MYSOLUTION_HPP

#include<iostream>
#include"reclists.hpp"

list reverse( list p );
list append( list p, list q );
list last( list p );
bool is_lat( list p );
bool member ( list p, list q );
list list_pair ( list p, list q );
list firsts ( list p) ;
list flat ( list p );
bool two_the_same ( list p, list q );
bool equal ( list p, list q );
list total_reverse ( list p );
list shape ( list p );
list intersection ( list p, list q );
list list_union ( list p, list q );

#endif
