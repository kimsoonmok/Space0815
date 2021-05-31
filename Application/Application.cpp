#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#include "CApp.h"

int CALLBACK WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nCmdShow
)
{
	CApp* app = CApp::GetInstance();

	if (!app->Initialize(hInstance, nCmdShow, _T("WindowClassName"), _T("TitleName"), 1136, 660))
		return 0;

	return app->Run(); // 정상 종료시 0을 반환
}