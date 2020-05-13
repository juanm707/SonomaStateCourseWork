#include "Shape.h"
using namespace std;

Shape::Shape()
{
  length = 0;
}

Shape::Shape(float L)
{
  length = L;
}

string Shape::GetType () const
{
	return "Shape";
}

void Shape::SetLength (float L)
{
  length = L;
}

float Shape::GetLength () const
{
	return length;
}

float Shape::GetArea () const
{
	return 0;
}

float Shape::GetPerimeter () const
{
  return 0;
}

void Shape::SetLength2 (float L2)
{
}

float Shape::GetLength2 () const
{
  return 0;
}

void Shape::SetLength3 (float L3)
{
}

float Shape::GetLength3 () const
{
  return 0;
}














ostream & operator << (ostream & outs, const Shape & S)
{
  cout << "The area of your " << S.GetType() << " is: " << S.GetArea() << "; its perimeter is: " << S.GetPerimeter() << '.';
	return outs;
}
