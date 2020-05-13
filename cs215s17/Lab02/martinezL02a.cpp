// Program : Lab 2 a
// Description: This program will be used to explore how C++ handles
// input for various date types.

// Three data values will be read from the standard input stream
// Results will be written to the standard output stream

#include <iostream>

// cin and cout will be used
using namespace std;

int main ()
{
  // this variable will be used to store the current input value
  int  v1;
  float v2;
  char v3;
  string v4;

  
  cout << "Enter the data set input: ";

  cin >> v1;
  cout << "The input value is " << v1 << "; the fail flag is ";
  if (cin.fail() == true)
    {
      cout << "true" << endl;
    }
  else
    {
      cout << "false" << endl;
    }


  cin >> v2;
  cout << "The input value is "<< v2 <<"; the fail flag is ";
  if (cin.fail() == true)
    {
      cout << "true" <<endl;
    }
  else
    {
      cout << "false" << endl;
    }


  cin >> v3;
  cout << "The input value is "<< v3 <<"; the fail flag is ";
  if (cin.fail() == true)
    {
      cout << "true" <<endl;
    }
  else
    {
      cout << "false" << endl;
    }

  cin >> v4;
  cout << "The input value is "<< v4 <<"; the fail flag is ";
  if (cin.fail() == true)
    {
      cout << "true" <<endl;
    }
  else
    {
      cout << "false" << endl;
    }
  

  return 0;
}
