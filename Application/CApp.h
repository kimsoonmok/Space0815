#pragma once
#include <Windows.h>
#include <d2d1.h>
#include <wincodec.h>
#include "CFrameRate.h"
#include "CMouse.h"
#include "CDevice.h"
#include <tchar.h>
#include "CBackground.h"
#include "CManager.h"
#pragma comment( lib, "d2d1.lib")
#pragma comment(lib, "windowscodecs.lib")

class CApp {
private :
	static CApp*			m_pApp;
	HWND					m_hWnd;
	CFrameRate				m_frameRate;

	CBackground*			m_background;
	CManager*				m_pManager;
private :
	CApp();
public:
	~CApp();

	static CApp* GetInstance(void)
	{
		if (m_pApp == nullptr)	m_pApp = new CApp(); // 한번만 호출해줘야함

		return m_pApp;
	}

	CApp* GetCApp(void)
	{
		return m_pApp;
	}

	bool	Initialize(HINSTANCE _hInstance, int _nCmdShow, const TCHAR* _lpcWindowClassName, const TCHAR* _lpcTitleName, DWORD _width, DWORD _height);
	void	Cleanup(void);
	int		Run(void);
	void	Update(void);
	void	Render(void);
	
	LRESULT CALLBACK MessageProc(HWND _hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam);
};

//CApp* g_app = nullptr;