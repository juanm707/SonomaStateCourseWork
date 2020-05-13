#include "CGraphicsDesign.h"
CGraphicsDesign::CGraphicsDesign ()
{
	CurrentColor = RGB(255, 255, 255);
	CurrentShape = 'S';
	CurrentSize = 40;
	SelectedShape = -1;
}

void CGraphicsDesign::Paint (CPaintDC * dc)
{
	for (unsigned i = 0; i < Many.size(); i++)
		Many[i].Paint(dc);
}

CRect CGraphicsDesign::AddShape (int X, int Y)
{
	CGraphicsShape One = CGraphicsShape (CurrentColor, CurrentShape, X, Y, CurrentSize);
	Many.push_back(One);
	return One.GetWhere();
}

CRect CGraphicsDesign::SelectShape(int x, int y)
{
	CRect oldWhere, newWhere;
	if (SelectedShape != -1)
	{
		oldWhere = newWhere = Many[SelectedShape].GetWhere();
		Many[SelectedShape].SetSelected(false);
	}
	SelectedShape = -1;
	for (int i = Many.size() - 1; SelectedShape == -1 && i >= 0; i--)
	{
		if (Many[i].InShape(x, y))
		{
			SelectedShape = i;
		}
	}

	if (SelectedShape != 1)
	{
		Many[SelectedShape].SetSelected(true);
		newWhere = Many[SelectedShape].GetWhere();
	}
	return oldWhere | newWhere;
}

CRect CGraphicsDesign::MoveShape(int dx, int dy)
{
	CRect oldWhere, newWhere;
	if (SelectedShape != -1)
	{
		oldWhere = Many[SelectedShape].GetWhere();
		Many[SelectedShape].Move(dx, dy);
		newWhere = Many[SelectedShape].GetWhere();
	}
	return oldWhere | newWhere;
}

CRect CGraphicsDesign::ResizeShape(int ds)
{
	CRect oldWhere, newWhere;
	if (SelectedShape != -1)
	{
		oldWhere = Many[SelectedShape].GetWhere();
		Many[SelectedShape].Resize(ds);
		newWhere = Many[SelectedShape].GetWhere();
	}
	return oldWhere | newWhere;
}

void CGraphicsDesign::SetColor (char C)
{
	if (C == 'R')
		CurrentColor = RGB(255, 0, 0);
	else if (C == 'G')
		CurrentColor = RGB(0, 255, 0);
	else if (C == 'B')
		CurrentColor = RGB(0, 0, 255);
}

void CGraphicsDesign::SetShape (char S)
{
	CurrentShape = S;
}
