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

class WordData
{
  public:
  int GetNumVowels () const;
  int GetNumConsonants () const;
  int GetNumDigits () const;
  int GetNumSpecialChars () const;

  WordData & operator = (const WordData & OtherWord);
  bool operator == (const WordData & OtherWord) const;
  WordData operator + (const WordData & OtherWord) const;
  friend istream & operator >> (istream & ins, WordData & w);
  friend ostream & operator << (ostream & outs, const WordData & w);

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

// Implementation

/*WordData & WordData::operator = (const WordData & OtherWord)
{
  // Test for self-assignment. If this and the address of OtherWord
  // are the same, return the object refrenced by thid:
  if (this == &OtherWord)
    {
      return * this;
    }

  // Copy the attributes of OtherWord into the corresponding
  // attributes of this.
  word = OtherWord.word;
  vowels = OtherWord.vowels;
  consonants = OtherWord.consonants;
  digits = OtherWord.digits;
  specialchars = OtherWord.specialchars;

  // Return the object refrenced by this;
  return * this;

}

bool WordData::operator == (const WordData & OtherWord) const
{
  if ( word == OtherWord.word)
    {
      return true;
    }
  return false;
}

WordData WordData::operator + (const WordData & OtherWord) const
{
  WordData sum;
  sum.word = word + OtherWord.word;
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



  
  



*/  
#endif
