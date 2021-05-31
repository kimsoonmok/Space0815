#include "CBackground.h"

CBackground::CBackground(HWND _hWnd)
{
	m_pBitmap = g_device.LoadBitmapFromFile(L"Cookie Run - Background.png"); // �ѱ۷�

	GetClientRect(_hWnd, &m_rect);

	m_state = ORIGINAL;
	m_aniNum = 0;

	m_spriteNumber[0] = new CSprite(m_pBitmap, { 3.0f, 17.0f, 570.0f, 337.0f }); // ���� ���
	m_spriteNumber[1] = new CSprite(m_pBitmap, { 574.0f, 17.0f, 1434.0f, 337.0f }); // �Ҳ� �ٴ�

	m_stateSpriteNumber[ORIGINAL][0] = 1;
	m_stateSpriteNumber[ORIGINAL][1] = 0;

	m_stateSpriteNumber[FLOORFIRE][0] = 1;
	m_stateSpriteNumber[FLOORFIRE][1] = 1;

	m_targetX = 0.0f;
}

CBackground::~CBackground()
{
	if (m_spriteNumber[1]) delete m_spriteNumber[1];
	if (m_spriteNumber[0]) delete m_spriteNumber[0];
}

void CBackground::Update(void)
{
	m_targetX--;
	if (m_targetX <= -(float)m_rect.right) m_targetX = 0; // ���ѷ���
	// m_targetX�� �������� Width��ŭ �������ٴ°� mapSprite�� �� ������ٴ°Ŵϱ� �ڿ������� �ٽ� Render
	//if (m_aniNum >= m_stateSpriteNumber[ORIGINAL][0]) m_aniNum = 0;
	//m_aniNum++;
	m_aniNum = 1;
}

void CBackground::Render(void)
{
	FLOAT tsx1 = m_targetX; // 0����
	FLOAT tdx1 = m_targetX + (FLOAT)(m_rect.right - m_rect.left)  ; // ������Width��ŭ
	FLOAT tsx2 = tdx1; // tdx1 ����
	FLOAT tdx2 = tsx2 + (FLOAT)(m_rect.right - m_rect.left); // ������Width��ŭ

	DWORD spriteNumber = m_stateSpriteNumber[m_state][m_aniNum];
	m_spriteNumber[spriteNumber]->Render({ tsx1,0,tdx1,(float)m_rect.bottom });
	m_spriteNumber[spriteNumber]->Render({ tsx2,0,tdx2,(float)m_rect.bottom });

	spriteNumber = m_stateSpriteNumber[m_state + 1][m_aniNum];
	m_spriteNumber[spriteNumber]->Render({ tsx1,0,tdx1,(float)m_rect.bottom });
	m_spriteNumber[spriteNumber]->Render({ tsx2,0,tdx2,(float)m_rect.bottom });
}
