#include <iostream>
#include "LList2.hpp"

using namespace std;

#define MAX 8
int main ()
{

  LList2 <int> L1;

  for (int i = 0; i < MAX; i++)
    {
      if (i % 2)
	{
	  L1.InsertFirst(i);
	}
      else
	{
	  L1.InsertLast(i);
	}
    }

  cout << "L1 in order: ";
  cout << L1 << endl;
  cout << "Testing begin, end, post++ and *\n";

  for (LList2<int>::Iterator itr = L1.begin (); itr != L1.end(); itr++)
    {
      cout << "Value: " << *itr << endl;
    }

  cout << "Testing rbegin, rend, post-- and *\n";
  for (LList2<int>::Iterator itr = L1.rbegin(); itr != L1.rend(); itr--)
    {
      cout << "Value : " << *itr << endl;
    }

  cout << "Testing pre++\n";
  cout << "Should write second item in list L1\n";
  LList2<int>::Iterator itr = L1.begin();
  cout << *++itr << endl;

  cout << "Testing pre--\n";
  cout << "Should write second to last item in list L1\n";
  itr = L1.rbegin();
  cout << *--itr << endl;

  
  
  

  return 0;
}
