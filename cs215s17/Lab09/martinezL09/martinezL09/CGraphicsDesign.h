#include <afxwin.h>
#include <vector>
#include "CGraphicsShape.h"

using namespace std;

class CGraphicsDesign
{
	public:
		CGraphicsDesign ();
		void Paint (CPaintDC * dc);
		CRect AddShape(int X, int Y);
		void SetColor (char C);
		void SetShape (char S);
		CRect SelectShape(int x, int y);
		CRect MoveShape(int dx, int dy);
		CRect ResizeShape(int ds);
	private:
		COLORREF CurrentColor;
		char CurrentShape;
		int CurrentSize;
		int CurrentX;
		int CurrentY;
		int SelectedShape;
		vector <CGraphicsShape> Many;
};