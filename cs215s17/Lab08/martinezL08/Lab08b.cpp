// Lab 08
// File : Lab08b.cpp
// Author : Dr. Watts
// Date : Spring 2014
// Description: This application program will be used to test the Shape class
// and its child classes: Square, Circle, EquiTri, Rectangle, and Triangle

#include <iostream>
#include <vector>
#include "Square.h"
#include "Circle.h"
#include "EquiTri.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Shape.h"

using namespace std;

int main ()
{
  vector <Shape *> myShapes;
	char which = ' ';
	do 
	{
		float len = 0;
		cout << "Enter S to create a Square\n";
		cout << "Enter C to create a Circle\n";
		cout << "Enter E to create an Equilateral Triangle\n";
		cout << "Enter R to create a Rectangle\n";
		cout << "Enter T to create a Triangle\n";
		cout << "Enter Q to quit\n";
		
		cin >> which;
		switch (which)
		{
			case 'S': case 's':
			{
				cout << "Enter the length of the side of your square: ";
				cin >> len;
				Square * S = new Square (len);
				myShapes.push_back (S);
				break;
			}
			case 'C': case 'c':
			{
				cout << "Enter the length of the diameter of your circle: ";
				cin >> len;
				Circle * C = new Circle (len);
				myShapes.push_back (C);
				break;
			}
			case 'E': case 'e':
			{
				cout << "Enter the length of the side of your equilateral triangle: ";
				cin >> len;
				EquiTri * E = new EquiTri (len);
				myShapes.push_back (E);
				break;
			}
			
		case 'R': case 'r':
		  {
		    float len2;
		    cout << "Enter the length of one of the sides of your Rectangle: ";
		    cin >> len;
		    cout << "Enter the length of the other side of your Rectangle: ";
		    cin >> len2;
		    Rectangle * R = new Rectangle(len, len2);
		    myShapes.push_back(R);
		    break;
		  }
		case 'T': case 't':
		  {
		    float len2;
		    float len3;
		    cout << "Enter the length of the first side of your Triangle: ";
		    cin >> len;
		    cout << "Enter the length of the second side of your Triangle: ";
		    cin >> len2;
		    cout << "Enter the length of the third side of your Triangle: ";
		    cin >> len3;
		    Triangle * T = new Triangle(len, len2, len3);
		    myShapes.push_back(T);
		    break;
		  }
		      
			case 'Q': case 'q':
				cout << "Thank you\n";
		}
	} while (toupper (which) != 'Q');
	for (int i = 0; i < myShapes.size(); i++)
		cout << *myShapes[i] << endl;
	
	return 0;
}
