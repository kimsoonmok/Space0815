#include "CApp.h"
#include <tchar.h>

//CApp* CApp::m_app = nullptr ;
CApp* CApp::m_pApp = nullptr;

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	//CApp::m_pApp = new CApp();
	CApp::GetInstance();
	// 한글 : CApp의 instance가 가지고 있는 프로시저 함수를 호출해라
	return CApp::GetInstance()->MessageProc(hWnd, uMessage, wParam, lParam);
}

CApp::CApp() : 
	m_frameRate(100)
{
}

CApp::~CApp() {

}

bool CApp::Initialize(HINSTANCE _hInstance, int _nCmdShow, const TCHAR* _lpcWindowClassName, const TCHAR* _lpcTitleName, DWORD _width, DWORD _height)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = _hInstance;
	wcex.hIcon = LoadIcon(_hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = _lpcWindowClassName;
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL,
			_T("Call to RegisterClassEx failed!"),
			_T("Windows Desktop Guided Tour"),
			NULL);

		return false;
	}

	HWND hWnd = CreateWindow(
		_lpcWindowClassName,
		_lpcTitleName,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		_width, _height,
		NULL,
		NULL,
		_hInstance,
		NULL
	);

	m_hWnd = hWnd;

	if (!hWnd)
	{
		MessageBox(NULL,
			_T("Call to CreateWindow failed!"),
			_T("Windows Desktop Guided Tour"),
			NULL);

		return false;
	}

	ShowWindow(hWnd, _nCmdShow); // check
	UpdateWindow(hWnd); // check

	if (!g_device.InitDevice(hWnd))
		return 1;

	//m_player = new CPlayer(_T("Mobile - Cookie Run - Brave Cookie.png"), m_hWnd);
	m_background = new CBackground(m_hWnd);
	m_pManager = new CManager(m_hWnd);

	return true;
}

void CApp::Cleanup(void)
{
	if (m_pManager) delete m_pManager;
	if (m_background) delete m_background;
	g_device.CleanupDevice();
}

int CApp::Run(void)
{
	MSG msg = { 0 };

	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (m_frameRate.IsFrame())
		{
			Render();
			Update();
		}
		Sleep(1);
	}

	return (int)msg.wParam;
}

void CApp::Update(void)
{
	m_background->Update();
	m_pManager->Update();
}


void CApp::Render(void)
{
	g_device.GetRenderTarget()->BeginDraw();
	g_device.GetRenderTarget()->Clear(D2D1::ColorF(D2D1::ColorF::White));

	m_background->Render();
	m_pManager->Render();

	g_device.GetRenderTarget()->EndDraw();

	m_frameRate.Render(m_hWnd); // BeginDraw와 EndDraw 사이에 있으면 출력이 제대로 이루어지지않음.
}

LRESULT CApp::MessageProc(HWND _hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	
	switch (uMessage)
	{
	case WM_CREATE:
		break;

	case WM_KEYDOWN :
		break;

	case WM_PAINT:
		hdc = BeginPaint(_hWnd, &ps);
		EndPaint(_hWnd, &ps);
		break;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              

	case WM_DESTROY:
		Cleanup();
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(_hWnd, uMessage, wParam, lParam);
		break;
	}

	return 0;
}
