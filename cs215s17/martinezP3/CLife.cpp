// File: CLife.cpp
// Author: Juan Martinez
// Project: CS215 Project 3 Spring 2017
// Description of file contents: 

#include "CLife.h"
#include <time.h>

CBitmap bgImage;
static CBitmap images [MAXTYPES];

using namespace std;

/*1*/ CLife::CLife ()
{
	// This function will: Initiliaze a cell game. 

	// srand (time (NULL));
	numRows = numCols = 1;
	grid = new CLifeSquare * [numRows+2];
	for (int r = 0; r < numRows+2; r++)
		grid[r] = new CLifeSquare [numCols+2];
	seed = 0;
	CLifeStatus = NEW;
}

/*2*/ CLife::CLife (const CLife & other)
{
	// This function will: copy constructor

}

/*3*/CLife::~CLife ()
{
	// This function will: Deallocate or release memory of each cell grid square.

	for (int r = 0; r < numRows + 2; r++)
		delete[] grid[r];
	delete[] grid;

}

/*4*/ CLife & CLife::operator = (const CLife & other)
{
	// This function will: copy one cell square to another. 

	return *this;
}

/*5*/ void CLife::LoadResources ()
{
	// This function will: Load images of each type (background, cell types etc...)

	int res = bgImage.LoadBitmap(CString("BACKGROUND_BMP"));
	res = images[BORDER].LoadBitmap(CString("EMPTY_BMP"));
	res = images[EMPTY].LoadBitmap(CString("EMPTY_BMP"));		
	res = images[ADDINGA].LoadBitmap(CString("ADDINGA_BMP"));
	res = images[ADDINGB].LoadBitmap(CString("ADDINGB_BMP"));
	res = images[PERSON].LoadBitmap(CString("PERSON_BMP"));
	res = images[HUMAN].LoadBitmap(CString("HUMAN_BMP"));
	res = images[DELETING].LoadBitmap(CString("DELETING_BMP"));
	res = images[RAYGUN].LoadBitmap(CString("RAYGUN_BMP"));
}

/*6*/ void CLife::Init (int R, int C, CFrameWnd * windowP)
{
	// This function will: Initialize a cell game.

	for (int r = 0; r < numRows + 2; r++)
		delete[] grid[r];
	delete[] grid;
	generationsMap.clear();
	numRows = R < DEF_ROWS ? DEF_ROWS : R;
	numCols = C < DEF_COLS ? DEF_COLS : C;
	grid = new CLifeSquare *[numRows + 2];
	for (int r = 0; r < numRows + 2; r++)
		grid[r] = new CLifeSquare[numCols + 2];
	for (int r = 1; r <= numRows; r++)
		for (int c = 1; c <= numCols; c++)
			grid[r][c].what = EMPTY;
	ZpopulationSize = 0;
	HpopulationSize = 0;
	generations = 0;	
	finished = 0;
	evaluating = true;
	CLifeStatus = NEW;
}

/*7*/ void CLife::Instructions (CFrameWnd * windowP)
{
	// This function will: Display the instructions for the game.

     CString message;
	 message += "The zombie cells are spreading faster than you think!\n";		
	 message += "You and other cells must work together to survive this apocalypse and bring peace back to the world.\n";
	 message += "You can take out zombie cells by fighting them or spawn new non-zombie cells to aide you.\n";
	

     
	CString title = "Instructions";
	windowP->MessageBox (message, title);
}

/*8*/ void CLife::Display (CFrameWnd * windowP)
{
	// This function will: Display the whole game.

	CPaintDC dc (windowP);
	CRect rect;
	windowP->GetClientRect (&rect);
	CDC memDC;
	int res = memDC.CreateCompatibleDC(&dc);
	memDC.SelectObject(&bgImage);
	dc.TransparentBlt (0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, 1920, 1080, SRCCOPY); 
	DeleteDC (memDC);
	SetUp (rect);
	DisplayGameRect (&dc);
	dc.SetBkMode(TRANSPARENT);	
	CFont font;
	CString fontName = "Terminal";
	font.CreatePointFont(rect.Height() / 5, fontName, &dc);
	CFont* def_font = dc.SelectObject(&font);
	COLORREF def_color = dc.SetTextColor (RGB (0, 0, 0));
	DisplayDataRect (&dc);
	DisplayButtonRect (&dc);
	dc.SelectObject(def_font);
	dc.SetTextColor(def_color);
}

/*9*/ void CLife::Click (int y, int x, CFrameWnd * windowP)
{
	// This function will: Handle a mouse click(nex, play/pause, restart).

	if (newRect.PtInRect(CPoint(x, y)))
	{
		seed = time(NULL) % 10000;
		windowP->KillTimer(1);
		Init (numRows, numCols, windowP);
		InitRandom(windowP);
		CLifeStatus = READY;
		windowP->Invalidate(true);	
	}

	if (playRect.PtInRect(CPoint(x, y)))
	{
		if (CLifeStatus == PLAYING)
		{
			CLifeStatus = PAUSED; 
			windowP->KillTimer(1);
			windowP->Invalidate(true);
			system("pause");

		}
		if (CLifeStatus == PAUSED || CLifeStatus == READY)
		{
			windowP->SetTimer(1, 500, NULL);
			CLifeStatus = PLAYING;
			windowP->Invalidate(true);
		}
		
	}

	if (restartRect.PtInRect(CPoint(x, y)))
	{
		seed = seed;
		windowP->KillTimer(1);
		Init(numRows, numCols, windowP);
		InitRandom(windowP);
		CLifeStatus = READY;
		windowP->Invalidate(true);

	}
	
}

/*10*/ void CLife::Move (char direction, CFrameWnd * windowP)
{
	// This function will: Move a cell square.

	CRect oldWhere;
	switch (direction)
	{
		case 'a': // moving left
			break;
		case 'w': // moving up
			break;
		case 'd': // moving right
			break;
		case 's': // moving down
			break;
	}
	CRect newWhere;
	windowP->InvalidateRect (oldWhere | newWhere);
}

/*11*/ void CLife::UpdateTime (CFrameWnd * windowP)
{
	// This function will: update the game.

	if (!finished)
	{
		Next(windowP);
		//windowP->Invalidate(true);
	}
	else
	{
		windowP->KillTimer(1);
		CLifeStatus = FINISHED;
	}
}

/*12*/ void CLife::Message (CFrameWnd * windowP)
{
	// This function will: display end message when game terminates given event.

	CString message = "Thank you for playing!\n\n";
	CString title = "Game Over";
	switch (finished)
	{
		case -1: message += "The community has vanished.";
			break;
		default: message += "The community has entered a stable pattern.";
	}
	windowP->KillTimer(1);
	windowP->MessageBox (message, title);
}

/*13*/ bool CLife::Done(CFrameWnd * windowP)
{
	// This function will: if game is done.
	if (finished == 0)
	{
		return false;
	}

	return true;
}

/*14*/ CLife::CLifeSquare::CLifeSquare ()
{
	// This function will: create initial empty border cells.

	what = BORDER;
}

/*15*/ void CLife::CLifeSquare::Display (CDC * deviceContextP)
{
	// This function will: display individual cell grid.

	deviceContextP->Rectangle(where);
	CDC memDC;
	int res = memDC.CreateCompatibleDC(deviceContextP);
	memDC.SelectObject(&images[what]);
	res = deviceContextP->TransparentBlt (where.left, where.top, where.Width(), where.Height(), &memDC, 0, 0, 100, 100, SRCCOPY); 
	DeleteDC (memDC);	
}

/*16*/ int CLife::CLifeSquare::Reset(CFrameWnd * windowP)
{
	// This function will: reset to appropiate square types. PERSON/ADDINGa is Zombie.

	if (what == ADDINGA)
	{
		what = PERSON;
		windowP->InvalidateRect (where);
		return 1;
	}
	if (what == ADDINGB)
	{
		what = HUMAN;
		windowP->InvalidateRect(where);
		return 1;
	}
	

	if (what == DELETING)
	{
		what = EMPTY;
		windowP->InvalidateRect (where);
		return -1;
	}

	return 0;
}

/*17*/ void CLife::SetUp (CRect rect)
{
	// This function will: setup the initial game squares and "field".

	int tbBorder = rect.Height() / 12;
	int lrBorder = rect.Width() / 12;
	gameRect = CRect (rect.Width() / 2.75, tbBorder, rect.Width()-lrBorder, rect.Height()-tbBorder);
	dataRect = CRect (lrBorder, rect.Height() / 2.55, rect.Width() / 4, 2 * rect.Height() / 3);

	buttonRect = CRect (lrBorder, 3 * rect.Height() / 4, rect.Width() / 4, rect.Height() - tbBorder);
	int thirdW = buttonRect.Width() / 3;
	newRect = CRect (buttonRect.left * 0.5, buttonRect.top, buttonRect.left * 1.27, buttonRect.bottom);

	playRect = CRect(buttonRect.left * 1.25, buttonRect.top, buttonRect.left + thirdW * 1.95, buttonRect.bottom);

	restartRect = CRect(buttonRect.left * 2.3, buttonRect.top, buttonRect.left + thirdW * 3.5, buttonRect.bottom);

	int sqHeight = gameRect.Height() / numRows;
	int sqWidth = gameRect.Width() / numCols;
	int top = gameRect.top + (gameRect.Height() - sqHeight * numRows) / 2;
	int left = gameRect.left + (gameRect.Width() - sqWidth * numCols) / 2;
	int size = sqHeight < sqWidth ? sqHeight : sqWidth;
	for (int r = 1; r <= numRows; r++)
		for (int c = 1; c <= numCols; c++)
		{
			grid[r][c].where = CRect(left + (c-1)*sqWidth + 1, top + (r-1)*sqHeight + 1, left + (c)*sqWidth, top + (r)*sqHeight);
		}
}

/*18*/ void CLife::DisplayGameRect (CDC * deviceContextP)
{
	// This function will: will display the cell squares. 

	for (int r = 1; r <= numRows; r++)
		for (int c = 1; c <= numCols; c++)
			grid [r][c].Display (deviceContextP);
}

/*19*/ void CLife::DisplayDataRect (CDC * deviceContextP)
{
	// This function will: display the data info rectangle
	
	CPoint corner = CPoint(dataRect.Height()/4, dataRect.Height()/4);  	
	deviceContextP->RoundRect(dataRect, corner);
	CRect genRect = CRect (dataRect.left, dataRect.top, dataRect.right, dataRect.top + dataRect.Height() / 2);
	CRect popRect = CRect (dataRect.left, dataRect.top + dataRect.Height() / 2, dataRect.right, dataRect.bottom);
	CRect HpopRect = CRect(dataRect.left, dataRect.top + dataRect.Height() / 3.5, dataRect.right, dataRect.bottom);

	char buffer [50];
	sprintf_s (buffer, "Generations: %d", generations);
	deviceContextP->DrawText(CString (buffer), genRect, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	sprintf_s (buffer, "Z Population: %d", ZpopulationSize);
	deviceContextP->DrawText(CString (buffer), popRect, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	sprintf_s(buffer, "H Population: %d", HpopulationSize);
	deviceContextP->DrawText(CString(buffer), HpopRect, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
}

/*20*/ void CLife::DisplayButtonRect (CDC * deviceContextP)
{
	// This function will: display the game change buttons.
	
	CPoint corner = CPoint(buttonRect.Height()/4, buttonRect.Height()/4);  
	deviceContextP->RoundRect(newRect, corner);
	deviceContextP->DrawText(CString ("New"), newRect, DT_SINGLELINE | DT_VCENTER | DT_CENTER);

	CPoint acorner = CPoint(buttonRect.Height() / 4, buttonRect.Height() / 4);
	deviceContextP->RoundRect(playRect, acorner);
	deviceContextP->DrawText(CString("Play/Pause"), playRect, DT_SINGLELINE | DT_VCENTER | DT_CENTER);

	CPoint bcorner = CPoint(buttonRect.Height() / 4, buttonRect.Height() / 4);
	deviceContextP->RoundRect(restartRect, bcorner);
	deviceContextP->DrawText(CString("Restart"), restartRect, DT_SINGLELINE | DT_VCENTER | DT_CENTER);



}

/*21*/ void CLife::InitRandom(CFrameWnd * windowP)
{
	// This function will: will populate a random cell game.

	srand (seed);
	for (int p = 0; p < 200; p++)
	{
		int r = 1 + rand () % numRows;
		int c = 1 + rand () % numCols;
		Add (r, c, PERSON, windowP);
	}

	for (int h = 0; h < 150; h++)
	{
		int r = 1 + rand() % numRows;
		int c = 1 + rand() % numCols;
		Add(r, c, HUMAN, windowP);
	}
}

/*22*/ void CLife::Next(CFrameWnd * windowP)
{
	// This function will: modify the game info from previous generation make changes to game status and cell squares.

	if (evaluating)
		for (int r = 1; r <= numRows; r++)
			for (int c = 1; c <= numCols; c++)
				Evaluate(r, c, windowP);
	else
	{
		for (int r = 1; r <= numRows; r++)
			for (int c = 1; c <= numCols; c++)
				ZpopulationSize += grid[r][c].Reset(windowP);
		if (ZpopulationSize == 0)
			finished = -1;	
		string mapStr = MakeString();
		map<string, int>::iterator itr = generationsMap.find(mapStr);
		if (itr == generationsMap.end())
		{
			generations++;
			generationsMap[mapStr] = generations;
		}
		else
			finished = itr->second;
		windowP->InvalidateRect (dataRect);
	}
	evaluating = !evaluating;
}

/*23*/ bool CLife::Add(int row, int col, square_types what, CFrameWnd * windowP)
{
	// This function will: add a cell of certain type and increase population counter. 

	if (row < 1 || row > numRows)
		return false;
	if (col < 1 || col > numCols)
		return false;
	if (grid[row][col].what != EMPTY)
		return false;
	grid[row][col].what = what;
	windowP->InvalidateRect(grid[row][col].where);

	if (grid[row][col].what == PERSON)
	{
		ZpopulationSize++;
	}

	else if (grid[row][col].what == HUMAN)
	{
		HpopulationSize++;
	}
}

/*24*/ bool CLife::Delete(int row, int col, CFrameWnd * windowP)
{
	// This function will: delete a cell of certain type and decrease population.

	if (row < 1 || row > numRows)
		return false;
	if (col < 1 || col > numCols)
		return false;
	if (grid[row][col].what <= EMPTY)
		return false;

	if (grid[row][col].what == PERSON)
	{
		ZpopulationSize--;
	}

	else if (grid[row][col].what == HUMAN)
	{
		HpopulationSize--;
	}

	grid[row][col].what = EMPTY;
	windowP->InvalidateRect (grid[row][col].where);

	return true;
}

/*25*/ void CLife::Evaluate(int row, int col, CFrameWnd * windowP)
{
	// This function will:  Evaluate the cell squares by checking all neighbors
	int Zneighbors = 0;
	int Hneighbors = 0;

	// PERSON is Zombie
	if (grid[row - 1][col - 1].what == PERSON || grid[row - 1][col - 1].what == DELETING)
	{
		Zneighbors++;
	}
	if (grid[row - 1][col].what == PERSON || grid[row - 1][col].what == DELETING)
	{
		Zneighbors++;
	}
	if (grid[row - 1][col + 1].what == PERSON || grid[row - 1][col + 1].what == DELETING)
	{
		Zneighbors++;
	}
	if (grid[row][col - 1].what == PERSON || grid[row][col - 1].what == DELETING)
	{
		Zneighbors++;
	}
	if (grid[row][col + 1].what == PERSON || grid[row][col + 1].what == DELETING)
	{
		Zneighbors++;
	}
	if (grid[row + 1][col - 1].what == PERSON || grid[row + 1][col - 1].what == DELETING)
	{
		Zneighbors++;
	}
	if (grid[row + 1][col].what == PERSON || grid[row + 1][col].what == DELETING)
	{
		Zneighbors++;
	}
	if (grid[row + 1][col + 1].what == PERSON || grid[row + 1][col + 1].what == DELETING)
	{
		Zneighbors++;
	}
	////////////////////////////////////////////////////////////////////////////////////////////

	if (grid[row - 1][col - 1].what == HUMAN || grid[row - 1][col - 1].what == DELETING)
	{
		Hneighbors++;
	}
	if (grid[row - 1][col].what == HUMAN || grid[row - 1][col].what == DELETING)
	{
		Hneighbors++;
	}
	if (grid[row - 1][col + 1].what == HUMAN || grid[row - 1][col + 1].what == DELETING)
	{
		Hneighbors++;
	}
	if (grid[row][col - 1].what == HUMAN || grid[row][col - 1].what == DELETING)
	{
		Hneighbors++;
	}
	if (grid[row][col + 1].what == HUMAN || grid[row][col + 1].what == DELETING)
	{
		Hneighbors++;
	}
	if (grid[row + 1][col - 1].what == HUMAN || grid[row + 1][col - 1].what == DELETING)
	{
		Hneighbors++;
	}
	if (grid[row + 1][col].what == HUMAN || grid[row + 1][col].what == DELETING)
	{
		Hneighbors++;
	}
	if (grid[row + 1][col + 1].what == HUMAN || grid[row + 1][col + 1].what == DELETING)
	{
		Hneighbors++;
	}
	////////////////////////////////////////////////////////////////////////////////////////////

	// EVALUATION //
	
	if (grid[row][col].what == EMPTY && Zneighbors == 3 && Hneighbors == 0)
	{
		grid[row][col].what = ADDINGA;
		windowP->InvalidateRect(grid[row][col].where);

	}
	else if (grid[row][col].what == PERSON && Zneighbors < Hneighbors)
	{
		grid[row][col].what = DELETING;
		windowP->InvalidateRect(grid[row][col].where);

	}
	else if (grid[row][col].what == PERSON && Zneighbors < 2)
	{
		grid[row][col].what = DELETING;
		windowP->InvalidateRect(grid[row][col].where);

	}
	else if (grid[row][col].what == HUMAN && Zneighbors > Hneighbors)
	{
		grid[row][col].what = ADDINGA;
		windowP->InvalidateRect(grid[row][col].where);

	}
	else if (grid[row][col].what == EMPTY && Hneighbors == 3)
	{
		grid[row][col].what = ADDINGB;
		windowP->InvalidateRect(grid[row][col].where);

	}
	else if (grid[row][col].what == HUMAN && Hneighbors == 6)
	{
		grid[row][col].what = DELETING;
		windowP->InvalidateRect(grid[row][col].where);

	}

}

/*26*/ string CLife::MakeString() const
{
	// This function will: create of string of all the cells squares to check for stablelized state. 
	string str;

	for (int r = 1; r <= numRows; r++)
	{
		for (int c = 1; c <= numCols; c++)
		{
			if (grid[r][c].what == EMPTY)
			{
				str += 'E';
			}

			else if (grid[r][c].what == PERSON)
			{
				str += 'P';
			}

			else if (grid[r][c].what == HUMAN)
			{
				str += 'H';
			}
		}
	}
	return str;
}
