#ifndef CARD_H
#define CARD_H

#include <iostream>
using namespace std;

class card
{
    public:
	card ();
	card (const card & other);
	~card ();
	card & operator = (const card & other);
	bool operator == (const card & other) const;
	bool operator != (const card & other) const;
	bool operator < (const card & other) const;
	bool operator > (const card & other) const;
	bool operator <= (const card & other) const;
	bool operator >= (const card & other) const;
	friend istream & operator >> (istream & ins, card & C);
	friend ostream & operator << (ostream & outs, const card & C);
	char rank;
	char suit;
    private:
	void evaluate ();
	int sortval;
};

#endif
