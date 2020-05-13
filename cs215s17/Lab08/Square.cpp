#include "Square.h"
using namespace std;

Square::Square()
{
  length = 0;
}

Square::Square(const Square & S)
{
  length = S.length;
}

Square::Square(float L)
{
  length = L;
}

Square::~Square()
{
}

Square & Square::operator = (const Square & S)
{
  if (this == &S)
    {
      return * this;
    }

  length = S.length;

  return * this;
}

string Square::GetType () const
{
	return "Square";
}

/*void Square::SetLength (float L)
{
  length = L;
}

float Square::GetLength () const
{
	return length;
}*/

float Square::GetArea () const
{
	return length * length;
}

float Square::GetPerimeter () const
{
	return length * 4;
}

bool Square::operator == (const Square & S) const
{
  if (length == S.length)
    {
      return true;
    }
  
  return false;;
}

bool Square::operator < (const Square & S) const
{
  if (length < S.length)
    {
      return true;
    }

  return false;
}

ostream & operator << (ostream & outs, const Square & S)
{
  cout << "The area of your Square is: " << S.GetArea() << "; its perimeter is " << S.GetPerimeter() << '.' << endl;
	return outs;
}