#include "Fraction.h"

fraction::fraction ()
{
	whole = 0;
	numerator = 0;
	denominator = 1;
}

fraction::fraction (int w)
{
	whole = w;
	numerator = 0;
	denominator = 1;
}

fraction::fraction (int n, unsigned d)
{
	whole = 0;
	numerator = n;
	denominator = d;
	reduce();
}

fraction::fraction (int w, unsigned n, unsigned d)
{
	whole = w;
	numerator = n;
	denominator = d;
	this->reduce();
}

fraction::~fraction ()
{
}

fraction fraction::operator = (const fraction & other)
{
	this->whole = other.whole;
	this->numerator = other.numerator;
	this->denominator = other.denominator;
	this->reduce();

	return *this;
}

fraction fraction::operator + (const fraction & other) const
{
	fraction sum;

	sum.whole = this->whole + other.whole;
	sum.numerator = this->numerator * other.denominator 
			+ this->denominator * other.numerator;
	sum.denominator = this->denominator * other.denominator;
	sum.reduce();

	return sum;
}

bool fraction::operator == (const fraction & other) const
{
	int t = whole * denominator + numerator;
	int o = other.whole * other.denominator + other.numerator;
	return t == o;
}

bool fraction::operator != (const fraction & other) const
{
	int t = whole * denominator + numerator;
	int o = other.whole * other.denominator + other.numerator;
	return t != o;
}

bool fraction::operator < (const fraction & other) const
{
	int t = whole * denominator + numerator;
	int o = other.whole * other.denominator + other.numerator;
	return t < o;
}

bool fraction::operator <= (const fraction & other) const
{
	int t = whole * denominator + numerator;
	int o = other.whole * other.denominator + other.numerator;
	return t <= o;
}

bool fraction::operator > (const fraction & other) const
{
	int t = whole * denominator + numerator;
	int o = other.whole * other.denominator + other.numerator;
	return t > o;
}

bool fraction::operator >= (const fraction & other) const
{
	int t = whole * denominator + numerator;
	int o = other.whole * other.denominator + other.numerator;
	return t >= o;
}
istream & operator >> (istream & ins, fraction & f)
{	// Note: trivial version of >>

	char temp;

	ins >> f.whole >> f.numerator >> temp >> f.denominator;

	return ins;
}

ostream & operator << (ostream & outs, const fraction & f)
{	// Note: trivial version of <<

	outs << f.whole << ' ' << f.numerator << '/' << f.denominator;
	
	return outs;
}

void fraction::reduce ()
{
	int f = 2;
	
	denominator = denominator == 0 ? 1 : denominator;
	whole += numerator / denominator;
	numerator %= denominator;
	while (f <= numerator)
		if ((numerator % f == 0) && (denominator % f == 0))
		{
			numerator /= f;
			denominator /= f;
		}
		else 
			f++;
}


