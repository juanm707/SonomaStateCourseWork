// File: CLifeWin.cpp
// Author: 
// Project: CS215 Project 3 Spring 2015
// Description of file contents:

#include <afxwin.h>
#include "CLifeWin.h"

/*1*/ CLifeWin::CLifeWin ()
{
// This function will:

		CString WindowTitle = "The Name of My Game";
		Create (NULL, WindowTitle);
		myLife.LoadResources();
		myLife.Init(0, 0, this);
		firstTime = true;
}

/*2*/ afx_msg void CLifeWin::OnPaint ()
{
// This function will:

		myLife.Display (this);
		if (firstTime)
		{
			myLife.Instructions(this);
			firstTime = false;
		}
}

/*3*/ afx_msg void CLifeWin::OnLButtonDown( UINT nFlags, CPoint point )
{
// This function will:

	myLife.Click (point.y, point.x, this);
}

/*4*/ afx_msg void CLifeWin::OnKeyDown (UINT achar, UINT repeat, UINT flags)
{
	switch(achar)
    {
		case VK_LEFT: case 'A':
			myLife.Move ('a', this);
			break;
		case VK_RIGHT: case 'D':
			myLife.Move ('d', this);
			break;
		case VK_UP: case 'W':
			myLife.Move ('w', this);
			break;
		case VK_DOWN: case 'S':
			myLife.Move ('s', this);
			break;
	}
}

/*5*/ afx_msg void CLifeWin::OnTimer (UINT nIDEvent)
{	
	// This function will: Handle timer events

	if (nIDEvent == 1)
		myLife.UpdateTime (this);  
	if (myLife.Done(this)) //?
		myLife.Message (this);
}

BEGIN_MESSAGE_MAP (CLifeWin, CFrameWnd)
	ON_WM_PAINT ()
	ON_WM_LBUTTONDOWN( )
	ON_WM_TIMER ()
END_MESSAGE_MAP ()
