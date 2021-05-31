#pragma once
#include "CDevice.h"
#include "CSprite.h"
#include <d2d1.h>
#include <wincodec.h>


class CPlayer {
private:
	enum ePlayer
	{
		RUN ,
		JUMP1,
		JUMP2,
		SLIDING,
		JUMP1UP,
		JUMP1DOWN,
		JUMPGROUNDED,
		JUMP2UP,
		JUMP2ROLL,
		JUMP2DOWN,
	};

	ID2D1Bitmap*	m_pBitmap;
	D2D_RECT_F		m_rect;
	
	CSprite*		m_ppSprites[53];
	DWORD			m_state; 
	DWORD			m_stateSpriteNumber[20][10];
	DWORD			m_aniNum;
	DWORD			m_gravity;

	int				m_oneStepStrength;
	int				m_twoStepStrength;
public:
	CPlayer();
	~CPlayer();

	D2D_RECT_F GetRect(void);

	void Move(int _distance);
	void Slide(void);
	void Run(void);
	void Jump1Up(void);
	void Jump1Down(void);
	void JumpGrounded(void);
	void Jump2Up(void);
	void Jump2Roll(void);
	void Jump2Down(void);
	void Update(void);
	void Render(void);
};