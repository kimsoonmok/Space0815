#include "CWnd.h"

//CWnd g_wnd;

CWnd* CWnd::m_pWnd = nullptr;

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	return CWnd::GetInstance()->MessageProc(hWnd, uMessage, wParam, lParam);
}

CWnd::CWnd()
{
}

CWnd::~CWnd()
{

}

BOOL CWnd::Initialize(HINSTANCE _hInstance, int _nCmdShow)
{
	m_lpcWindowClassName = _T("Window Class Name");
	m_hInst = _hInstance;
	m_nCmdShow = _nCmdShow;

	m_wcex.cbSize = sizeof(WNDCLASSEX);
	m_wcex.style = CS_HREDRAW | CS_VREDRAW;
	m_wcex.lpfnWndProc = WndProc;
	m_wcex.cbClsExtra = 0;
	m_wcex.cbWndExtra = 0;
	m_wcex.hInstance = _hInstance;
	m_wcex.hIcon = LoadIcon(_hInstance, IDI_APPLICATION);
	m_wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	m_wcex.lpszMenuName = NULL;
	m_wcex.lpszClassName = m_lpcWindowClassName;

	if (!RegisterClassEx(&m_wcex))
	{
		MessageBox(NULL,
			_T("Call to RegisterClassEx failed!"),
			_T("Windows Desktop Guided Tour"),
			NULL);

		return false;
	}

	return true;
}

HWND CWnd::SetWindow(const TCHAR* _lpcTitleName, DWORD _width, DWORD _height)
{
	m_hWnd = CreateWindow(
		m_lpcWindowClassName,
		_lpcTitleName,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		_width, _height,
		NULL,
		NULL,
		m_hInst,
		NULL
	);

	if (!m_hWnd)
	{
		MessageBox(NULL,
			_lpcTitleName,
			_T("Windows Desktop Guided Tour"),
			NULL);

		return 0;
	}

	return m_hWnd;
}

void CWnd::Render(HWND _hWnd)
{
	ShowWindow(_hWnd, m_nCmdShow);
	UpdateWindow(_hWnd);
}

int CWnd::Run(void)
{
	MSG msg = { 0 };

	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg); // 여기서 WndProc를 호출하는데 같은 위치에 있어야하나 ?
			DispatchMessage(&msg);
		}

		Sleep(1);
	}

	return (int)msg.wParam;
}

LRESULT CWnd::MessageProc(HWND _hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (uMessage)
	{
	case WM_CREATE:
		break;

	case WM_KEYDOWN:
		break;

	case WM_PAINT:
		hdc = BeginPaint(_hWnd, &ps);
		EndPaint(_hWnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(_hWnd, uMessage, wParam, lParam);
		break;
	}

	return 0;
}
