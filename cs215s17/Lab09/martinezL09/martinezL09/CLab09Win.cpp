#include <afxwin.h>
#include "CLab09Win.h"

CLab09Win::CLab09Win ()
{
	CString WindowTitle = "Graphics";
	Create (NULL, WindowTitle);
}
afx_msg void CLab09Win::OnPaint ()
{
	CPaintDC dc (this);
	design.Paint (&dc);
}
afx_msg void CLab09Win::OnKeyDown (UINT achar, UINT repeat, UINT flags)
{
	CRect modified;
    switch(achar)
    {
	case 'B': // 'b'
		design.SetColor ('B');
		break;
	case 'C': // 'c'
		design.SetShape ('C');
		break;
	case 'G': // 'g'
		design.SetColor ('G');
		break;
	case 'R': // 'r'
		design.SetColor ('R');
		break;
	case 'S': // 's'
		design.SetShape ('S');
		break;
	case 39: // right arrow
		modified = design.MoveShape(1, 0);
		InvalidateRect(modified);
		break;
	case 107: // '+' (numeric pad)
		modified = design.ResizeShape(2);
		InvalidateRect(modified);
		break;
    };
}
afx_msg void CLab09Win::OnRButtonDown (UINT flags, CPoint point)
{
	design.AddShape(point.x, point.y);
	Invalidate (TRUE);
}

afx_msg void CLab09Win::OnLButtonDown(UINT flags, CPoint point)
{
	CRect selected = design.SelectShape(point.x, point.y);

	current = point;
	InvalidateRect(selected);
}

afx_msg void CLab09Win::OnMouseMove(UINT flags, CPoint point)
{
	if (flags == MK_LBUTTON)
	{
		int deltaX = point.x - current.x;
		int deltaY = point.y - current.y;
		CRect modified = design.MoveShape(deltaX, deltaY);
		current = point;
		InvalidateRect(modified);
	}
}

BEGIN_MESSAGE_MAP (CLab09Win, CFrameWnd)
	ON_WM_PAINT ()
	ON_WM_KEYDOWN ()
	ON_WM_RBUTTONDOWN ()
	ON_WM_LBUTTONDOWN ()
	ON_WM_MOUSEMOVE ()
END_MESSAGE_MAP ()
