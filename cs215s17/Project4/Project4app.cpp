//////////////////////////////////////////////////////////////////
// Project: Project 4                                           //
// File: Project4.cpp                                           //
// Author: Juan Martinez                                        //
// Class: CS215 Spring 2017                                     //
// Description: Sample file for testing OrderedSet and WordData //
//////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include "OrderedSet.hpp"
#include "WordData.h"
using namespace std;

int WordDataTest (string file);

int main (int argc, char * argv [])
{
  WordDataTest(argv[1]);
  //  cout << "Creating new set" << endl;
  // WordDataTest("words2.txt");
  return 0;
}

int WordDataTest(string file)
{
  cout << "Testing OrderedSet with WordData:\n\n";
  ifstream input (file.c_str());
  WordData oneword;
  OrderedSet<WordData> WD;
  while (input >> oneword)
    WD.Insert(oneword);
  input.close();
  // Iterator
  OrderedSet<WordData>::Iterator itr;
  cout << "From first to last:\n";
  for (itr = WD.begin(); itr != WD.end(); itr++)
    {
      cout << "\t" << *itr << endl;
    }
  
  cout << "From last to first:\n";
  for (itr = WD.rbegin(); itr != WD.rend(); --itr)
    cout << "\t" << *itr << endl;
  cout << "Size of WordData set WD: " << WD.Size() << endl;
  cout << "Deleting first word... WD[0] " << endl;
  cout << WD[0] << endl;
  WD.Delete(WD[0]);
  WD.Delete(WD[7]);
  cout << "First word in set is now WD [0]: " << endl;
  cout << WD[0] << endl;
  cout << WD[7] << endl;
  // is Empty
  cout << "Is set empty? ";
  if (WD.IsEmpty())
    cout << "yes" << endl;
  else
    cout << "no" << endl;
  cout << "Adding word: pizza" << endl;
  // SetWord
  oneword.SetWord("pizza");
  WD.Insert(oneword);
  // Is in
  if (WD.IsIn(oneword))
    cout << "pizza is in" << endl;
  else
    cout << "no pizza" << endl;
  cout << "Last word is: " << endl;
  // GetWord
  cout << WD[WD.Size() - 1].GetWord() << endl;
  OrderedSet<WordData> Add;
  oneword.SetWord("Sonoma");
  Add.Insert(oneword);
  oneword.SetWord("State");
  Add.Insert(oneword);
  WD.Insert(oneword);
  // Adding sets, multiplying sets..
  cout << "Set one is addition of sets...\n";
  cout << "Set two is multiplication of sets...\n";
  OrderedSet<WordData> one = WD + Add;
  OrderedSet<WordData> two = WD * Add;
  
  for (int i = 0; i < one.Size(); i++)
    cout << "One: " << one[i] << endl;
  for (int i = 0; i < two.Size(); i++)
    cout << "Two: " << two[i] << endl;
  //Copy constructor
  WordData cons = WD[0];
  cout << cons << endl;
  //GetNum(Vowels, consonants, digits, specialchars)
  int totalV = 0;
  int totalC = 0;
  int totalD = 0;
  int totalS = 0;
  for (int i = 0; i < WD.Size(); i++)
    {
      totalV += WD[i].GetNumVowels();
      totalC += WD[i].GetNumConsonants();
      totalD += WD[i].GetNumDigits();
      totalS += WD[i].GetNumSpecialChars();
    }
  cout << "Total vowels: " << totalV << endl;
  cout << "Total consonants: " << totalC << endl;
  cout << "Total digits: " << totalD << endl;
  cout << "Total special chars: " << totalS << endl;
  //Assignment operator
  cout << "WD[0]: " << WD[0] << endl;
  WD[0] = WD[1];
  cout << "WD[0] now: " << WD[0] << endl;
  // Equality Operator
  cout << "Is WD[0] = to WD[1]?" << endl;
  if (WD[0] == WD[1])
    cout << "YES\n";
  else
    cout << "NO\n";
  // < operator
  cout << "Is WD[0] < than the last word?\n";
  if (WD[0] < WD[WD.Size() - 1])
    cout << "YES\n";
  else
    cout << "NO\n";
  //Adding words
  cout << "Adding second to last and last word\n";
  WordData add = WD[WD.Size() - 2] + WD[WD.Size() - 1];
  cout << "New word is: " << add << endl;
  //exception
  cout << "Testing exceptions\n";
  
  try
    {
      OrderedSet<WordData>::Iterator itr2 = WD.end();
      WordData check = *itr2;
      cout << check;
    }
  catch (OrderedSet<WordData>::Exception E)
    {
      cerr << "Exception: " << E.Message() << endl;
    }
      
  try
    {
      cout << WD[WD.Size()] << endl;
    }
  catch (OrderedSet<WordData>::Exception E)
    {
      cerr << "Exception: " << E.Message() << endl;
    }

  //Ordered set assignment operator =
  OrderedSet<WordData> A1;
  A1 = WD;
  cout << "Set A1 = WD" << endl;
  cout << "Is A1 == WD?" << endl;
  if (A1 == WD)
    cout << "YES\n";
  else
    cout << "NO\n";
  cout << "Clearing set WD...\n";
  WD.Clear();
  cout << "Is WD empty?" << endl;
  if (WD.IsEmpty())
    cout << "YES" << endl;
  else
    cout << "NO" << endl;
  cout << "Outputting set WD...\n";
  cout << WD << endl;
  cout << "Hey" << endl;
  OrderedSet<WordData> str;
  OrderedSet<int> integer;
  integer.Insert(1);
  cout << integer << endl;
  integer[0] = 100;
  cout << integer << endl;
  OrderedSet<char> charlist;
  charlist.Insert('a');
  charlist.Insert('b');
  charlist.Insert('c');
  cout << charlist << endl;
  cout << charlist.Size() << endl;
  OrderedSet<char> otherlist;
  otherlist.Insert('z');
  otherlist = charlist;
  cout << otherlist << endl;
  cout << otherlist.Size() << endl;
  return 0;
}

