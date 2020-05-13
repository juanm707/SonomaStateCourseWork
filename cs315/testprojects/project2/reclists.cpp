////////////////////////////////////
// Author:     Dr. Kooshesh       //
// Student:    Juan Martinez      //
// Term:       Fall 2017          //
// Course:     CS 315             //
// Assignment: Project 2          //
// Date:       9/28/17            //
// Professor:  Dr. Kooshesh       //
// File:       reclists.cpp       //
////////////////////////////////////

#include<iostream>
#include<string.h>
#include<stdlib.h>
#include"reclists.hpp"

using namespace std;


const int LINE_LEN = 72;                // for safe screen width.
const char *LEADER = "  ";
const int LENofLEADER = strlen(LEADER); // length of above.
int line_used = 0; 

void write_item(list p);
void emit( const char str[] );
void write_list(list p)
{
     // writes the external representation of  p  -- assumes that  p  has been
     // defined by  readlist  or through the use of above functions.
      write_item(p);
      cout << endl;
}

void emit( const char str[] )
{

     int len = strlen( str );
     if( line_used + len + 1 > LINE_LEN ) {
	  cout << endl;
	  cout << LEADER;  // indent subsequent lines.
	  line_used = LENofLEADER;
     }
     line_used = line_used + len + 1;
     cout << ' '; 
     cout << str;
}

const char *NILSYM = "()";
const char *LEFT_PAREN = "(";
const char *RIGHT_PAREN = ")";

void write_item(list p)
{
     if( is_null(p) ) emit(NILSYM);
     else if( is_atom(p) )
	  emit(p->atom);
     else {
	  emit(LEFT_PAREN);
	  do {
	       write_item(car(p));
	       p = cdr(p);
	  } while ( ! is_null(p) );
	  emit(RIGHT_PAREN);
     }
}


list null()
{
     return 0;
}

bool is_null( list p )
{
     return p == 0;
}

bool is_atom( list p )
{
     return ! is_null(p) && p->type == ATOMS;
}

list cdr(list p)
{
     // return remainder of list -- dies if  p  is a empty list or an atom.
     if( is_null(p) || is_atom(p) ) {
	  cout << "ERROR in cdr:  cdr has been called either with an empty list or an atom.  Input list is:\n";
          write_list( p );
	  exit( 1 );
     }
     return p->rest;
}


list  car( list p)
{
     // return first element of list -- dies if p is a empty list or an atom.
     if( is_null(p) || is_atom(p) ) {
	  cout << "ERROR in car:  car has been called either with an empty list or an atom.  Input list is:\n";
          write_list( p );
	  exit( 1 );
     }
     return  p->first;
}

bool eq( list p, list q )
{
     if( ! is_atom(p) || ! is_atom(q) ) return 0;
     return strcmp( p->atom, q->atom ) == 0;
}
