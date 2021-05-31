#pragma once
#include <d2d1.h>
#include "CDevice.h"
#include "CSprite.h"

class CItems
{
private:
	ID2D1Bitmap*	m_pBitmap;
	CSprite*		m_pSpriteNumber; // 60°³

	FLOAT			m_targetX;
	D2D_RECT_F		m_rect;
	BOOL			m_state;
public:
	CItems();
	~CItems();

	D2D_RECT_F	GetRect(void);
	void SetState(BOOL _state);

	void Update();
	void Render();
};