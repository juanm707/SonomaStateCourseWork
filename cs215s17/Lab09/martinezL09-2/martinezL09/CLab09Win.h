#include <afxwin.h>
#include "CGraphicsDesign.h"

class CLab09Win : public CFrameWnd
{
	public:
		CLab09Win ();
		afx_msg void OnPaint ();
		afx_msg void OnKeyDown (UINT achar, UINT repeat, UINT flags);
		afx_msg void OnRButtonDown (UINT flags, CPoint point);

		afx_msg void OnLButtonDown(UINT flags, CPoint point);
		afx_msg void OnMouseMove(UINT flags, CPoint point);

	private:
		CGraphicsDesign design;
		CPoint current;
		DECLARE_MESSAGE_MAP ()
};
