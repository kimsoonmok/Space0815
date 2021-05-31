#include <Windows.h>
#include <TCHAR.h>
#include "resource.h"
LRESULT CALLBACK WndProc(HWND _hWnd, UINT _iMsg, WPARAM _wParam, LPARAM _lParam);
BOOL CALLBACK Dlg6_1Proc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM _lParam);

HINSTANCE g_hInst;

int WINAPI WinMain(
	HINSTANCE hInstance, 
	HINSTANCE hPrevInstance, 
	LPSTR lpszCmdLine, 
	int nCmdShow)
{
	HWND hWnd;
	MSG	msg;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.style = 
}