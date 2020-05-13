#pragma once

#include <afxwin.h>
#include <winver.h>

class CLab09Win : public CFrameWnd
{
public:
	CLab09Win();
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
private:
	int MessageX;
	int MessageY;
	CString Message;
	CRect Locations[10];
	COLORREF Colors[10];
	DECLARE_MESSAGE_MAP()
};

