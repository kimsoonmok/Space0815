#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#include "CApp.h"

// CWnd
// ������ â �ΰ������ ȭ�� �ΰ��� �׸� �������

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

	return app->Run(); // ���� ����� 0�� ��ȯ
}