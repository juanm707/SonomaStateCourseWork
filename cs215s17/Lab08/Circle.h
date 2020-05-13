#ifndef CIRCLE_H
#define CIRCLE_H

#include <iostream>
#include "Shape.h"

using namespace std;

const float PI = 3.14159;

class Circle : public Shape
{
	public:
		Circle();
		Circle(const Circle & C);
		Circle(float L);
		~Circle();
		Circle & operator = (const Circle & C);
		string GetType () const;
    		float GetArea () const;
		float GetPerimeter () const;
		bool operator == (const Circle & C) const;
		bool operator < (const Circle & C) const;
		
	private:
};

#endif
