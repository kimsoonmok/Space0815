#include "CFloor.h"
#define FLOORNUM 20

CFloor::CFloor(HWND _hWnd)
{
	m_pBitmap = g_device.LoadBitmapFromFile(_T("Cookie Run - OvenFloor.png"));
	
	for (int i = 0; i < FLOORNUM; i++)
	{
		m_pSpriteNumber[i] = new CSprite(m_pBitmap, { 0.0f, 0.0f, 124.0f, 120.0f });
	}
	GetClientRect(_hWnd, &m_rect);

	m_targetX = 0.0f;
}

CFloor::~CFloor()
{ 
	//if (m_pSpriteNumber) delete[] m_pSpriteNumber;

	if (m_pSpriteNumber)
	{
		for (int i = FLOORNUM - 1; i >= 0; i--)
		{
			delete m_pSpriteNumber[i];
		}
	}
}

void CFloor::Update(void)
{
	m_targetX -= 20;

	FLOAT hOvenWidth = -(float)m_rect.right + 4.0f; // m_rect.right -> 1120

	if (hOvenWidth >= m_targetX) m_targetX = 0;
}

void CFloor::Render(void)
{
	FLOAT tsy = (FLOAT)m_rect.bottom - 120.0f;
	FLOAT tdy = (FLOAT)m_rect.bottom;

	for (int i = 0; i < FLOORNUM; i++)
	{
		m_pSpriteNumber[i]->Render({124.0f*i + m_targetX, tsy, (124.0f + 124.0f*i) + m_targetX, tdy});
	}
}
