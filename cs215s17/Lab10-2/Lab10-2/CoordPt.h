#ifndef COORDPT_H
#define COORDPT_H

#include <iostream>
using namespace std;

class CoordinatePoint
{
public:
    CoordinatePoint();
	// Precondition: default constructor - no parameters required.
	// Postcondition: a new object with x set to 0 and y set to
	// 0 will be created.

    CoordinatePoint(int x_coord, int y_coord);
	// Precondition: x_coord and y_coord must be integer values.
	// Postcondition: a new object with x set to x_coord and y set to
	// y_coord will be created.

    CoordinatePoint(const CoordinatePoint & Other);
	// Precondition: copy constructor - Other must be a valid object.
	// Postcondition: a new object with x set to Other.x and
	// y set to Other.y will be created.

    ~CoordinatePoint();
	// Precondition: destructor - no parameters required.
	// Postcondition: no action since there is no dynamic memory.

    CoordinatePoint & operator = (const CoordinatePoint & Other);
	// Precondition: assignment operator - Other must be a valid object.
	// Postcondition: for the existing object, x will be set to Other.x
	// and y will be set to Other.y.

    float Magnitude () const;
	// Precondition: x and y are integer values.
	// Postcondition: the distance from the origin (0,0) will be
	// calculated (using the Pythagorean Theorem) and returned.

    float Distance (const CoordinatePoint & Other) const;
	// Precondition: *this and Other must be a valid objects.
	// Postcondition: the distance from the *this to Other will be
	// calculated (using the Pythagorean Theorem) and returned.

    CoordinatePoint operator + (const CoordinatePoint & Other);
	// Precondition: *this and Other must be a valid objects.
	// Postcondition: the sum of *this and Other will be
	// calculated and returned.

    friend istream & operator >>  (istream & input, CoordinatePoint & p);
	// Precondition: p is an object of type CoordinatePoint.
	// Postcondition: the contents of p will be read from the input stream -
	// input will be in the format (x,y) - where x and y are integer values.
	// The parenthesis and comma will are required but will not be stored -
	// the fail flag will be set if the input format is incorrect. 

    friend ostream & operator <<  (ostream & output, const CoordinatePoint & p);
	// Precondition: p is an object of type CoordinatePoint.
	// Postcondition: the contents of p will be sent to the output stream 
	// using the format (x,y) where x and y are the x and y coordinates
	// of p.

private:
    int x;
    int y;
};

#endif
