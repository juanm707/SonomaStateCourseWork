#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include "martinezL14.hpp"
using namespace std;

void Insert (OrderedSet <int> & S);
void TestDereference (OrderedSet <int>::Iterator itr);
void TestSubscript (OrderedSet <int> & S, int sub);

int main()
{
  srand(0);
  OrderedSet <int> S1;
  Insert (S1);
  // S1.Insert(100);
  TestDereference (S1.begin());
  TestDereference (S1.end());
  TestSubscript (S1, 1);
  TestSubscript (S1, -1);
  TestSubscript (S1, 1+S1.Size());
  
  return 0;
}

void Insert (OrderedSet <int> & S)
{
  cout << "Insert values in set:\n";

  for (int i = 0; i < 10; i++)
    {
      S.Insert(-10 + rand() % 21);
    }
  S.Insert(100);
  S.Insert(-9);
  cout << "Elements in S: " << S << endl;
  cout << "Deleting 0,5,9" << endl;
  S.Delete(0);
  S.Delete(5);
  S.Delete(9);
  cout << S << endl;
  OrderedSet <int> A;
  A.Insert(99);
  A.Insert(3);
  A.Insert(5);
  A.Insert(7);
  A.Insert(9);
  A.Insert(23);
  A.Insert(69);
  A.Insert(70);
  A.Insert(1234);
  cout << "A: " << A << endl;
  OrderedSet <int> B;
  B.Insert(98);
  B.Insert(2);
  B.Insert(3);
  B.Insert(5);
  B.Insert(7);
  B.Insert(45);
  B.Insert(46);
  B.Insert(76);
  cout << "B: " << B << endl;
  OrderedSet <int> C = A + B;
  OrderedSet <int> D = A * B;
  cout << "A+B=C: " << C << endl;
  cout << "A*B=D: " << D << endl;
  cout << "Adding to C" << endl;
  C.Insert(1);
  C.Insert(2);
  C.Insert(3);
  cout << "C: " << C << endl;
  cout << "Clearing C... " << endl;
  C.Clear();
  cout << "C: " << C << endl;
  cout << "Is C empty?" << endl;
  bool check;
  if (C.IsEmpty())
    {
      check = true;
      cout << "Yes" << endl;
    }
  else
    cout << "No" << endl;
  OrderedSet <int> none;
  cout << "None set: " << none << endl;
}

void TestDereference (OrderedSet <int>::Iterator itr)
{
  try
    {
      cout << "Testing * operator:\n";
      int value = *itr;
      cout << "The value at the iterator is: ";
      cout << value << endl;
    }
  catch (OrderedSet<int>::Exception E)
    {
      cerr << "Exception: " << E.Message() << endl;
      return;
    }
}

void TestSubscript(OrderedSet <int> & S, int sub)
{
  try
    {
      cout << "Testing [] operator:\n";
      int value = S[sub];
      cout << "The value at S[" << sub << "] is: ";
      cout << value << endl;
    }
  catch (OrderedSet<int>::Exception E)
    {
      cerr << "Exception: " << E.Message() << endl;
      return;
    }
}





