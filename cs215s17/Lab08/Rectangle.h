#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <iostream>
#include "Shape.h"
using namespace std;

class Rectangle : public Shape
{
 public:
  Rectangle();
  Rectangle(float L1, float L2);
  void SetLength2 (float L2);
  float GetLength2 () const;
  string GetType () const;
  float GetArea () const;
  float GetPerimeter () const;
 private:
  float length2;
};

#endif

