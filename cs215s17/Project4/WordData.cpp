//////////////////////////////////////////////////////////////////
// Project: Project 4                                           //
// File: WordData.cpp                                           //
// Author: Juan Martinez                                        //
// Class: CS215 Spring 2017                                     //
// Description: Implementation for WordData class.              //    
//////////////////////////////////////////////////////////////////

#include <cstring>
#include <string>
#include <iostream>
#include <iomanip>
#include "WordData.h"

using namespace std;

// Prototype
bool isvowel (char aletter);
const bool testing = false;

// Function implementations will be placed after this line

//////////////////////////////////////////////////////////////////
// Function: WordData ()                                        //
// Parameters: none                                             //
// Return value: none                                           //
// Description: This function is the default constructor for a  //
// WordData object. Lengtho is set to 0, and word to a new array//
// with a end line character. Data also set to 0.               //
//////////////////////////////////////////////////////////////////    

WordData::WordData ()
{
  // The default constructor
  if (testing)
    {
      cout << "The default constructor has been called "
	   << "for address: " << this << endl;
    }

  length = 0;
  word = new char[1];
  word[0] = '\0';
  vowels = consonants = digits = specialchars = 0;
 
}

//////////////////////////////////////////////////////////////////
// Function: WordData (const WordData & OtherWord)              //
// Parameters: OtherWord = other WordData object                //
// Return value: none                                           //
// Description: This function is the copy constructor for a     //
// WordData object. Lengtho is set to other word length,        //
// Data also set to otherwords data.                            //
//////////////////////////////////////////////////////////////////         

WordData::WordData (const WordData & OtherWord)
{
  if (testing)
    {
      cout << "The copy constructor has been called "
	   << "for the address: " << this << endl;
    }

  length = OtherWord.length;
  word = new char [1 + length];
  strcpy (word, OtherWord.word);
  
  vowels = OtherWord.vowels;
  consonants = OtherWord.consonants;
  digits = OtherWord.digits;
  specialchars = OtherWord.specialchars;
}

//////////////////////////////////////////////////////////////////
// Function: ~WordData ()                                       //
// Parameters: none                                             //
// Return value: none                                           //
// Description: This function is the deconstructor for a        //
// WordData object.                                             //
////////////////////////////////////////////////////////////////// 

WordData::~WordData ()
{
  if (testing)
    {
      cout << "The destructor has been called "
	   << "for the address: " << this << endl;
    }

  delete [] word;
}

//////////////////////////////////////////////////////////////////
// Function: isvowel (char aletter)                             //
// Parameters: char - aletter                                   //
// Return value: bool                                           //
// Description: This function checks if a letter is a vowel.    //
////////////////////////////////////////////////////////////////// 

bool isvowel (char aletter)
{
  char upcase = toupper (aletter);
  if (upcase == 'A' || upcase == 'E' || upcase == 'I'
      || upcase == 'O' || upcase == 'U')
    return true;

  return false;
}

/////////////////////////////////////////////////////////////////
// Function: SetWord (const string & InWord)                   //
// Parameters: string & InWord                                 //
// Return value: none                                          //
// Description: Sets word to the word passed by InWord, and    //
// updates all the data values using the new word.             //
/////////////////////////////////////////////////////////////////

void WordData::SetWord (const string & InWord)
{
  if (testing)
    {
      cout << "The SetWord constructor has been called "
	   << "for the address: " << this << endl;
    }

  delete [] word;
  length = InWord.length();
  word = new char [1 + length];
  strcpy (word, InWord.c_str());
  
  vowels = 0;
  consonants = 0;
  digits = 0;
  specialchars = 0;
    
  for (int i = 0; i < length; i++)
    {
      if (isalpha (word[i]))
	switch (toupper (word[i]))
	  {
	  case 'A': case 'E': case 'I':
	  case 'O': case 'U':
	    vowels++; break;
	  default:
	    consonants++;
	  }
      
      else if (isdigit (word[i]))
	{
	  digits++;
	}
      else
	{
	  specialchars++;
	}
    }  
}

//////////////////////////////////////////////////////////////////
// Function: GetWord () const                                   //
// Parameters: none                                             //
// Return value: string                                         //
// Description: This function returns the word for the object.  //
//////////////////////////////////////////////////////////////////

string WordData::GetWord () const
{
  if (testing)
    {
      cout << "The GetWord constructor has been called "
	   << "for the address: " << this << endl;
    }
      
  return word;
}

//////////////////////////////////////////////////////////////////
// Function: WriteData (ostream & outs) const                   //
// Parameters: Output stream outs                               //
// Return value: void                                           //
// Description: This function outputs the word, and its data    //
// in a specific format.                                        //
//////////////////////////////////////////////////////////////////

void WordData::WriteData (ostream & outs) const
{
  if (testing)
    {
      cout << "The Write Data constructor has been called "
	   << "for the address: " << this << endl;
    }
  
 
  outs << setw(15) << left << word;
  outs << setw(8) << right << vowels;
  outs << setw(8) << consonants;
  outs << setw(8) << digits;
  outs << setw(8) << specialchars;
  

}

//////////////////////////////////////////////////////////////////
// Function: GetNumVowels () const                              //
// Parameters: none                                             //
// Return value: int                                            //
// Description: This function returns the number of vowels in word
//////////////////////////////////////////////////////////////////

int WordData::GetNumVowels () const
{
  return vowels;
}

//////////////////////////////////////////////////////////////////
// Function: GetNumConsonants () const                          //
// Parameters: none                                             //
// Return value: int                                            //
// Description: This function returns the number of consonants  //
// in word                                                      //
////////////////////////////////////////////////////////////////// 

int WordData::GetNumConsonants () const
{
  return consonants;
}

//////////////////////////////////////////////////////////////////
// Function: GetNumDigits () const                              //
// Parameters: none                                             //
// Return value: int                                            //
// Description: This function returns the number of digits in word
////////////////////////////////////////////////////////////////// 

int WordData::GetNumDigits () const
{
  return digits;
}

//////////////////////////////////////////////////////////////////
// Function: GetNumSpecialChars () const                        //
// Parameters: none                                             //
// Return value: int                                            //
// Description: This function returns the number of special chars/
// in word.                                                     //
////////////////////////////////////////////////////////////////// 

int WordData::GetNumSpecialChars () const
{
  return specialchars;
}

//////////////////////////////////////////////////////////////////
// Function: operator > (const WordData & OtherWord) const      //
// Parameters: WordData object "OtherWord"                      //
// Return value: bool                                           //
// Description: This function determnines wether word's length is/
// greater than OtherWord's length. If same length, then it checks
// alphabetically by letter.                                    //
//////////////////////////////////////////////////////////////////

bool WordData::operator > (const WordData & OtherWord) const
{
  if (length > OtherWord.length)
    {
      return true;
    }
  if (length < OtherWord.length)
    {
      return false;
    }

  string a = word;
  for (int i = 0; i < a.length(); i++)
    {
      a[i] = tolower(a[i]);
    }

  string b = OtherWord.word;
  for (int i = 0; i < b.length(); i++)
    {
      b[i] = tolower(b[i]);
    }
  return a > b;
  
}

//////////////////////////////////////////////////////////////////
// Function: operator < (const WordData & OtherWord) const      //
// Parameters: WordData object "OtherWord"                      //
// Return value: bool                                           //
// Description: This function determnines wether word's length is/
// less than OtherWord's length. If same length, then it checks //
// alphabetically by letter.                                    //
//////////////////////////////////////////////////////////////////  

bool WordData::operator < (const WordData & OtherWord) const
{
  if (length < OtherWord.length)
    {
      return true;
    }

  if (length > OtherWord.length)
    {
      return false;
    }
  string one = word;
  for (int i = 0; i < one.length(); i++)
    {
      one[i] = tolower(one[i]);
    }

  string two = OtherWord.word;
  for (int i = 0; i < two.length(); i++)
    {
      two[i] = tolower(two[i]);
    }

  return one < two;

}

//////////////////////////////////////////////////////////////////
// Function: operator = (const WordData & OtherWord)            //
// Parameters: WordData object "OtherWord"                      //
// Return value: WordData                                       //
// Description: Test for self-assignment. If this and the       //
// address of OtherWord are the same, return the object         //
// refrenced by this. Delete the existing word. Copy the length //
// of OtherWord. Allocate space for the new word. Copy the new  //
// word from OtherWord into word. Copy the remaining attributes //
// of OtherWord into the corresponding attributes of this.      //
// Return the object refrenced by this.                         //
//////////////////////////////////////////////////////////////////  

WordData & WordData::operator = (const WordData & OtherWord)
{
  // Test for self-assignment. If this and the address of OtherWord
  // are the same, return the object refrenced by thid:
  if (this == &OtherWord)
    {
      return * this;
    }

  // Delete the existing word
  delete [] word;

  // Copy the length of OtherWord
  length = OtherWord.length;

  // Allocate space for the new word
  word = new char [1 + length];

  // Copy the new word from OtherWord into word
  strcpy(word, OtherWord.word);
  

  // Copy the remaining attributes of OtherWord into the
  // corresponding attributes of this.
  vowels = OtherWord.vowels;
  consonants = OtherWord.consonants;
  digits = OtherWord.digits;
  specialchars = OtherWord.specialchars;

  // Return the object refrenced by this;
  return * this;

}

//////////////////////////////////////////////////////////////////
// Function: operator == (const WordData & OtherWord) const     //
// Parameters: WordData object "OtherWord"                      //
// Return value: bool                                           //
// Description: Returns true if the words are the same.         //
//////////////////////////////////////////////////////////////////    

bool WordData::operator == (const WordData & OtherWord) const
{
  if (strcmp (word, OtherWord.word) == 0)
    {
      return true;
    }
  return false;
}

//////////////////////////////////////////////////////////////////
// Function: operator != (const WordData & OtherWord) const     //
// Parameters: WordData object "OtherWord"                      //
// Return value: bool                                           //
// Description: Returns true if the words are different.        //
//////////////////////////////////////////////////////////////////       

bool WordData::operator != (const WordData & OtherWord) const
{
  if (strcmp ( word, OtherWord.word) == 0)
    {
      return false;
    }
  return true;
}

//////////////////////////////////////////////////////////////////
// Function: operator + (const WordData & OtherWord) const      //
// Parameters: WordData object "OtherWord"                      //
// Return value: WordData                                       //
// Description: Returns one word that is a combination of two   //
// words.                                                       //
//////////////////////////////////////////////////////////////////       

WordData WordData::operator + (const WordData & OtherWord) const
{
  WordData sum;
  sum.length = length + OtherWord.length;
  sum.word = new char [1 + sum.length];
  strcpy (sum.word, word);
  strcat (sum.word, OtherWord.word);
  
  sum.vowels = vowels + OtherWord.vowels;
  sum.consonants = consonants + OtherWord.consonants;
  sum.digits = digits + OtherWord.digits;
  sum.specialchars = specialchars + OtherWord.specialchars;

  return sum;
}

//////////////////////////////////////////////////////////////////
// Function: operator << (ostream & outs, const WordData & w)   //
// Parameters: Output stream outs, WordData object w            //
// Return value: ostream                                        //
// Description: This function outputs the word, and its data    //
// in a specific format.                                        //
//////////////////////////////////////////////////////////////////  

ostream & operator << (ostream & outs, const WordData & w)
{
  outs << setw(12) << left << w.word;
  outs << setw(8) << right << w.vowels;
  outs << setw(8) << right << w.consonants;
  outs << setw(8) << right << w.digits;
  outs << setw(8) << right << w.specialchars;

  return outs;
}

//////////////////////////////////////////////////////////////////
// Function: operator >> (istream & ins, WordData & w)          //
// Parameters: Istream ins, WordData w                          //
// Return value: istream                                        //
// Description: This function reads in a word, and calls SetWord//
// to store word in the WordData object.                        //
//////////////////////////////////////////////////////////////////  

istream & operator >> (istream & ins, WordData & w)
{
  string astring;
  ins >> astring;

  if (!ins.fail())
    {
      w.SetWord(astring);
    }

  return ins;
}

//////////////////////////////////////////////////////////////////
// Function: WordData (const string & InWord)                   //
// Parameters: string InWord                                    //
// Return value: void                                           //
// Description: This function creates a WordData object that    //
// takes the word InWord as a parameter and stores it in object.//
//////////////////////////////////////////////////////////////////  

WordData::WordData (const string & InWord)
{
  length = 0;
  word = new char[1];
  word[0] = '\0';
  vowels = consonants = digits = specialchars = 0;
  
  SetWord (InWord);
}
