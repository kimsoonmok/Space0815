#include "CMouse.h"

void CMouse::Render(HWND _hWnd)
{
	HDC hdc = GetDC(_hWnd);

	TCHAR buf[100];
	_stprintf_s(buf, 100, _T("X:%d, Y:%d"), m_mouseX, m_mouseY);
	TextOut(hdc, m_mouseX, m_mouseY, buf, _tcslen(buf));

	ReleaseDC(_hWnd, hdc);
}
