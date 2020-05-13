#ifndef SHAPE_H
#define SHAPE_H

#include <iostream>
using namespace std;

class Shape
{
	public:
		Shape();
		Shape(float L);
		virtual string GetType () const;
		void SetLength (float L);
		float GetLength () const;
		virtual float GetArea () const;
		virtual float GetPerimeter () const;

		virtual void SetLength2 (float L2);
		virtual float GetLength2 () const;
		virtual void SetLength3 (float L3);
		virtual float GetLength3 () const;
		
		friend ostream & operator << (ostream & outs, const Shape & S);
	protected:
		float length;
};

#endif
