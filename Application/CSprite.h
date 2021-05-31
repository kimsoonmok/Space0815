#pragma once
#include <d2d1.h>

class CSprite {
private:
	D2D1_RECT_F		m_rect;
	ID2D1Bitmap*	m_pBitmap;
public:
	CSprite() {}
	CSprite(ID2D1Bitmap* _pBitmap, D2D1_RECT_F _rect);
	~CSprite() {}

	void SetRect(ID2D1Bitmap* _pBitmap, D2D1_RECT_F _rect);
	void SetRect(D2D1_RECT_F _rect);

	void Render(D2D1_RECT_F _targetRect);
};