#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <iostream>
#include "Shape.h"
using namespace std;

class Triangle : public Shape
{
 public:
  Triangle();
  Triangle(float L1, float L2, float L3);
  void SetLength2(float L2);
  float GetLength2 () const;
  void SetLength3(float L3);
  float GetLength3 () const;
  string GetType () const;
  float GetArea () const;
  float GetPerimeter () const;
 private:
  float length2;
  
  float length3;
};

#endif
