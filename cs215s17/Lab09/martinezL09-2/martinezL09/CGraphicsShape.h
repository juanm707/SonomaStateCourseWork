#include <afxwin.h>

using namespace std;

class CGraphicsShape
{
	public:
		CGraphicsShape ();
		CGraphicsShape (COLORREF C, char S, int X, int Y, int Z, CString I);
		CRect GetWhere() const;
		bool InShape(int x, int y) const;
		void SetSelected(bool flag);
		void Move(int dx, int dy);
		void Resize(int ds);
		void Paint (CPaintDC * dc);
	private:
		COLORREF Color;
		char WhichShape;
		int CenterX;
		int CenterY;
		int Size;
		CRect Where;
		bool Selected;
		CString ImageName;
};