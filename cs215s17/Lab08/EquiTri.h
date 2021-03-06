#ifndef EQUITRI_H
#define EQUITRI_H

#include <iostream>
#include "Shape.h"

using namespace std;

class EquiTri : public Shape
{
 public:
  EquiTri();
  EquiTri(const EquiTri & T);
  EquiTri(float L);
  ~EquiTri();
  EquiTri & operator = (const EquiTri & T);
  string GetType () const;
  //void SetLength (float L);
  //float GetLength () const;
  float GetArea () const;
  float GetPerimeter () const;
  bool operator == (const EquiTri & T) const;
  bool operator < (const EquiTri & T) const;
  //friend ostream & operator << (ostream & outs, const EquiTri & T);
 private:
};

#endif

  
