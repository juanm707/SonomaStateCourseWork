#include <cmath>
#include "CGraphicsShape.h"

CGraphicsShape::CGraphicsShape ()
{
	Color = RGB(255, 255, 255);
	WhichShape = 'S';
	CenterX = 100;
	CenterY = 100;
	Size = 40;
	Where = CRect(80, 80, 120, 120);
	Selected = false;
}

CGraphicsShape::CGraphicsShape (COLORREF C, char S, int X, int Y, int Z, CString I)
{
	Color = C;
	WhichShape = S;
	CenterX = X;
	CenterY = Y;
	Size = Z;
	Where = CRect(CenterX - Z / 2, CenterY - Z / 2, CenterX + Z / 2, CenterY + Z / 2);
	Selected = false;
	ImageName = I;
}

CRect CGraphicsShape::GetWhere() const
{
	return Where;
}

bool CGraphicsShape::InShape(int x, int y) const
{
	if (WhichShape == 'S')
	{
		if (x >= (CenterX - Size / 2) && x <= (CenterX + Size / 2))
		{
			if (y >= (CenterY - Size / 2) && y <= (CenterY + Size / 2))
			{
				return true;
			}
		}
	}
	else if (WhichShape == 'C')
	{
		double radius = Size / 2;
		double distance = sqrt(((CenterX - x)*(CenterX - x)) + ((CenterY - y)*(CenterY - y)));
		if (distance > radius)
		{
			return false;
		}

		else if (distance <= radius)
		{
			return true;
		}

	}
	return false;
}

void CGraphicsShape::SetSelected(bool flag)
{
	Selected = flag;
}

void CGraphicsShape::Resize(int ds)
{
	Size += ds;
	Where.top -= ds / 2;
	Where.bottom += ds / 2;
	Where.left -= ds / 2;
	Where.right += ds / 2;

}

void CGraphicsShape::Move(int dx, int dy)
{
	Where.left += dx;
	Where.right += dx;
	Where.top += dy;
	Where.bottom += dy;
	CenterX += dx;
	CenterY += dy;
}

void CGraphicsShape::Paint (CPaintDC * dc)
{
	CBrush paintBrush;
	paintBrush.CreateSolidBrush (Color);
	CBrush * pBrushSv = dc->SelectObject (&paintBrush);

	CPen pen, *pPenSv = NULL;
	pen.CreatePen(PS_DOT, 1, RGB(0, 0, 0));

	if (Selected)
		pPenSv = dc->SelectObject(&pen);

	if (WhichShape == 'S')
		dc->Rectangle (Where);
	else if (WhichShape == 'C')
		dc->Ellipse (Where);
	dc->SelectObject (pBrushSv);
	
	if (Selected)
		dc->SelectObject(pPenSv);
	if (ImageName != "")
	{
		CBitmap Image;
		int res = Image.LoadBitmapW(CString(ImageName));
		CDC memDC;
		memDC.CreateCompatibleDC(dc);
		memDC.SelectObject(&Image);
		dc->TransparentBlt(Where.left+1, Where.top+1, Where.Width()-2, Where.Height() - 2, &memDC, 0, 0, 80, 80, SRCCOPY);

	}
}