#pragma once
#include <Windows.h>
#include <tchar.h>

class CMouse {
public:
	DWORD m_mouseX;
	DWORD m_mouseY;
public:
	CMouse() 
	{
		m_mouseX = 0;
		m_mouseY = 0;
	}
	~CMouse() {}

	void Render(HWND _hWnd);
};