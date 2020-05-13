#include "CoordPt.h"
#include <cmath>
using namespace std;

CoordinatePoint::CoordinatePoint()
// Precondition: default constructor - no parameters required.
// Postcondition: a new object with x set to 0 and y set to
// 0 will be created.
{
	x = 0;
	y = 0;
}

CoordinatePoint::CoordinatePoint(int x_coord, int y_coord)
// Precondition: x_coord and y_coord must be integer values.
// Postcondition: a new object with x set to x_coord and y set to
// y_coord will be created.
{
	x = x_coord;
	y = y_coord;
}

CoordinatePoint::CoordinatePoint(const CoordinatePoint & Other)
// Precondition: copy constructor - Other must be a valid object.
// Postcondition: a new object with x set to Other.x and
// y set to Other.y will be created.
{
	x = Other.x;
	y = Other.y;
}

CoordinatePoint::~CoordinatePoint()
// Precondition: destructor - no parameters required.
// Postcondition: no action since there is no dynamic memory.
{
}

CoordinatePoint & CoordinatePoint::operator = (const CoordinatePoint & Other)
// Precondition: assignment operator - Other must be a valid object.
// Postcondition: for the existing object, x will be set to Other.x
// and y will be set to Other.y.
{
	x = Other.x;
	y = Other.y;
	return *this;
}

float CoordinatePoint::Magnitude () const
// Precondition: x and y are integer values.
// Postcondition: the distance from the origin (0,0) will be
// calculated (using the Pythagorean Theorem) and returned.
{
	return sqrt (float (x * x + y * y));
}

float CoordinatePoint::Distance (const CoordinatePoint & Other) const
// Precondition: *this and Other must be a valid objects.
// Postcondition: the distance from the *this to Other will be
// calculated (using the Pythagorean Theorem) and returned.
{
	int deltax = x - Other.x;
	int deltay = y - Other.y;
	return sqrt (float (deltax * deltax + deltay * deltay));
}

CoordinatePoint CoordinatePoint::operator + (const CoordinatePoint & Other)
// Precondition: *this and Other must be a valid objects.
// Postcondition: the sum of *this and Other will be
// calculated and returned.
{
	int xvalue = x + Other.x;
	int yvalue = y + Other.y;
	return CoordinatePoint (xvalue, yvalue);
}

istream & operator >>  (istream & input, CoordinatePoint & p)
// Precondition: p is an object of type CoordinatePoint.
// Postcondition: the contents of p will be read from the input stream -
// input will be in the format (x,y) - where x and y are integer values.
// The parenthesis and comma will are required but will not be stored -
// the fail flag will be set if the input format is incorrect. 
{
	char format;
	input >> format >> p.x >> format >> p.y >> format;
	return input;
}

ostream & operator <<  (ostream & output, const CoordinatePoint & p)
// Precondition: p is an object of type CoordinatePoint.
// Postcondition: the contents of p will be sent to the output stream 
// using the format (x,y) where x and y are the x and y coordinates
// of p.
{
	output << '(' << p.x << ',' << p.y << ')';
	return output;
}
