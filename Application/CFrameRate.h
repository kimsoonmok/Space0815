#pragma once
#include <Windows.h>
#include <tchar.h>

class CFrameRate {
private:
	DWORD		m_frameTick;
	DWORD		m_prevTick;
	DWORD		m_sumTick;
	DWORD		m_deltaTick;
	DWORD		m_addTick;
	DWORD		m_fps;
	DWORD		m_fpsCount;
public:
	//CLFrameRate() {};
	CFrameRate(DWORD _frameTick);
	~CFrameRate() {};

	DWORD GetFps(void);

	bool IsFrame(void);
	void Render(HWND _hWnd);
};