#include <afxwin.h>
#include "CLab09Win.h"

CLab09Win::CLab09Win()
{
	Create(NULL, CString("Lab09"));
	MessageX = 100;
	MessageY = 100;
	Message = "Hello World";
	srand(int(time(NULL)));

	for (int i = 0; i < 10; i++)
	{
		int ulX = rand() % 800;
		int ulY = rand() % 400;
		int lrX = ulX + 20 + rand() % 400;
		int lrY = ulY + 10 + rand() % 200;

		Locations[i] = CRect(ulX, ulY, lrX, lrY);
		int red = rand() % 255;
		int green = rand() % 255;
		int blue = rand() % 255;
		Colors[i] = RGB(red, green, blue);
	}
}

afx_msg void CLab09Win::OnPaint()
{
	CPaintDC dc(this);
	for (int i = 0; i < 10; i++)
	{
		CBrush * newBrush = new CBrush(Colors[i]);
		CBrush * saveBrush = dc.SelectObject(newBrush);

		dc.Rectangle(Locations[i]);
		dc.SelectObject(saveBrush);
		delete newBrush;
	}
	dc.SetBkMode(TRANSPARENT);
	dc.DrawText(Message, CRect(MessageX, MessageY, MessageX + 80,
		MessageY + 16), DT_LEFT);
}

afx_msg void CLab09Win::OnMouseMove(UINT nFlags, CPoint point)
{
	if (nFlags == MK_LBUTTON)
	{
		CRect oldRect = CRect(MessageX, MessageY, MessageX + 80, MessageY + 16);
		MessageX = point.x;
		MessageY = point.y;
		CRect newRect = CRect(MessageX, MessageY, MessageX + 80, MessageY + 16);
		InvalidateRect(oldRect | newRect);
	}
}

BEGIN_MESSAGE_MAP(CLab09Win, CFrameWnd)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

