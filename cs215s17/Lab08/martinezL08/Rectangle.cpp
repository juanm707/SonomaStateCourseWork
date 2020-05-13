#include "Rectangle.h"
using namespace std;

Rectangle::Rectangle()
{
  length = 0;
  length2 = 0;
}

Rectangle::Rectangle(float L1, float L2)
{
  length = L1;
  length2 = L2;
}

void Rectangle::SetLength2 (float L2)
{
  length2 = L2;
}

float Rectangle::GetLength2 () const
{
  return length2;
}

string Rectangle::GetType () const
{
  return "Rectangle";
}

float Rectangle::GetArea () const
{
  return length * length2;
}

float Rectangle::GetPerimeter () const
{
  return (length + length2) * 2;
}
