#include <iostream>
#include <iomanip>
using namespace std;

int main ()
{
  int r, g, b, a;
  cout << "Enter a RGBA color value (e.g 255 127 51 0): " << endl;
  cin >> r;
  cin >> g;
  cin >> b;
  cin >> a;
  
  cout << "Your color in hexadecimal is: ";

  if (r > 255)
    {
      r = r / 10;
    }
  else if (r < 16)
    {
      cout << 0;
    }
  cout << hex << r;

  if (g > 255)
    {
      g = g / 10;
    }
  else if (g < 16)
    {
      cout << 0;
    }
  cout << g;

  if (b > 255)
    {
      b = b / 10;
    }
  else if (b < 16)
    {
      cout << 0;
    }
  cout << b;

  if (a > 255)
    {
      a  = a / 10;
    }
  else if (a < 16)
    {
      cout << 0;
    }
  cout << a;
  // cout << hex << r;
  // cout << g;
  // cout << b;
  // cout << a;

  return 0;
}
