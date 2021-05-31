#include "CApp.h"
#include <tchar.h>

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "windowscodecs.lib")

CApp* CApp::m_pApp = nullptr;

CApp::CApp()
{
}

CApp::~CApp() 
{
}

bool CApp::Initialize(HINSTANCE _hInstance, int _nCmdShow)
{
	m_pWnd = CWnd::GetInstance();

	if (!m_pWnd->Initialize(_hInstance, _nCmdShow))
		return false;

	m_hWnd[0] = m_pWnd->SetWindow(_T("wnd1"), 1136, 660);
	m_hWnd[1] = m_pWnd->SetWindow(_T("wnd2"), 500, 500);

	//if (!g_device.InitDevice(m_hWnd[0]))
	//	return false;

	m_pWnd->Render(m_hWnd[0]);
	m_pWnd->Render(m_hWnd[1]);

	return true;
		}

void CApp::Cleanup(void)
{
	//g_device.CleanupDevice();
}

int CApp::Run(void)
{
	return m_pWnd->Run();
}
