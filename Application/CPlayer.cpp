#include "CPlayer.h"
#define PLAYER_SIZE	272.0f
#define PLAYER_TSX	300.0f
#define PLAYER_TSY  229.0f
#define PLAYER_TDX  PLAYER_TSX+PLAYER_SIZE
#define PLAYER_TDY  PLAYER_TSY+PLAYER_SIZE

CPlayer::CPlayer()
{
	m_pBitmap = g_device.LoadBitmapFromFile(_T("Cookie Run - Brave Cookie.png"));

	m_rect = {PLAYER_TSX, PLAYER_TSY, PLAYER_TDX,PLAYER_TDY };

	m_state = 0;
	m_aniNum = 0;
	m_gravity = 10;

	m_oneStepStrength = -50;
	m_twoStepStrength = -60;

	float sx, sy;
	for (int i = 0; i < 53; i++)
	{
		sx = PLAYER_SIZE * (i % 11);
		sy = PLAYER_SIZE * (i / 11);

		m_ppSprites[i] = new CSprite(m_pBitmap, { sx + 2, sy + 2,
			sx + PLAYER_SIZE - 2.0f, sy + PLAYER_SIZE - 2.0f });
	}

	m_stateSpriteNumber[RUN][0] = 4;
	m_stateSpriteNumber[RUN][1] = 11;
	m_stateSpriteNumber[RUN][2] = 12;
	m_stateSpriteNumber[RUN][3] = 13;
	m_stateSpriteNumber[RUN][4] = 14;

	m_stateSpriteNumber[JUMP1UP][0] = 1;
	m_stateSpriteNumber[JUMP1UP][1] = 7;
	m_stateSpriteNumber[JUMP1DOWN][0] = 1;
	m_stateSpriteNumber[JUMP1DOWN][1] = 8;
	m_stateSpriteNumber[JUMPGROUNDED][0] = 2;
	m_stateSpriteNumber[JUMPGROUNDED][1] = 6;
	m_stateSpriteNumber[JUMPGROUNDED][2] = 6; // 2������ ���� ���� �����ֱ����ؼ� �ϳ� �� ��������

	m_stateSpriteNumber[JUMP2UP][0] = 2;
	m_stateSpriteNumber[JUMP2UP][1] = 0;
	m_stateSpriteNumber[JUMP2UP][2] = 0;
	
	m_stateSpriteNumber[JUMP2ROLL][0] = 4;
	m_stateSpriteNumber[JUMP2ROLL][1] = 1;
	m_stateSpriteNumber[JUMP2ROLL][2] = 2;
	m_stateSpriteNumber[JUMP2ROLL][3] = 3;
	m_stateSpriteNumber[JUMP2ROLL][4] = 4;

	m_stateSpriteNumber[JUMP2DOWN][0] = 1;
	m_stateSpriteNumber[JUMP2DOWN][1] = 5;

	m_stateSpriteNumber[SLIDING][0] = 2;
	m_stateSpriteNumber[SLIDING][1] = 9;
	m_stateSpriteNumber[SLIDING][2] = 10;
}

CPlayer::~CPlayer()
{
	if (m_ppSprites)
	{
		for (int i = 52; i >= 0; i--)
		{
			if (m_ppSprites[i]) delete m_ppSprites[i];
		}
	}
}

D2D_RECT_F CPlayer::GetRect(void)
{
	return m_rect;
}

void CPlayer::Move(int _distance)
{
	m_rect.top += _distance;
	m_rect.bottom += _distance;
}

void CPlayer::Slide(void)
{
	// Control Key ���Ǹ� Run 
	if (GetAsyncKeyState(VK_CONTROL) & 0x0001)
	{
		m_state = RUN;
		m_aniNum = 0;
	}

	// m_spriteNumber 8,9 �ݺ�
	if (m_aniNum >= m_stateSpriteNumber[SLIDING][0]) m_aniNum = 0;

	m_aniNum++;
}

void CPlayer::Run(void)
{
	if (m_aniNum >= m_stateSpriteNumber[RUN][0]) m_aniNum = 0;

	// KEY Check
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		m_state = JUMP1UP;
		m_aniNum = 0;
	}
	if (GetAsyncKeyState(VK_CONTROL) & 0x8000)
	{
		m_state = SLIDING;
		m_aniNum = 0;
	}

	m_aniNum++;
}

void CPlayer::Jump1Up(void)
{
	// aniNum ����
	if (m_aniNum >= m_stateSpriteNumber[JUMP1UP][0]) m_aniNum = 0;

	// ��ǥ �̵�
	Move(m_oneStepStrength);
	m_oneStepStrength += m_gravity; // �߷�����

	// ���� state�̵�
	if (m_oneStepStrength > 0)
	{
		m_state = JUMP1DOWN;
		m_aniNum = 0;
		m_oneStepStrength = 0;
	}

	// 2�� ���� üũ
	if (GetAsyncKeyState(VK_SPACE) & 0x0001)
	{
		m_oneStepStrength = -50;
		m_state = JUMP2UP;
		m_aniNum = 0;
	}

	m_aniNum++;
}

void CPlayer::Jump1Down(void)
{
	if (m_aniNum >= m_stateSpriteNumber[JUMP1DOWN][0]) m_aniNum = 0;

	Move(m_oneStepStrength);
	m_oneStepStrength += m_gravity;

	// ���� state�̵�
	if (m_rect.top > PLAYER_TSY)
	{
		m_state = JUMPGROUNDED;
		m_aniNum = 0;
		m_oneStepStrength = -50;
		m_rect.top = PLAYER_TSY;
		m_rect.bottom = m_rect.top + PLAYER_SIZE;
	}

	// 2�� ���� üũ
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		m_oneStepStrength = -50;
		m_state = JUMP2UP;
		m_aniNum = 0;
	}

	m_aniNum++;
}

void CPlayer::JumpGrounded(void)
{
	if (m_aniNum >= m_stateSpriteNumber[JUMPGROUNDED][0])
	{
		m_state = RUN; 
		m_aniNum = 0;
	}
	m_aniNum++;
}

void CPlayer::Jump2Up(void)
{
	// aniNum ���� + state �̵�
	if (m_aniNum >= m_stateSpriteNumber[JUMP2UP][0])
	{
		m_aniNum = 0;
		m_state = JUMP2ROLL;
	}

	// ��ǥ �̵� 
	Move(m_twoStepStrength);
	m_twoStepStrength += m_gravity;

	m_aniNum++;
}

void CPlayer::Jump2Roll(void)
{ // ROLL�� �ٲ�鼭 ��ǥ -40 �̵��� ����
	if (m_aniNum >= m_stateSpriteNumber[JUMP2ROLL][0])
	{
		m_aniNum = 0;
		m_state = JUMP2DOWN;
	}

	if (m_stateSpriteNumber[JUMP2ROLL][m_aniNum] == 2)
	{
		m_twoStepStrength = 30;
	}

	Move(m_twoStepStrength);
	m_twoStepStrength += m_gravity;

	m_aniNum++;
}

void CPlayer::Jump2Down(void)
{
	if (m_aniNum >= m_stateSpriteNumber[JUMP2DOWN][0]) m_aniNum = 0;

	Move(m_twoStepStrength);
	m_twoStepStrength += m_gravity;

	if (m_rect.top > PLAYER_TSY)
	{
		m_state = JUMPGROUNDED;
		m_aniNum = 0;
		m_oneStepStrength = -50;
		m_twoStepStrength = -60;
		m_rect.top = PLAYER_TSY;
		m_rect.bottom = m_rect.top + PLAYER_SIZE;
	}
	m_aniNum++;
}

void CPlayer::Update(void)
{
	DWORD gravity = 10;

	switch (m_state)
	{
	case RUN:
		Run();
		break;

	case JUMP1UP: // 1�� JUMP ���
		Jump1Up();
		break;

	case JUMP1DOWN: // 1�� JUMP �ϰ�
		Jump1Down();
		break;

	case JUMPGROUNDED: //Down(����)
		JumpGrounded();
		break;

	case JUMP2UP:
		Jump2Up();
		break;
	
	case JUMP2ROLL:
		Jump2Roll();
		break;
		
	case JUMP2DOWN:
		Jump2Down();
		break;

	case SLIDING: // Slide
		Slide();
		break;
	}
}

void CPlayer::Render(void)
{
	int spriteNumber = m_stateSpriteNumber[m_state][m_aniNum];
	m_ppSprites[spriteNumber]->Render(m_rect);
}