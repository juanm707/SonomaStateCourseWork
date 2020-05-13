#include "Triangle.h"
#include <cmath>

using namespace std;

Triangle::Triangle()
{
  length2 = 0;
  length3 = 0;
}

Triangle::Triangle(float L1, float L2, float L3)
{
  length = L1;
  length2 = L2;
  length3 = L3;
}

void Triangle::SetLength2 (float L2)
{
  length2 = L2;
}

float Triangle::GetLength2 () const
{
  return length2;
}

void Triangle::SetLength3 (float L3)
{
  length3 = L3;
}

float Triangle::GetLength3 () const
{
  return length3;
}

string Triangle::GetType () const
{
  return "Triangle";
}

float Triangle::GetArea () const
{
  float p;
  p = GetPerimeter() / 2;
  return sqrt(p * (p - length) * (p - length2) * (p - length3));
}

float Triangle::GetPerimeter () const
{
  return length + length2 + length3;
}
