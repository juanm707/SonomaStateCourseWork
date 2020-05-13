// Title: Lab 4 Worddata class and implementation
// Author: Juan Martinez
// Description:

#ifndef WORDDATA
#define WORDDATA
#include <cstring>
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

// Prototype
bool isvowel (char aletter);
const bool testing = false;


class WordData
{
 public:
  int GetNumVowels () const;
  int GetNumConsonants () const;
  int GetNumDigits () const;
  int GetNumSpecialChars () const;

  bool operator > (const WordData & OtherWord) const;
 
  WordData ();
  WordData (const WordData & OtherWord);
  ~WordData ();
  void SetWord (const string & InWord);
  string GetWord () const;
  void WriteData (ostream & outs) const;
 private:
  string word; // C++ string to hold the word
  int vowels; // Vowel counter
  int consonants; // consonant counter
  int digits; // digit counter
  int specialchars; // special character counter
};

// Function implementations will be placed after this line

WordData::WordData ()
{
  // The default constructor
  if (testing)
    {
      cout << "The default constructor has been called "
	   << "for address: " << this << endl;
    }
  
  vowels = 0;
  consonants = 0;
  digits = 0;
  specialchars = 0;
}

WordData::WordData (const WordData & OtherWord)
{
  if (testing)
    {
      cout << "The copy constructor has been called "
	   << "for the address: " << this << endl;
    }
  
  word = OtherWord.word;
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
  
  word = InWord;
  
  for (int i = 0; i < word.length(); i++)
    {
      if (isalpha (word[i]))
	{
	  if (isvowel (word[i]))
	    {
	      vowels++;
	    }
	  else
	    {
	      consonants++;
	    }
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


#endif
