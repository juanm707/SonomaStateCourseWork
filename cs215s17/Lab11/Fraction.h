#ifndef FRACTION_H
#define FRACTION_H

#include <iostream>
using namespace std;

class fraction
{
public:

	fraction ();
	fraction (int w);
	fraction (int n, unsigned d);
	fraction (int w, unsigned n, unsigned d);
	~fraction ();

	fraction operator = (const fraction & other);
	fraction operator + (const fraction & other) const;
	bool operator == (const fraction & other) const;
	bool operator != (const fraction & other) const;
	bool operator < (const fraction & other) const;
	bool operator <= (const fraction & other) const;
	bool operator > (const fraction & other) const;
	bool operator >= (const fraction & other) const;

	friend istream & operator >> (istream & ins, fraction & f);
	friend ostream & operator << (ostream & outs, const fraction & f);

private:

	void reduce ();

	int whole;
	int numerator;
	unsigned denominator;
};

#endif
