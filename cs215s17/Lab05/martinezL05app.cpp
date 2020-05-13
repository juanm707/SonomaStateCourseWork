// Title: Lab 5 Driver program
// Author: Dr. Watts
// Modified by: Juan Martinez
// Description: This program is designed to test the WordData class.

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstdlib>
#include "martinezL05.h"

using namespace std;

const int MINWORDS = 20;
const int BLOCKSIZE = 10;

int ReadFile (string filename, WordData * & Words);
void WriteReport (ostream & output, WordData Words [], int count);
void Swap (WordData & a, WordData & b);
void WordSort (WordData W [], int count);

int main (int argc, char * argv [])
{ // This function will open the file when the file name is passed
  // as an argument. It will then call functions to read the file
  // and write a short report about the words read from the file.
	if (argc < 2)
	{
		cout << "Usage: " << argv[0] << " <filename>\n";
		exit (1);
	}
	int count = 0;
	WordData * W = NULL;
	count = ReadFile (argv[1], W);
	WordSort (W, count);
	WriteReport (cout, W, count);
	return 0;
}
				
int ReadFile (string filename, WordData * & Words)
{ // This function will read each of thewords from the file
  // passed to it into a temporary string. The string will be
  // stored in the next available space in the array. If more
  // space is needed, this function will resize the storage
  // array. After all of the words have been read and stored,
  // this function will return the count of the number of
  // words read from the file. 
	ifstream input (filename.c_str());
	if (input.fail())
	{
		cout << "File: " << filename << " not found\n";
		exit (2);
	}
	Words = new WordData [MINWORDS];
	int size = MINWORDS;
	int count = 0;
	string aword;
	while (input >> aword)
	{
		if (count >= size)
		{
			cout << "Expanding array; count = " << count << "\n";
			// Allocate larger array
			WordData * temp = new WordData [size + BLOCKSIZE];
			// Copy data from old array to new array
			for (int i = 0; i < size; i++)
				temp[i] = Words[i];
			// Delete old array
			delete [] Words;
			// Point to new array
			Words = temp;
			size += BLOCKSIZE;
		}
		// Store new word in arry
		Words[count].SetWord (aword);
		// Increment count
		count++;
	}
	input.close();
	return count;
}

void WriteReport (ostream & output, WordData Words [], int count)
{ // This function writes a short report about the words
  // in the array. The report will be written to the 
  // output stream passed to this function.
        // Print report header
  int vowelTotal = 0;
  int conTotal = 0;
  int digitTotal = 0;
  int specialTotal = 0;
  
        output << setw (15) << left << "Word";
        output << setw (8) << right << "Vowels";
        output << setw (8) << right << "Const.";
        output << setw (8) << right << "Digits";
        output << setw (8) << right << "Special";
        output << endl;
        // Loop through all words in array
        for (int i = 0; i < count; i++)
        {
	  vowelTotal += Words[i].GetNumVowels ();
	  conTotal += Words[i].GetNumConsonants ();
	  digitTotal += Words[i].GetNumDigits ();
	  specialTotal += Words[i].GetNumSpecialChars ();
	  
        // Print data for word
                Words[i].WriteData(output);
                output << endl;
        }
	// Print the report summary
	output << setw (15) << left << " ";
	output << setw (8) << right << "---";
	output << setw (8) << right << "---";
	output << setw (8) << right << "---";
	output << setw (8) << right << "---" << endl;
	
	output << setw (15) << left << "Totals";
	output << setw (8) << right << vowelTotal;
	output << setw (8) << right << conTotal;
	output << setw (8) << right << digitTotal;
	output << setw (8) << right << specialTotal << endl;
}
 
void Swap (WordData & a, WordData & b)
{ // This function will swap the contents of 2 WordData objects
	WordData temp = a;
	a = b;
	b = temp;
}

void WordSort (WordData W [], int count)
{ // This function will sort the objects in the array W into
  // ascending order using the insertion sort.

	for (int i = 1; i < count; i++)
		for (int j = i; j > 0 && W[j-1] > W[j]; j--)
			Swap (W[j], W[j-1]);
}

