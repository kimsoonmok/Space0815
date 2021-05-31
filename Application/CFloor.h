#pragma once
#include <d2d1.h>
#include "CDevice.h"
#include "CSprite.h"

// ��ֹ��� �����ϸ� �����̸��� �޾Ƽ� � ��Ʈ�� �����Ұ��� ���Ѵ�.
// ���� �ϳ� �����ϰ� �浹üũ �ϼ��غ���
class CFloor {
private:
	ID2D1Bitmap*	m_pBitmap;
	CSprite*		m_pSpriteNumber[20];
	RECT			m_rect;
	FLOAT			m_targetX;
public:
	CFloor(HWND _hWnd);
	~CFloor();

	void Update(void);
	void Render(void);
};