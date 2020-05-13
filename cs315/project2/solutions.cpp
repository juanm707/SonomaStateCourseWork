////////////////////////////////////
// Author:     Juan Martinez      //
// Student:    Juan Martinez      //
// Term:       Fall 2017          //
// Course:     CS 315             //
// Assignment: Project 2          //
// Date:       9/28/17            //
// Professor:  Dr. Kooshesh       //
// File:       solutions.cpp      //
////////////////////////////////////

#include "reclists.hpp"
#include "solutions.hpp"

// As you implement functions in this file, you should add the 
// function-prototype to the solutions.hpp. The function-prototypes 
// for append and reverse are already in solutions.hpp.

list append( list p, list q )
{
     if( is_null( p ) ) return q;
     return cons( car(p), append( cdr(p), q ));
}

list reverse( list p )
{
     if( is_null(p) || is_atom(p) ) return p;
     return append( reverse( cdr(p) ), cons(car(p), null() )) ;
}

bool is_lat (list p)
{
    if(is_null(p))
        return true;
    if (is_atom(car(p)))
        return is_lat(cdr(p));
    return false;
}

bool member (list p, list q)
{
    if (is_null(q))
        return false;
    if (is_atom(car(q))) {
        if (eq(p, car(q)))
            return true;
        return member(p, cdr(q));
    }
    return member(p, car(q)) || member(p, cdr(q));
}

list last ( list p )
{
     if (is_null(cdr(p)))
          return car(p);
     return last(cdr(p));
}

list list_pair( list p, list q )
{
    if (is_null(p) || is_null(q))
        return null();
    return cons(cons(car(p), cons(car(q), null())), list_pair(cdr(p), cdr(q)));

}

list firsts( list p )
{
    if (is_null(p))
        return null();
    return cons(car(car(p)), firsts(cdr(p)));
}

list flat ( list p )
{
    if (is_null(p))
        return null();
    if (is_atom(car(p)))
        return cons(car(p), flat(cdr(p)));
    return append(flat(car(p)),flat(cdr(p)));
}

bool two_the_same ( list p, list q )
{
    if (is_null(p))
        return false;
    if (is_atom(car(p))) {
        if (member(car(p),q))
            return true;
        else
            return two_the_same(cdr(p),q);
    }
    
    return two_the_same(car(p),q) || two_the_same(cdr(p),q);
}

bool equal ( list p, list q) {

  if (is_null(p) || is_null(q)) {
        if (is_null(p) && is_null(q))
            return true;
        else
            return false;
  }

    if (is_atom(car(p))) {

        if (is_atom(q))
            return false;

        if (is_atom(car(q))) {
            if (eq(car(p), car(q))) {
                return equal(cdr(p), cdr(q));
            } else
                return false;
        } else {
            return false;
        }
    }
    return equal(car(p), car(q)) && equal(cdr(p), cdr(q));
}

list total_reverse ( list p )
{
    if (is_null(p) || is_atom(p))
        return p;

    if (is_atom(car(p)))
        return append( total_reverse(cdr(p)), cons(car(p), null()));

    return append (total_reverse(cdr(p)), cons(total_reverse(car(p)), null()));
}

list shape ( list p )
{
    if (is_null(p))
        return null();
    if (is_atom(car(p)))
        return shape(cdr(p));
    return cons(shape(car(p)), shape(cdr(p)));
}

list intersection ( list p, list q )
{
    if ( is_null(p))
        return null();
    if (member(car(p), q))
        return cons(car(p),intersection(cdr(p),q));
    return intersection(cdr(p), q);
}

list list_union ( list p, list q )
{   // both lists must be list of atoms ( a b c ) etc.
    // and can not have duplicates in either list ( a a b c )

    if (is_null(p))
        return q;
    if (member(car(p), q))
        return list_union(cdr(p), q);
    return cons(car(p), list_union(cdr(p), q));
}
