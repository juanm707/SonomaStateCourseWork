////////////////////////////////////
// Author:     Dr. Kooshesh       //
// Student:    Juan Martinez      //
// Term:       Fall 2017          //
// Course:     CS 315             //
// Assignment: Project 2          //
// Date:       9/28/17            //
// Professor:  Dr. Kooshesh       //
// File:       parser.cpp         //
////////////////////////////////////

#include<iostream>
#include<cstdlib>
#include<string.h>
#include "lex.hpp"
#include "reclists.hpp"

using namespace std;

list make_atom( char name[] );
list get_rest();

list read_list()
     //  This is a simple recursive descend parser that recognizes the
     //  following grammar:
    
     //    <list> -->  atom | () | ( <more-list> ) 
     //    <more-list> --> <list> | <list> <more-list>

     //    This function parses <list>.  get_rest() parses <more-list>.  

{
     char val[MAX_ATOM_LEN];
     tokens token = get_token( val );
     if( token == ATOM ) return  make_atom( val );
     if( token == LPAREN ) return get_rest();
     if( token == END_OF_TEXT ) return 0;
     cout << "ERROR -- error in  readlist: " <<
                          "Did not expect: " << token << endl;
     exit(1);
}

list get_rest()
{
  
     char val[ MAX_ATOM_LEN ];
     tokens token = get_token( val );
     if( token == RPAREN ) return 0;
     unget_token();
     list r = read_list();
     return cons( r, get_rest() );
}

list make_atom( char name[] )
{
     list r = new list_node;
     r->atom = new char[ strlen(name) + 1 ];
     r->type = ATOMS;
     strcpy(r->atom, name);
     return r;
}

list cons(list p, list q)
{
     // insert  p  as first element of list  q  -- dies if  q  is a an atom.

     if( ! is_null(q) && is_atom(q) ) {
	  cout << "ERROR -- error in cons\n";
	  exit( 1 );
     }
     list r = new list_node;
     r->type = LISTS;
     r->first = p;
     r->rest = q;
     return r;
}
