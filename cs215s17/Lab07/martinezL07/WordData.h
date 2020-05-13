// Title: Lab 7 Worddata class and implementation
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

  WordData (const string & InWord);

  bool operator > (const WordData & OtherWord) const;
  bool operator < (const WordData & OtherWord) const;
 
  WordData ();
  WordData (const WordData & OtherWord);
  ~WordData ();
  void SetWord (const string & InWord);
  string GetWord () const;
  void WriteData (ostream & outs) const;
  private:

  int length;
  char * word; // C++ string to hold the word
  int vowels; // Vowel counter
  int consonants; // consonant counter
  int digits; // digit counter
  int specialchars; // special character counter
};
  
#endif
