// Title: Lab 7 Worddata class and implementation
// Author: Juan Martinez
// Description:

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

WordData::~WordData ()
{
  if (testing)
    {
      cout << "The destructor has been called "
	   << "for the address: " << this << endl;
    }

  delete [] word;
  
}

bool isvowel (char aletter)
{
  char upcase = toupper (aletter);
  if (upcase == 'A' || upcase == 'E' || upcase == 'I'
      || upcase == 'O' || upcase == 'U')
    return true;

  return false;
}

void WordData::SetWord (const string & InWord)
{
  if (testing)
    {
      cout << "The SetWord constructor has been called "
	   << "for the address: " << this << endl;
    }

  delete [] word;
  length = Inword.length();
  word = new char [1 + length];
  strcpy = (word, InWord.c_str());
  
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

string WordData::GetWord () const
{
  if (testing)
    {
      cout << "The GetWord constructor has been called "
	   << "for the address: " << this << endl;
    }
      
  return word;
}


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

int WordData::GetNumVowels () const
{
  return vowels;
}

int WordData::GetNumConsonants () const
{
  return consonants;
}

int WordData::GetNumDigits () const
{
  return digits;
}

int WordData::GetNumSpecialChars () const
{
  return specialchars;
}

bool WordData::operator > (const WordData & OtherWord) const
{
  if (word.length() > OtherWord.GetWord().length())
    {
      return true;
    }
  else if (word.length() < OtherWord.GetWord().length())
    {
      return false;
    }
  else if (word.length() == OtherWord.GetWord().length())
    {
      if (word > OtherWord.GetWord())
	{
	  return true;
	}
      else if (word <= OtherWord.GetWord())
	{
	  return false;
	}
    }
}

bool WordData::operator < (const WordData & OtherWord) const
{
  if (length < OtherWord.length())
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

bool WordData::operator == (const WordData & OtherWord) const
{
  if (strcmp (word, OtherWord.word) == 0)
    {
      return true;
    }
  return false;
}

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

ostream & operator << (ostream & outs, const WordData & w)
{
  outs << setw(12) << left << w.word;
  outs << setw(8) << right << w.vowels;
  outs << setw(8) << right << w.consonants;
  outs << setw(8) << right << w.digits;
  outs << setw(8) << right << w.specialchars;

  return outs;
}

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

WordData::WordData (const string & InWord)
{
  length = 0;
  word = new char[1];
  word[0] = '\0';
  vowels = consonants = digits = specialchars = 0;
  
  SetWord (InWord);
}
