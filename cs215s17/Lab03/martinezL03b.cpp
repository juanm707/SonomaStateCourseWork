// Assignment : Lab 03
// File : martinezL03b.cpp
// Author : Juan Martinez
// Date : Spring 2017
// Description : This program will read a list of words from a file
// called "words.txt". It will then display them vertically
// and with each count of vowels, consonants, digits, and special characters.
// It then displays the total amount of each, and then lists words
// alphabetically and with the same info.

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>

using namespace std;

// MAXWORDS contains the maximum number of words
const int MAXWORDS = 100;

// Definition of the worddata structure
struct worddata
{
  worddata ();
  string word;
  int vowels;
  int consonants;
  int digits;
  int specialchars;
};


// Prototypes for functions used by this program

int ReadFile (ifstream & input, worddata Words []);
void WriteReport (ostream & output, worddata Words [], int count);
void Swap (worddata & a, worddata & b);
void WordSort (worddata Words [], int N);
bool isvowel (char aletter);


int main ()
{
  // Declare an input file and open "words.txt"
  ifstream input;
  input.open ("words.txt");

  if (input.fail())
    {
      cout << "File: words.txt not found\n";
      exit (1);
    }
  
  // Declare an array of worddata objects to hold the words
  // and their vowel, consonant, digit, and special
  // character counts.
  worddata WordArray [MAXWORDS];
  
  // Call the ReadFile function to read the file, store the
  // words in the array and return the number of words read
  // from the file.
  int count = ReadFile (input, WordArray);
  cout << count << " words read from the file\n";
  
  // Call the WriteReport function to write the data
  // stored in the array in a formatted fashion.
  WriteReport (cout, WordArray, count);
  
  // Call the WordSort function to sort the words into
  // alphabetical order.
  WordSort (WordArray, count);
  
  // Call the WriteReport function to write the data
  // stored in the array in a formatted fashion.
  WriteReport (cout, WordArray, count);

  
  return 0;

}

// Implementations for functions used by this program
worddata::worddata ()
{
  vowels = 0;
  consonants = 0;
  digits = 0;
  specialchars = 0;
}

int ReadFile (ifstream & input, worddata Words [])
{
  int count = 0;
  while (input >> Words[count].word)
    {
      for (int i = 0; i < Words[count].word.length(); i++)
	{
	  if (isalpha (Words[count].word[i]))
	    {
	      if (isvowel (Words[count].word[i]))
		{
		  Words[count].vowels++;
		}
	      else
		{
		  Words[count].consonants++;
		}
	    }
	  else if (isdigit (Words[count].word[i]))
	    {
	      Words[count].digits++;
	    }
	  else
	    {
	      Words[count].specialchars++;
	    }
	}
      count++;
    }
  
  input.close();
  return count;

}

void WriteReport (ostream & output, worddata Words [], int count)
{
  int totalvowels = 0, totalconsonants = 0;
  int totaldigits = 0, totalspecialchars = 0;

  output << setw (12) << left << "Words";
  output << setw (8) << right << "Vowels";
  output << setw (8) << "Const.";
  output << setw (8) << "Digits";
  output << setw (8) << "Special" << endl;

  // Counter variable
  int w = 0;
  while (w < count)
    {
    
      output << setw(12) << left << Words[w].word;
      output << setw(8) << right << Words[w].vowels;
      output << setw(8) << Words[w].consonants;
      output << setw(8) << Words[w].digits;
      output << setw(8) << Words[w].specialchars << endl;
      
      totalvowels += Words[w].vowels;
      totalconsonants += Words[w].consonants;
      totaldigits += Words[w].digits;
      totalspecialchars += Words[w].specialchars;

      w++;
    }

      output << setw(12) << left << ' ';
      output << setw(8) << right << "---";
      output << setw(8) << "---";
      output << setw(8) << "---";
      output << setw(8) << "---" << endl;

      output << setw(12) << left << "Totals";
      output << setw(8) << right << totalvowels;
      output << setw(8) << totalconsonants;
      output << setw(8) << totaldigits;
      output << setw(8) << totalspecialchars << endl;
    
}

void Swap (worddata & a, worddata & b)
{
  worddata temp;
  temp = a;
  a = b;
  b = temp;
  
}

void WordSort (worddata Words [], int N)
{
  int i = 1;
  while (i < N)
    {
      int j = i;
      while (j > 0 && Words[j].word < Words[j-1].word)
	{
	  Swap (Words[j], Words [j-1]);
	  j--;
	}
      i++;
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
