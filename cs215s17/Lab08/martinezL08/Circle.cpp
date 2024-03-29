#include "Circle.h"
#include <cmath>
using namespace std;

Circle::Circle()
{
  length = 0;
}

Circle::Circle(const Circle & C)
{
  length = C.length;
}

Circle::Circle(float L)
{
  length = L;
}

Circle::~Circle()
{
}

Circle & Circle::operator = (const Circle & C)
{
  if (this == &C)
    {
      return * this;
    }

  length = C.length;

  return * this;
}

string Circle::GetType() const
{
  return "Circle";
}

float Circle::GetArea () const
{
  return PI * (length/2 * length/2);
}

float Circle::GetPerimeter () const
{
  return 2 * PI * (length/2);
}

bool Circle::operator == (const Circle & C) const
{
  if (length == C.length)
    {
      return true;
    }

  return false;
}

bool Circle::operator < (const Circle & C) const
{
  if (length < C.length)
    {
      return true;
    }
  return false;
}

ostream & operator << (ostream & outs, const Circle & C)
{
  cout << "The area of your Circle is: " << C.GetArea() << "; its perimeter is: " << C.GetPerimeter() << '.' << endl;
  return outs;
}
