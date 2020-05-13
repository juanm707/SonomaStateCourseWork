// File: CLife.cpp
// Assignment: Project 2
// Author: Juan Martinez
// Date: Spring 2017
// Description: This is the implementation of the
// CLife class, which is a class for the cell game
// and also includes the struct for each individual cell.

#include <ctime>
#include <cstdlib>
#include "CLife.h"

CLife::CLifeSquare::CLifeSquare ()
{
// This function will: Make every cell grid a BORDER type to begin with.
  what = BORDER;
}

void CLife::CLifeSquare::Display (ostream & outs)
{
// This function will: Display the symbol for
// for the specific type that a cell is.
  
                string dispString;
                switch (what)
                {
                        case EMPTY:
                                dispString = " ";
                                break;
                        case ADDING:
                                dispString = "*";
                                break;
                        case PERSON:
                                dispString = "O";
                                break;
                        case DELETING:
                                dispString = ".";
                                break;
                        default:
                                dispString = "B";
                }
                outs << dispString;
}

int CLife::CLifeSquare::Reset ()
{
// This function will: Reset the cells to types that correspond
// with ADDING or DELETING. -1 for deleting a cell, so decrease in population.
  
  if (what == ADDING)
    {
      what = PERSON;
      return 1;
    }
  
  if (what == DELETING)
    {
      what = EMPTY;
      return -1;
    }

  return 0;
}

CLife::CLife ()
{
// This function will: Construct a cell life game, creating a 3x3 game, adding space for cells.

        numRows = 1;
        numCols = 1;
        grid = new CLifeSquare * [numRows+2];
        for (int r = 0; r < numRows+2; r++)
            grid[r] = new CLifeSquare [numCols+2];
	
        evaluating = true;
        finished = 0;
	populationSize = 0;
	generations = 0;
}

CLife::~CLife ()
{
// This function will: Deallocate memory for each cell (Deconstructor).

        for (int r = 0; r < numRows+2; r++)
                delete [] grid[r];
        delete [] grid;
}

void CLife::Init (int R, int C)
{
// This function will: Setup/initialize a game of given size.

        for (int r = 0; r < numRows+2; r++)
                delete [] grid[r];
        delete [] grid;
        generationsMap.clear();
        numRows = R;
        numCols = C;
        grid = new CLifeSquare * [numRows+2];
        for (int r = 0; r < numRows+2; r++)
            grid[r] = new CLifeSquare [numCols+2];
        for (int r = 1; r <= numRows; r++)
                for (int c = 1; c <= numCols; c++)
                        grid[r][c].what = EMPTY;
        finished = 0;
        evaluating = true;
        populationSize = 0;
        generations = 1;
}

void CLife::Instructions (ostream & outs, istream & ins)
{
// This function will: Display the instructions.

        outs << endl;
        outs << "THE CELL LIFE GAME\n\n";
        outs << "The Cell Life game is a surival simulation game for a cell.\n";
	outs << "A cell is either alive 'O' or dead ' '.\n";
        outs << "A '.' is a deleting cell and '*' is a cell being born\n";
	outs << "A cell can live on to next generation if only it has 2 or 3 live neighbors.\n";
	outs << "It dies if it has more than 3 or less than 2. A new cell is born if exactly 3 neighbors surround it.\n";
        outs << endl;
}

void CLife::Display (ostream & outs)
{
// This function will: Display the cell squares/game board.

// 65 for char L since that is where 'A' is in decimal in ASCII.
  char L = 65;

  cout << " ";

  for (int c = 1; c <= numCols; c++)
    {
      cout << " " <<  "| ";
      cout << L;
      L++;
    }
  
  cout << " |" << endl;

// Reset to 65 for the letters on the row, previous was for letters on top.
  L = 65;

        for (int r = 1; r <= numRows; r++)
        {
	  cout << " " << "-";
	  
	  for (int z = 0; z < numCols * 2; z++)
	    {      
	      cout << "--";
	    }
	  
	  cout << '+';
	  cout << endl;
	  cout << L;
	  
                for (int c = 1; c <= numCols; c++)
		  {
		    cout << " | ";
                    grid[r][c].Display (outs);
		  }
		
		outs << " | " << endl;
		L++;
	}

	for(int y = 0; y <= numCols*2; y++)
	  {
	    cout << "--";
	  }
	
	cout << '+' << endl;

	cout << "Populations: " << populationSize << " | Generations: " << generations << endl;
	
}

void CLife::InitRandom ()
{
// This function will: Initialize a random game, and spawn random cells.
  
  srand(time(NULL));
  
  int popsize = 0;
  
  for (int i = 0; i < 100; i++)
    {
      int r = rand() % numRows + 1;
      int c = rand() % numCols + 1;
      
      if (Add(r, c))
	{
	  // Nothing.
	}
    }
  
  //  populationSize += popsize;  
}

void CLife::InitFile (istream & ins)
{
// This function will: Read an input file. Two types available: Points
// ex. (2, 3) and Grid ex. ...X..XXXX..X with X indicating a live cell.
  
  int rows;
  int cols;
  char type;

  ins >> rows >> cols >> type;
  Init(rows, cols);
  
  if (type == 'P')
    {
      int rp;
      int cp;
     
      while(ins >> rp >> cp)
	{
	  Add(rp, cp);
	}
    }
  
  else if (type == 'G')
    {
      string line;

      for (int r = 1; r < rows; r++)
	{
	  ins >> line;
	  
	  for (int i = 0; i < line.length(); i++)
	    {
	      if (line[i] == 'X')
		{
		  Add(r, i + 1);
		}
	    }
	}
    }
		
}

void CLife::Next ()
{
// This function will: Produce the next generation, evaulating each cell, and changing it
// to a new type if indicated.

        if (evaluating)
                for (int r = 1; r <= numRows; r++)
                        for (int c = 1; c <= numCols; c++)
                                Evaluate (r, c);
        else
        {
                for (int r = 1; r <= numRows; r++)
                        for (int c = 1; c <= numCols; c++)
			  populationSize += grid[r][c].Reset();
                string mapStr = MakeString ();
                map<string, int>::iterator itr = generationsMap.find (mapStr);
                if (itr == generationsMap.end())
                {
                        generations++;
                        generationsMap [mapStr] = generations;
                }
                else
                {
                        finished = itr->second;
                }
        }
        if (populationSize == 0)
                finished = -2;
        evaluating = !evaluating;
	
}

bool CLife::Add (int row, int col)
{
// This function will: Add a cell
  
  if (row > numRows || col > numCols)
    {
      return false;
    }
  
  if (grid[row][col].what == PERSON)
    {
      return false;
    }
  
  grid[row][col].what = PERSON;
  populationSize++;
  
        return true;
}

bool CLife::Delete (int row, int col)
{
// This function will: delete a cell.
  
  if (grid[row][col].what == EMPTY)
    {
      return false;
    }
  
  grid[row][col].what = EMPTY;

        return true;
}

void CLife::Message (ostream & outs)
{
// This function will: Display the end message.

        string message = "Thank you for playing! :)\n";
        outs << endl << message << endl;
}

bool CLife::Done () 
{
// This function will: Determine if game is done or continue playing. Ends if
// no more cells present or a specific patter has been achieved.
  
  if (finished == 0)
    {
      return false;
    }
  
  return true;
  
}

void CLife::Evaluate (int row, int col)
{
// This function will: evaluate The Cell square by
// checking all neighbors.
  
  int neighbors = 0;
  
  if (grid[row - 1][col - 1].what == PERSON || grid[row - 1][col - 1].what == DELETING)
    {
      neighbors++;
    }
  if (grid[row - 1][col].what == PERSON || grid[row - 1][col].what == DELETING)
    {
      neighbors++;
    }
  if (grid[row - 1][col + 1].what == PERSON || grid[row - 1][col + 1].what == DELETING)
    {
      neighbors++;
    }
  if (grid[row][col - 1].what == PERSON || grid[row][col - 1].what == DELETING)
    {
      neighbors++;
    }
  if (grid[row][col + 1].what == PERSON || grid[row][col + 1].what == DELETING)
    {
      neighbors++;
    }
  if (grid[row + 1][col - 1].what == PERSON || grid[row + 1][col - 1].what == DELETING)
    {
      neighbors++;
    }
  if (grid[row + 1][col].what == PERSON || grid[row + 1][col].what == DELETING)
    {
      neighbors++;
    }
  if (grid[row + 1][col + 1].what == PERSON || grid[row + 1][col + 1].what == DELETING)
    {
      neighbors++;
    }
  
// EVALUATION //

  if (grid[row][col].what == PERSON && neighbors < 2)
    {
     grid[row][col].what = DELETING;
    }
  if (grid[row][col].what == PERSON && neighbors > 3)
    {
     grid[row][col].what = DELETING;
    }
  if (grid[row][col].what == EMPTY && neighbors == 3)
    {
      grid[row][col].what = ADDING;
    }
}

string CLife::MakeString () const
{
// This function will: return a string of the cell types. P for Person, E for Empty.
  
  string resultString;
  
  for (int r = 1; r <= numRows; r++)
    {
      for (int c = 1; c <= numCols; c++)
      {
	if (grid[r][c].what ==  EMPTY)
	  {
	    resultString += "E";
	  }
	else if (grid[r][c].what == PERSON)
	  {
	    resultString += "P";
	  }   
      }
    }
  
  return resultString;
}
