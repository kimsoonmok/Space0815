#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#include "CApp.h"

// CWnd
// 윈도우 창 두개만들고 화면 두개에 그림 띄워오기

int CALLBACK WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nCmdShow
)
{
	CApp* app = CApp::GetInstance();
	
	if (!app->Initialize(hInstance, nCmdShow))
		return 0;

	return app->Run(); // 정상 종료시 0을 반환
}