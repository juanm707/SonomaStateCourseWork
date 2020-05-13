#include "card.h"

card::card ()
{
	rank = suit = '?';
	sortval = 0;
}

card::card (const card & other)
{
	rank = other.rank;
	suit = other.suit;
	sortval = other.sortval;
}

card::~card ()
{
}

card & card::operator = (const card & other)
{
	if (this == &other)
		return * this;
	rank = other.rank;
	suit = other.suit;
	sortval = other.sortval;
	return * this;
}

bool card::operator == (const card & other) const
{
	return sortval == other.sortval;
}

bool card::operator != (const card & other) const
{
	return sortval != other.sortval;
}

bool card::operator < (const card & other) const
{
	return sortval < other.sortval;
}

bool card::operator > (const card & other) const
{
	return sortval > other.sortval;
}

bool card::operator <= (const card & other) const
{
	return sortval <= other.sortval;
}

bool card::operator >= (const card & other) const
{
	return sortval >= other.sortval;
}

istream & operator >> (istream & ins, card & C)
{
	card T;
	ins >> T.rank;
	ins >> T.suit;
	T.evaluate();
	if (T.sortval)
		C = T;
	else
		ins.setstate(ios::failbit);
	return ins;
	return ins;
}

ostream & operator << (ostream & outs, const card & C)
{
	outs << C.rank << C.suit;
	return outs;
}

void card::evaluate ()
{
	rank = toupper(rank);
	suit = toupper(suit);
	sortval = 0;
	char r[] = {'A','2','3','4','5','6','7','8','9','T','J','Q','K'};
	char s[] = {'C', 'D', 'H', 'S'};
	int i;
	for (i = 0;  i < 13 && rank != r[i]; i++);
	sortval = (i+1) * 100;
	for (i = 0;  i < 4 && suit != s[i]; i++);
	sortval += i+1;
	if (sortval / 100 < 1 || sortval / 100 > 13 ||
		sortval % 100 < 1 || sortval % 100 > 4)
			sortval = 0;
}
