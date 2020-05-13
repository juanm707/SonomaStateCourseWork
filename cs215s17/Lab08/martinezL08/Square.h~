#ifndef SQUARE_H
#define SQUARE_H

#include <iostream>
#include "Shape.h"

using namespace std;

class Square : public Shape
{
	public:
		Square();
		Square(const Square & S);
		Square(float L);
		~Square();
		Square & operator = (const Square & S);
		string GetType () const;
		
		
		float GetArea () const;
		float GetPerimeter () const;
		bool operator == (const Square & S) const;
		bool operator < (const Square & S) const;
		//friend ostream & operator << (ostream & outs, const Square & S);
	private:
};

#endif
