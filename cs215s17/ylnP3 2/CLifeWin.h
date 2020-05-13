// File: CLifeWin.h
// Author: 
// Project: CS215 Project 3 Spring 2015
// Description of file contents:

#include <afxwin.h>
#include "CLife.h"

class CLifeWin : public CFrameWnd
{
	public:
/*1*/		CLifeWin ();
/*2*/		afx_msg void OnPaint ();
/*3*/		afx_msg void OnLButtonDown( UINT nFlags, CPoint point );
/*4*/		afx_msg void OnKeyDown (UINT achar, UINT repeat, UINT flags);
/*5*/		afx_msg void OnTimer (UINT nIDEvent);
	private:
		CLife myLife;
		bool firstTime;
		DECLARE_MESSAGE_MAP ()
};
