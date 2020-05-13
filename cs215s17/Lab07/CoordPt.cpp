#include "CoordPt.h"
#include <cmath>
using namespace std;

CoordinatePoint::CoordinatePoint()
// Precondition: default constructor - no parameters required.
// Postcondition: a new object with x set to 0 and y set to
// 0 will be created.
{
#ifdef DEBUG
	cout << "Entering default constructor for Coordinate Point\n";
#endif
	x = 0;
	y = 0;
#ifdef DEBUG
	cout << "Exiting default constructor for Coordinate Point\n";
#endif
}

CoordinatePoint::CoordinatePoint(int x_coord, int y_coord)
// Precondition: x_coord and y_coord must be integer values.
// Postcondition: a new object with x set to x_coord and y set to
// y_coord will be created.
{
#ifdef DEBUG
	cout << "Entering second constructor for Coordinate Point\n";
#endif
	x = x_coord;
	y = y_coord;
#ifdef DEBUG
	cout << "Exiting second constructor for Coordinate Point\n";
#endif
}

CoordinatePoint::CoordinatePoint(const CoordinatePoint & Other)
// Precondition: copy constructor - Other must be a valid object.
// Postcondition: a new object with x set to Other.x and
// y set to Other.y will be created.
{
#ifdef DEBUG
	cout << "Entering copy constructor for Coordinate Point\n";
#endif
	x = Other.x;
	y = Other.y;
#ifdef DEBUG
	cout << "Exiting copy constructor for Coordinate Point\n";
#endif
}

CoordinatePoint::~CoordinatePoint()
// Precondition: destructor - no parameters required.
// Postcondition: no action since there is no dynamic memory.
{
#ifdef DEBUG
	cout << "Entering destructor for Coordinate Point\n";
#endif
#ifdef DEBUG
	cout << "Exiting destructor for Coordinate Point\n";
#endif
}

CoordinatePoint & CoordinatePoint::operator = (const CoordinatePoint & Other)
// Precondition: assignment operator - Other must be a valid object.
// Postcondition: for the existing object, x will be set to Other.x
// and y will be set to Other.y.
{
#ifdef DEBUG
	cout << "Entering assignment operator for Coordinate Point\n";
#endif
	if (this == &Other)
		return *this;
	x = Other.x;
	y = Other.y;
#ifdef DEBUG
	cout << "Exiting assignment operator for Coordinate Point\n";
#endif
	return *this;
}

float CoordinatePoint::Magnitude () const
// Precondition: x and y are integer values.
// Postcondition: the distance from the origin (0,0) will be
// calculated (using the Pythagorean Theorem) and returned.
{
#ifdef DEBUG
	cout << "Entering magnitude function for Coordinate Point\n";
#endif
	float magnitude = sqrt (float (x * x + y * y));
#ifdef DEBUG
	cout << "Exiting magnitude function for Coordinate Point\n";
#endif
	return magnitude;
}

float CoordinatePoint::Distance (const CoordinatePoint & Other) const
// Precondition: *this and Other must be a valid objects.
// Postcondition: the distance from the *this to Other will be
// calculated (using the Pythagorean Theorem) and returned.
{
#ifdef DEBUG
	cout << "Entering distance function for Coordinate Point\n";
#endif
	int deltax = x - Other.x;
	int deltay = y - Other.y;
	float distance = sqrt (float (deltax * deltax + deltay * deltay));
#ifdef DEBUG
	cout << "Exiting distance function for Coordinate Point\n";
#endif
	return distance;
}

CoordinatePoint CoordinatePoint::operator + (CoordinatePoint & Other)
// Precondition: *this and Other must be a valid objects.
// Postcondition: the sum of *this and Other will be
// calculated and returned.
{
#ifdef DEBUG
	cout << "Entering addition operator for Coordinate Point\n";
#endif
	int xvalue = x + Other.x;
	int yvalue = y + Other.y;
	CoordinatePoint sum (xvalue, yvalue);
#ifdef DEBUG
	cout << "Exiting addition operator for Coordinate Point\n";
#endif
	return sum;
}

bool CoordinatePoint::operator < (const CoordinatePoint & Other) const
// Precondition: *this and Other must be a valid objects.
// Postcondition: the magnitude of *this and Other will be compared.
// If the magnitude of *this is < the magnitude of Other, true will
// be returned; otherwise, false will be returned.
{
#ifdef DEBUG
	cout << "Entering less than operator for Coordinate Point\n";
#endif
	bool lessthan = Magnitude() < Other.Magnitude();
#ifdef DEBUG
	cout << "Exiting less than operator for Coordinate Point\n";
#endif
	return lessthan;
}

istream & operator >>  (istream & input, CoordinatePoint & p)
// Precondition: p is an object of type CoordinatePoint.
// Postcondition: the contents of p will be read from the input stream -
// input will be in the format (x,y) - where x and y are integer values.
// The parenthesis and comma will are required but will not be stored -
// the fail flag will be set if the input format is incorrect. 
{
#ifdef DEBUG
	cout << "Entering input operator for Coordinate Point\n";
#endif
	char format;
	input >> format >> p.x >> format >> p.y >> format;
#ifdef DEBUG
	cout << "Exiting input operator for Coordinate Point\n";
#endif
	return input;
}

ostream & operator <<  (ostream & output, const CoordinatePoint & p)
// Precondition: p is an object of type CoordinatePoint.
// Postcondition: the contents of p will be sent to the output stream 
// using the format (x,y) where x and y are the x and y coordinates
// of p.
{
#ifdef DEBUG
	cout << "Entering output operator for Coordinate Point\n";
#endif
	output << '(' << p.x << ',' << p.y << ')';
#ifdef DEBUG
	cout << "Exiting output operator for Coordinate Point\n";
#endif
	return output;
}
