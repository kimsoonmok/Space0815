#pragma once
#include <tchar.h>
#include <d2d1.h>
#include <wincodec.h>
#include "CPlayer.h"

// 컴파일 : cpp -> obj 파일로 만드는것
// 전처리기 : #define 같은것을 대칭시켜줌
// 링커 : 헤더파일이 내장되어있는 obj들을 연결시켜서 exe파일을 만듦		  

class CDevice {
private:
	ID2D1Factory*				m_pD2DFactory;
	ID2D1HwndRenderTarget*		m_pRenderTarget;
	IWICImagingFactory*			m_pWICFactory;
public:
	CDevice();
	~CDevice();
	
	ID2D1HwndRenderTarget* GetRenderTarget(void)
	{
		return m_pRenderTarget;
	}

	bool InitDevice(HWND _hWnd);
	void CleanupDevice(void);
	ID2D1Bitmap* LoadBitmapFromFile(PCWSTR _wcFileName);
};

extern CDevice   g_device;