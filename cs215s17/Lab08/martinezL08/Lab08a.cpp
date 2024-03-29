#include <iostream>
#include "Square.h"
#include "Circle.h"

using namespace std;

int main ()
{
	int len = 0;
	do
	{
		cout << "Enter the length of your square and circle "
		     << "(0 to quit): ";
		cin >> len;
		
		Square S1;
		Circle C1;
		
		cout << "S1: " << S1 << endl;
		cout << "C1: " << C1 << endl;
		
		Square S2 = S1;
		Circle C2 = C1;
		
		cout << "S2: " << S2 << endl;
		cout << "C2: " << C2 << endl;
		
		S2.SetLength(len);
		C2.SetLength(len);
		
		cout << "S2: " << S2 << endl;
		cout << "C2: " << C2 << endl;
		
		if (S1 == S2)
			cout << "S1 and S2 are the same\n";
		S1 = S2;
		if (S1 == S2)
			cout << "S1 and S2 are the same\n";
		cout << "S1: " << S1 << endl;
		Square * Sp = new Square (len);
		cout << "*Sp: " << *Sp << endl;
		delete Sp;

		if (C1 == C2)
		  {
		    cout << "C1 and C2 are the same\n";
		  }
		C1 == C2;
		if (C1 == C2)
		  {
		    cout << "C1 and C2 are the same\n";
		  }
		cout << "C1: " << C1 << endl;
		Circle * Cp = new Circle (len);
		cout << "*Cp: " << *Cp << endl;
		delete Cp;
		
	} while (len > 0);
	return 0;
}
