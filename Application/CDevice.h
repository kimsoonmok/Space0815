#pragma once
#include <tchar.h>
#include <d2d1.h>
#include <wincodec.h>
#include "CPlayer.h"

// ������ : cpp -> obj ���Ϸ� ����°�
// ��ó���� : #define �������� ��Ī������
// ��Ŀ : ��������� ����Ǿ��ִ� obj���� ������Ѽ� exe������ ����		  

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