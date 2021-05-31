#pragma once
#include <Windows.h>
#include <d2d1.h>
#include <wincodec.h>
#include "CDevice.h"
#include "CWnd.h"
#include <tchar.h>

class CApp {
private:
	static CApp*	m_pApp;
	CWnd*			m_pWnd;
	HWND			m_hWnd[2];
private:
	CApp();
public:
	~CApp();

	static CApp* GetInstance(void)
	{
		if (m_pApp == nullptr)	m_pApp = new CApp();

		return m_pApp;
	}

	bool	Initialize(HINSTANCE _hInstance, int _nCmdShow);
	void	Cleanup(void);
	int		Run(void);
};