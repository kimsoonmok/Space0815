#include "CItems.h"

CItems::CItems()
{
	m_pBitmap = g_device.LoadBitmapFromFile(_T("Cookie Run - Jellies.png"));
	// tsx = 3.0f, tsy = 1802.0f
	// tdx = 67.0f, tdy = 1866.0f
	// spriteSize = x:64.0f, y:64.0f
	DWORD spriteSize = 64.0f;

	//for (int i = 0; i < 60; i++)
	//{
	//	m_pSpriteNumber[i] = new CSprite(m_pBitmap, {3.0f, });
	//}
	m_pSpriteNumber = new CSprite(m_pBitmap, { 3.0f, 1802.0f, 67.0f, 1866.0f});
	m_targetX = 0.0f;
	m_rect = { 0 };
	m_state = TRUE;
}

CItems::~CItems()
{
	if (m_pSpriteNumber) delete m_pSpriteNumber;
}

D2D_RECT_F CItems::GetRect(void)
{
	return m_rect;
}

void CItems::SetState(BOOL _state)
{
	m_state = _state;
}

void CItems::Update()
{
	m_targetX -= 20;
}

void CItems::Render()
{
	m_rect = { 800.0f + m_targetX, 400.0f, 864.0f + m_targetX, 464.0f };

	if (m_state)
	{
		m_pSpriteNumber->Render(m_rect);
	}
}
