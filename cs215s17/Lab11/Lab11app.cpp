#include <iostream>
#include <fstream>
#include "LList2.hpp"
#include "Fraction.h"

using namespace std;

// Add a global variable for holding the sum of the fractions here
fraction total = 0;
 
// Add function prototype here
void addUp (const fraction & frac);



int main ()
{
        ifstream input ("Lab11.in");
        fraction one;
        LList2 <fraction> FL;

        while (input >> one)
                FL.InsertLast (one);
              cout << "The fractions are: ";
        cout << FL << endl;

// Add code to find the sum of the fractions in the list FL here
	FL.Forward(addUp);
// Add code to print the sum here
	cout << "The total is " << total << endl;

        return 0;
}

// Add function implementation here
void addUp (const fraction & frac)
{
  total = total + frac;
}


