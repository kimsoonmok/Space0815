#pragma once
#include <d2d1.h>
#include "CDevice.h"
#include "CSprite.h"

// 장애물을 생성하면 파일이름을 받아서 어떤 비트맵 생성할건지 정한다.
// 젤리 하나 생성하고 충돌체크 완성해보기
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