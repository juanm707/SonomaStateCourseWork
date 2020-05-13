// File: CLifeApp.cpp
// Author: 
// Project: CS215 Project 3 Spring 2015
// Description of file contents:

#include <afxwin.h>
#include "CLifeApp.h"


/*1*/ BOOL CLifeApp::InitInstance ()
{
// This function will:

		m_pMainWnd = new CLifeWin();
		m_pMainWnd->ShowWindow (m_nCmdShow);
		m_pMainWnd->UpdateWindow ();

		return TRUE;
}

CLifeApp CLifeApp;
