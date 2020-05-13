// File: CLife.cpp
// Author: 
// Project: CS215 Project 3 Fall 2016
// Description of file contents: 

#include "CLife.h"
#include <time.h>

CBitmap bgImage;
static CBitmap images [MAXTYPES];

using namespace std;

/*1*/ CLife::CLife ()
{
	// This function will: 

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
	// This function will: 

}

/*3*/CLife::~CLife ()
{
	// This function will: 

	for (int r = 0; r < numRows + 2; r++)
		delete[] grid[r];
	delete[] grid;

}

/*4*/ CLife & CLife::operator = (const CLife & other)
{
	// This function will: 

	return *this;
}

/*5*/ void CLife::LoadResources ()
{
	// This function will: 

	int res = bgImage.LoadBitmap(CString("BACKGROUND_BMP"));
	res = images[BORDER].LoadBitmap(CString("EMPTY_BMP"));
	res = images[EMPTY].LoadBitmap(CString("EMPTY_BMP"));		
	res = images[ADDING].LoadBitmap(CString("PERSON_BMP"));
	res = images[PERSON].LoadBitmap(CString("PERSON_BMP"));
	res = images[DELETING].LoadBitmap(CString("PERSON_BMP"));
}

/*6*/ void CLife::Init (int R, int C, CFrameWnd * windowP)
{
	// This function will: 

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
	populationSize = 0;
	generations = 0;	
	finished = 0;
	evaluating = true;
	CLifeStatus = NEW;
}

/*7*/ void CLife::Instructions (CFrameWnd * windowP)
{
	// This function will: 

     CString message;
	 message += "These are the instructions for my game.\n";
     
	CString title = "Instructions";
	windowP->MessageBox (message, title);
}

/*8*/ void CLife::Display (CFrameWnd * windowP)
{
	// This function will: 

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
	CString fontName = "Comic Sans";
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
	// This function will: Handle a mouse click

	if (newRect.PtInRect(CPoint(x, y)))
	{
		seed = time(NULL) % 10000;
		windowP->KillTimer(1);
		Init (numRows, numCols, windowP);
		InitRandom(windowP);
		CLifeStatus = READY;
		windowP->Invalidate(true);	
	}
}

/*10*/ void CLife::Move (char direction, CFrameWnd * windowP)
{
	// This function will:

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
	// This function will: 

	if (!finished)
		Next (windowP);
	else
	{
		windowP->KillTimer(1);
		CLifeStatus = FINISHED;
	}
}

/*12*/ void CLife::Message (CFrameWnd * windowP)
{
	// This function will:

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
	// This function will: 

	return finished != 0;
}

/*14*/ CLife::CLifeSquare::CLifeSquare ()
{
	// This function will: 

	what = BORDER;
}

/*15*/ void CLife::CLifeSquare::Display (CDC * deviceContextP)
{
	// This function will: 

	deviceContextP->Rectangle(where);
	CDC memDC;
	int res = memDC.CreateCompatibleDC(deviceContextP);
	memDC.SelectObject(&images[what]);
	res = deviceContextP->TransparentBlt (where.left, where.top, where.Width(), where.Height(), &memDC, 0, 0, 100, 100, SRCCOPY); 
	DeleteDC (memDC);	
}

/*16*/ int CLife::CLifeSquare::Reset(CFrameWnd * windowP)
{
	// This function will: 

	if (what == ADDING)
	{
		what = PERSON;
		windowP->InvalidateRect (where);
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
	// This function will: 

	int tbBorder = rect.Height() / 12;
	int lrBorder = rect.Width() / 12;
	gameRect = CRect (rect.Width() / 3, tbBorder, rect.Width()-lrBorder, rect.Height()-tbBorder);
	dataRect = CRect (lrBorder, rect.Height() / 3, rect.Width() / 4, 2 * rect.Height() / 3);
	buttonRect = CRect (lrBorder, 3 * rect.Height() / 4, rect.Width() / 4, rect.Height() - tbBorder);
	int thirdW = buttonRect.Width() / 3;
	newRect = CRect (buttonRect.left, buttonRect.top, buttonRect.left + thirdW, buttonRect.bottom);

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
	// This function will: 

	for (int r = 1; r <= numRows; r++)
		for (int c = 1; c <= numCols; c++)
			grid [r][c].Display (deviceContextP);
}

/*19*/ void CLife::DisplayDataRect (CDC * deviceContextP)
{
	// This function will: 
	
	CPoint corner = CPoint(dataRect.Height()/4, dataRect.Height()/4);  	
	deviceContextP->RoundRect(dataRect, corner);
	CRect genRect = CRect (dataRect.left, dataRect.top, dataRect.right, dataRect.top + dataRect.Height() / 2);
	CRect popRect = CRect (dataRect.left, dataRect.top + dataRect.Height() / 2, dataRect.right, dataRect.bottom);
	char buffer [50];
	sprintf_s (buffer, "Generations: %d", generations);
	deviceContextP->DrawText(CString (buffer), genRect, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	sprintf_s (buffer, "Population: %d", populationSize);
	deviceContextP->DrawText(CString (buffer), popRect, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
}

/*20*/ void CLife::DisplayButtonRect (CDC * deviceContextP)
{
	// This function will: 
	
	CPoint corner = CPoint(buttonRect.Height()/4, buttonRect.Height()/4);  
	deviceContextP->RoundRect(newRect, corner);
	deviceContextP->DrawText(CString ("New"), newRect, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
}

/*21*/ void CLife::InitRandom(CFrameWnd * windowP)
{
	// This function will: 

	srand (seed);
	for (int p = 0; p < 20; p++)
	{
		int r = 1 + rand () % numRows;
		int c = 1 + rand () % numCols;
		Add (r, c, PERSON, windowP);
	}
}

/*22*/ void CLife::Next(CFrameWnd * windowP)
{
	// This function will: 

	if (evaluating)
		for (int r = 1; r <= numRows; r++)
			for (int c = 1; c <= numCols; c++)
				Evaluate(r, c, windowP);
	else
	{
		for (int r = 1; r <= numRows; r++)
			for (int c = 1; c <= numCols; c++)
				populationSize += grid[r][c].Reset(windowP);
		if (populationSize == 0)
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
	// This function will: 

	if (row < 1 || row > numRows)
		return false;
	if (col < 1 || col > numCols)
		return false;
	if (grid[row][col].what != EMPTY)
		return false;
	grid[row][col].what = what;
	windowP->InvalidateRect (grid[row][col].where);
	populationSize++;
	return true;
}

/*24*/ bool CLife::Delete(int row, int col, CFrameWnd * windowP)
{
	// This function will: 

	if (row < 1 || row > numRows)
		return false;
	if (col < 1 || col > numCols)
		return false;
	if (grid[row][col].what <= EMPTY)
		return false;
	grid[row][col].what = EMPTY;
	windowP->InvalidateRect (grid[row][col].where);
	populationSize--;
	return true;
}

/*25*/ void CLife::Evaluate(int row, int col, CFrameWnd * windowP)
{
	// This function will: 
}

/*26*/ string CLife::MakeString() const
{
	// This function will: 
	string str;
	return str;
}
