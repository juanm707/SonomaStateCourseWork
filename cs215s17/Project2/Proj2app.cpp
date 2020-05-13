#include <iostream>
#include <fstream>
#include "SetLimits.h"
#include "CLife.h"
using namespace std;

int main ()
{
    SetLimits();
    char play = 'y';
    CLife life;
    life.Instructions (cout, cin);
    while (tolower (play) == 'y')
    {
	char key;
	char row, col;
	string filename;
	ifstream input;
	life.Init(15, 21);
	cout << "An empty community has been created!\n\n";
	life.Display (cout);
	cout << "How would you like to populate your community?\n\n";
	cout << "Enter R/r for a randomly generated initial population.\n";
	cout << "Enter U/u to establish your own initial population.\n";
	cout << "Enter F/f to read the initial population from a file.\n\n";
	cin >> key;
	switch (tolower (key))
	{
		case 'r' :
			life.InitRandom ();
			break;
		case 'u' :
			do
			{
			  cout << endl << "Enter row and column letters (ZZ to end): " << endl;
				cin >> row >> col;
				
				if (life.Add (toupper(row) - 'A' + 1, toupper(col) - 'A' + 1))
					life.Display (cout);
			} while (toupper(row) != 'Z' && toupper(col) != 'Z');
			break;
		case 'f' :
			cout << "Enter the name of the file: ";
			cin >> filename;
			cout << endl;
			input.open (filename.c_str());
			if (input.fail())
			{
				life.InitRandom ();
			}
			else
			{
				life.InitFile (input);
				input.close();
			}
			break;
		default :
			cout << "Not a valid selection\n";
			life.InitRandom ();
	}
	life.Display (cout);
	bool finished = false, quitting = false;
	while (!finished && !quitting)
	{
		int row, col;
		cout << "\nEnter option (N/n = next, Q/q = quit, I/i = instructions): ";
		cin >> key;
		cout << endl;
		
		switch (tolower (key))
		{
			case 'n' :
				life.Next ();
				break;
			case 'q' :
				quitting = true;
				break;
			case 'i':
				life.Instructions (cout, cin);
				break;
			default :
				cout << "Not a valid selection\n";
		}
		life.Display (cout);
		finished = life.Done();
	}
	life.Message (cout);
	cout << "Would you like to play again (y/n)? ";
	cin >> play;
	cin.clear ();;
    }
    cout << endl;
    return 0;
}
