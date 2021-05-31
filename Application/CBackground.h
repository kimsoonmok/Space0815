#pragma once
#include <d2d1.h>
#include "CDevice.h"
#include "CSprite.h"

class CBackground 
{
	enum eBackground {
		ORIGINAL = 0,
		FLOORFIRE
	};
private:
	RECT			m_rect;
	ID2D1Bitmap*	m_pBitmap;
	CSprite*		m_spriteNumber[10];
	DWORD			m_stateSpriteNumber[5][10];
	DWORD			m_state;
	DWORD			m_aniNum;
	FLOAT			m_targetX;
public:
	CBackground(HWND _hWnd);
	~CBackground();
	
	void Update(void);
	void Render(void);
};