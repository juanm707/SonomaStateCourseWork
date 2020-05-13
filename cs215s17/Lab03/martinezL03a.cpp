// Assignment :
// File :
// Author :
// Date :
// Description :

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>

using namespace std;

bool isvowel (char aletter);

// MAXWORDS contains the maximum number of words
const int MAXWORDS = 100;

int main ()
{
  
  // Declare and open an input file
  ifstream input;
  input.open ("words.txt");
  
  // Array for storing words
  string words [MAXWORDS];
  
  // Read the words in the file into the array
  int count = 0;
  while (input >> words[count])
    {
      count++;
    }

  cout << count << " words read from the file\n";
  
  // Close the input file
  input.close ();
  
  // Write the words and their vowel, consonant, digit
  // and special characters counts.
  
  // Starting with the last word in the array.
  int w = count - 1;
  while (w >= 0)
    {
      cout << words[w] << '\t';
      // Analyze the letters in the word
      int vowelcount = 0;
      int conCount = 0;
      int digitCount = 0;
      int specialCount = 0;

      // Counter variable
      int i = 0;
      
      while (i < words[w].length())
	{
	  
	
      //Write the vowel, consonant, digit and special character
      // counts. Separate the parts of the line with tabs.
	  if (isalpha(words[w][i]))
	    {
	      if (isvowel(words[w][i]))
		{
		  vowelcount++;
		}
	      else
		{
		  conCount++;
		}
	    }
	  else if (isdigit(words[w][i]))
	    {
	      digitCount++;
	    }
	  else
	    {
	      specialCount++;
	    }
	  
	  i++;
	}
      cout << vowelcount << '\t' << conCount
	   << '\t' << digitCount << '\t' << specialCount << endl;
      
      w--;
    }
  
  
  // Starting with the first word in the array.
  w = 0;
  while (w < count)
    {
      cout << words[w] << '\t';
      
      // Analyze the letters in the word
      int vowelcount = 0;
      int conCount = 0;
      int digitCount = 0;
      int specialCount = 0;

      // Counter variable
      int i = 0;

      while (i < words[w].length())
	{
      
      // Write the vowel, consonant, digit and special character
      // counts. Separate the parts of the line with tab.
	  if (isalpha(words[w][i]))
	    {
	      if (isvowel(words[w][i]))
		{
		  vowelcount++;
		}
	      else
		{
		  conCount++;
		}
	    }
	  else if (isdigit(words[w][i]))
	    {
	      digitCount++;
	    }
	  else
	    {
	      specialCount++;
	    }

	  i++;
	}
      cout << vowelcount << '\t' << conCount
	   << '\t' << digitCount << '\t' << specialCount << endl;

      w++;
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
  
