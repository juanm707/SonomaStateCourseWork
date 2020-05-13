// Assignment : Lab 01
// File : martinezL01b.cpp
// Author : Juan Martinez
// Date : Spring 2017
// Description : This program will request the user's name and write
// the message "Hello Name" in the shape of a sin and cosine wave
// on the standard console output screen.

// Include input and output stream and string libraries and math library.
#include <iostream>
#include <string>
#include <cmath>
// Use the standard namespace.
// This will allow the program to write to cout and read from cin.
using namespace std;

// Prototype for function to ask the user for their name.
string GetName (ostream & outs, istream & ins);
// Prototype for function to print message.
void PrintMessage (string message, ostream & outs);

int main()
{
  // Declare a string variable to hold the user's name.
  // Call the GetName function to get the user's name and
  // store the returned value in usersname.
  
  string usersname = GetName (cout, cin);
  // Create a message by concatenating hello and the user's
  // name.
  string mymessage = "Hello " + usersname;
  // Call the PrintMessage function to print the message.
  PrintMessage (mymessage, cout);
  // Exit from the program.
  return 0;
}

// Function to ask the user for their name.
// The input stream and the output stream are passed to this
// function. This function will write a message requesting the
// user's name to the output stream. It will then read the user's
// name from the input stream and store it in a string variable.
// Finally, it will return the string.
string GetName (ostream & outs, istream & ins)
{
  // Declare a string variable to hold the user's name.
  string name;
  // Request the user's name.
  outs << "Please enter your name: " << endl;
  // Read the user's name from cin - the standard input - generally
  // the keyboard.
  ins >> name;
  return name;
}

// Function to print the message.
// The message and the output stream are passed to this function.
// This function will write the message to the output stream.
// There is no returned value.
void PrintMessage (string message, ostream & outs)
{
  // Declare a variable to hold the desired number of lines.
  float maxAngle = 6.28;
  // Declare a variable to count the lines as they are printed.
  float angle = 0.0;

  while (angle < maxAngle)
    {

      outs << "| ";
      
      //Declare a variable to hold the desired number of spaces.
      int numSpaces = int (20 + 20 * sin (angle));
      //Declare a variable to count the spaces as they are printed.
      int spaceCount = 0;

      while (spaceCount < numSpaces)
	{
	  // Write a single space to outs.
	  outs << ' ';
	  // Increment the space counter.
	  spaceCount++;
	}

      // Write the message to outs.
      outs << message;
      // The max number spaces from end to end.
      int limit = 40;

      // Outputs the rest of the spaces.
      while (spaceCount < limit)
	{
	  outs << ' ';
	  spaceCount++;
	}
         
      outs << " | ";
      
      // Outputs the cosine wave
      numSpaces = int (20 + 20 * cos (angle));
      spaceCount = 0;
      
      while (spaceCount < numSpaces)
	{
	  outs << ' ';
	  spaceCount++;
	}
      
      outs << message;

      // Outputs the rest of the spaces.
      while (spaceCount < limit)
	{
	  outs << ' ';
	  spaceCount++;
	}
      
      outs << " |" << endl;
      
      // Increment the angle.
      angle += 0.3;
      
    }
  
}

