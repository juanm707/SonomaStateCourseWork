// File: CLifeApp.cpp
// Author: Juan Martinez
// Project: CS215 Project 3 Spring 2017
// Description of file contents:Implementation for application program, updates/displays game window.

#include <afxwin.h>
#include "CLifeApp.h"


/*1*/ BOOL CLifeApp::InitInstance ()
{
// This function will: Start a new Cell Life game.

		m_pMainWnd = new CLifeWin();
		m_pMainWnd->ShowWindow (m_nCmdShow);
		m_pMainWnd->UpdateWindow ();

		return TRUE;
}

CLifeApp CLifeApp;
