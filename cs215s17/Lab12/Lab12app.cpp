// Assignment : Lab 12
// File : martinezL12.cpp
// Author : Juan Martinez
// Date : Spring 2017
// Description : This program reads in a file with card types, displays the cards
// then displays the cards in half, and then a shuffled deck.

#include <iostream>
#include "LList2.hpp"
#include "card.h"
#include <fstream>

using namespace std;

int main()
{
  // Open file cards.in
  ifstream infile;
  infile.open("cards.in");

  char r;
  char s;

  LList2 <card> cardList;
  card C;
  
  while (infile >> r)
    {
      C.rank = r;
      infile >> s;
      C.suit = s;
      cardList.InsertLast(C);
    }

  cout << "The cards: " << cardList << endl;

  LList2 <card> firstHalf;
  LList2 <card> secondHalf;

  int counter = 0;

  for (LList2<card>::Iterator itr = cardList.begin(); itr != cardList.end(); itr++)
    {
      if (counter < (cardList.Size()/2))
	{
	  firstHalf.InsertLast(*itr);
	  counter++;
	}
      else
	{
	  secondHalf.InsertLast(*itr);
	}
    }
  
  cout << "First half: " << firstHalf << endl;
  cout << "Second Half: " << secondHalf << endl << endl;

  LList2 <card> shuffleList;
  LList2<card>::Iterator itr2 = firstHalf.begin();

  counter = 0;

  for (LList2<card>::Iterator itr = secondHalf.begin(); itr != secondHalf.end(); itr++)
    {
      if (counter % 2) /*1 is true, 0 is false*/
	{
	 shuffleList.InsertLast(*itr2);
	  itr2++;
	  itr--;
	}
      else
	{
	  shuffleList.InsertLast(*itr);
	}
      
      counter++;
    }
  if ( (cardList.Size() % 2) == false)
    {
      shuffleList.InsertLast(*itr2);
    }
  
  cout << "Shuffled cards: " << shuffleList << endl << endl;
	  
	  
         
  return 0;
}
