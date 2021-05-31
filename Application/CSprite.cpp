#include "CSprite.h"
#include "CDevice.h"

CSprite::CSprite(ID2D1Bitmap* _pBitmap, D2D1_RECT_F _rect)
{
	SetRect(_pBitmap, _rect);
}

void CSprite::SetRect(ID2D1Bitmap* _pBitmap, D2D1_RECT_F _rect) {
	m_pBitmap = _pBitmap;
	m_rect = _rect;
}

void CSprite::SetRect(D2D1_RECT_F _rect)
{
	m_rect = _rect;
}


void CSprite::Render(D2D1_RECT_F _targetRect)
{
	g_device.GetRenderTarget()->DrawBitmap(m_pBitmap, _targetRect,
		1.0f,
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		m_rect);
}
