////////////////////////////////////
// Author:     Dr. Kooshesh       //
// Student:    Juan Martinez      //
// Term:       Fall 2017          //
// Course:     CS 315             //
// Assignment: Project 2          //
// Date:       9/28/17            //
// Professor:  Dr. Kooshesh       //
// File:       lex.cpp            //
////////////////////////////////////

#include<ctype.h>
#include<string.h>
#include<stdlib.h>
#include "lex.hpp"

const int ATOM_NAME_LEN = 9;
tokens last_token;
char name[ATOM_NAME_LEN];
int get_new_token = 1;   // unget_token has not been called yet.

using namespace std;

void unget_token()
{
     get_new_token = 0;
}

tokens get_token( char s[] )
{
     if( ! get_new_token ) {
	  strcpy( s, name );
	  get_new_token = 1;
	  return last_token;
     }
     char c;
     cin >> c;  // skip spaces and get a character.
     if( cin.eof() ) return END_OF_TEXT;
     if( c == LPAREN ) {
	  last_token = LPAREN;
	  return LPAREN;
     }
     if( c == RPAREN ) {
	  last_token = RPAREN;
	  return RPAREN;
     }
     int i;
     for(i = 0; cin.good() && isalpha( c ) && i < MAX_ATOM_LEN; i++ ) {
	  s[i] = c;
	  cin.get(c);
     }
     if( i == 0 ) {
	  cout << "\nUnrecongnized lexical item:" << c << endl;
	  exit( 1 );
     }
     s[i] = '\0';
     if( cin.good() ) cin.putback(c);
     last_token = ATOM;
     strcpy( name, s );
     return ATOM;
}
