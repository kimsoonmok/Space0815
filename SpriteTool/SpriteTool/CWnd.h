#pragma once
#include <d2d1.h>
#include <Windows.h>
#include <tchar.h>

class CWnd
{
private:
	static CWnd*	m_pWnd;
	HWND			m_hWnd;
	WNDCLASSEX		m_wcex;

	//const TCHAR* m_lpcWindowClassName;
	const TCHAR*	m_lpcWindowClassName;
	HINSTANCE		m_hInst;
	int				m_nCmdShow;
public:
	CWnd();
	~CWnd();

	static CWnd* GetInstance(void)
	{
		if (m_pWnd == nullptr) m_pWnd = new CWnd();

		return m_pWnd;
	}

	BOOL Initialize(HINSTANCE _hInstance, int _nCmdShow);
	HWND SetWindow(const TCHAR* _lpcTitleName, DWORD _width, DWORD _height);
	void Render(HWND _hWnd); 
	int Run(void);

	LRESULT CALLBACK MessageProc(HWND _hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam);
};

//extern CWnd g_wnd;