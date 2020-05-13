////////////////////////////////////
// Author:     Dr. Kooshesh       //
// Student:    Juan Martinez      //
// Term:       Fall 2017          //
// Course:     CS 315             //
// Assignment: Project 2          //
// Date:       9/28/17            //
// Professor:  Dr. Kooshesh       //
// File:       reclists.hpp       //
////////////////////////////////////

#ifndef __RECLISTS_HPP
#define  __RECLISTS_HPP

enum ListType {ATOMS, LISTS};

struct list_node {
     ListType type;
     char *atom;
     list_node *first, *rest;
};

typedef list_node *list;

list null(); // returns the empty list, ().
bool  is_null(list p);  // returns true if  p  is an empty list.
bool  is_atom(list p);     // returns true if  p  is an atom.
bool  eq(list p, list q);
// returns true if  p  and  q  are both atoms and are the same atom.

list car(list p);
// returns first element of list -- dies if p is a empty list or an atom.

list cdr(list p);
// return remainder of list -- dies if  p  is a empty list or an atom.

list cons(list p, list q);
// insert  p  as first element of list  q  -- dies if  q  is a an atom.

void write_list(list p);
// writes the external representation of  p  -- assumes that  p  has been
// defined by readlist or through use of above functions.

list read_list();
// Read a list, which can span several lines, returning that list.

#endif
