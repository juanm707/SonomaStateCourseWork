// Assignment : Lab 02
// File : martinezL02b.cpp
// Author : Juan Martinez
// Date : Spring 2017
// Description : This program will count the number of
// vowels, consonants, digits, and special characters
// in a word, and display it on the screen next to the word.

#include <iostream>
#include <fstream>

using namespace std;

bool isvowel (char aletter);

int main ()
{
  ifstream input;
  string aword;
  

  input.open ("words.txt");
  while (input >> aword)
    {
      int vowelcount = 0;
      int conCount = 0;
      int digitCount = 0;
      int specialCount = 0;

      // Counter variable.
      int i = 0;
      
      while (i < aword.length())
	{
	  if (isvowel(aword[i]))
	    {
	      vowelcount++;
	    }
	  else if (isdigit(aword[i]))
	    {
	      digitCount++;
	    }
	  
	  else if (isalpha(aword[i]))
	    {
	      conCount++;
	    }
	  else
	    {
	      specialCount++;
	    }
	      
	  i++;
	}
      
      cout << aword << '\t' << aword.length()
	   << '\t' << vowelcount << '\t' <<  conCount
	   << '\t' << digitCount << '\t' << specialCount << endl;
    }
 
  return 0;
}

bool isvowel (char aletter)
{
  char upcase = toupper (aletter);
  if (upcase == 'A' || upcase == 'E' || upcase == 'I'
      || upcase == 'O' || upcase == 'U')
              return true;
  
  return false;
}

