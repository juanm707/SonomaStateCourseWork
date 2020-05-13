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

CGraphicsShape::CGraphicsShape (COLORREF C, char S, int X, int Y, int Z)
{
	Color = C;
	WhichShape = S;
	CenterX = X;
	CenterY = Y;
	Size = Z;
	Where = CRect(CenterX - Z / 2, CenterY - Z / 2, CenterX + Z / 2, CenterY + Z / 2);
	Selected = false;
}

CRect CGraphicsShape::GetWhere() const
{
	return Where;
}

bool CGraphicsShape::InShape(int x, int y) const
{
	if (WhichShape == 'S')
	{
		if (x >= (CenterX - Size/2) && x <= (CenterX + Size/2))
			if(y >=(CenterX - Size/2) && y <=(CenterX + Size/2))
			{
				return TRUE;
			}
	}
	else if (WhichShape == 'C')
	{
		float radius = Size / 2;
		if()

	}
	return false;
}

void CGraphicsShape::SetSelected(bool flag)
{
	Selected = flag;
}

void CGraphicsShape::Resize(int ds)
{

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

	CPen pen, *pPenSv;
	pen.CreatePen(PS_DOT, 1, RGB(0, 0, 0));

	if (Selected)
		pPenSv = dc->SelectObject(&pen);

	if (WhichShape == 'S')
		dc->Rectangle (CenterX-Size/2, CenterY-Size/2, CenterX+Size/2, CenterY+Size/2);
	else if (WhichShape == 'C')
		dc->Ellipse (CenterX-Size/2, CenterY-Size/2, CenterX+Size/2, CenterY+Size/2);
	dc->SelectObject (pBrushSv);
	
	if (Selected)
		dc->SelectObject(pPenSv);
}