#include "CFrameRate.h"

CFrameRate::CFrameRate(DWORD _frameTick)
{
	m_frameTick = _frameTick;
	m_prevTick = 0;
	m_sumTick = 0;
	m_deltaTick = 0;
	m_addTick = 0;
	m_fps = 0;
	m_fpsCount = 0;
}

DWORD CFrameRate::GetFps(void)
{
	return m_fps;
}

bool CFrameRate::IsFrame(void)
{
	DWORD nowTick = GetTickCount();

	//  p      n
	//  |------|-----|------|-----|------|-----|------|-----|
	//	   30     32    31     33    30     32    31     33
	if (m_prevTick == 0) m_prevTick = nowTick;

	m_deltaTick = nowTick - m_prevTick;
	m_prevTick = nowTick;
	m_sumTick += m_deltaTick;

	if (m_sumTick > m_frameTick + m_addTick)
	{ 
		m_addTick += m_frameTick;
		m_fpsCount++;
		if (m_sumTick >= 1000)
		{
			m_fps = m_fpsCount;
			m_sumTick = 0;
			m_fpsCount = 0;
			m_addTick = 0;
		}
		return true;
	}
	return false;
}

void CFrameRate::Render(HWND _hWnd)
{
	HDC hdc = GetDC(_hWnd);
	TCHAR buf[100];

	_stprintf_s(buf, 100, _T("FPS : %d"), m_fps);
	TextOut(hdc, 0, 0, buf, _tcslen(buf));

	ReleaseDC(_hWnd, hdc);
}
