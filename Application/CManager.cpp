#include "CManager.h"

CManager::CManager(HWND _hWnd)
{
	m_pFloor = new CFloor(_hWnd);
	m_pPlayer = new CPlayer();
	m_pItems[0] = new CItems();
}

CManager::~CManager()
{
	if (m_pFloor) delete m_pFloor;
	if (m_pPlayer) delete m_pPlayer;
	if (m_pItems[0]) delete m_pItems[0];
}

void CManager::Update(void)
{
	m_pPlayer->Update();
	m_pItems[0]->Update();
	m_pFloor->Update();
	ConflictCheck();
}

void CManager::Render(void)
{
	m_pPlayer->Render();
	m_pItems[0]->Render();
	m_pFloor->Render();
}

void CManager::ConflictCheck(void)
{
	// Player 를 기준으로 Jelly의 위치를 체크
	// Player가 움직일때마다 Jelly의 네 모서리가
	// player 범위 안에있는지 체크
	// player 범위를 spriteSize로 체크할지, sprite 안에있는 쿠키의 크기로할지 고민
	// 쿠키	left 360, right 470, range 110
	//		top 410, bottom 545, range 135

	// item이 player의 x범위(360,470)에 들어왔을때 item의 top, bottom이
	// player의 y범위(410,545) 사이에 있는지 체크함으로써 충돌체크한다.
	
	// player 의 좌표를 얻기위해
	D2D_RECT_F	playerRect = m_pPlayer->GetRect();
	FLOAT		playerLeft = playerRect.left;
	FLOAT		playerTop = playerRect.top;
	FLOAT		playerRight = playerRect.right;
	FLOAT		playerBottom = playerRect.bottom;

	// item 의 좌표를 얻기위해
	D2D_RECT_F	itemRect = m_pItems[0]->GetRect();
	FLOAT		itemLeft = itemRect.left;
	FLOAT		itemTop = itemRect.top;
	FLOAT		itemRight = itemRect.right;
	FLOAT		itemBottom = itemRect.bottom;

	// left가 player의 x범위에 있다면
	if ((itemLeft >= playerLeft) && (itemLeft <= playerRight))
	{
		// item과 y범위가 겹치는곳이 있는지 비교
		if ((itemTop >= playerTop) && (itemLeft <= playerBottom))
		{
			m_pItems[0]->SetState(FALSE); return;
		}
		if ((itemBottom >= playerTop) && (itemBottom <= playerBottom))
		{
			m_pItems[0]->SetState(FALSE); return;
		}
	}

	// right가 player의 y범위에 있다면
	if ((itemRight >= playerLeft) && (itemRight <= playerRight))
	{
		// item과 y범위가 겹치는곳이 있는지 비교
		if ((itemTop >= playerTop) && (itemLeft <= playerBottom))
		{
			m_pItems[0]->SetState(FALSE); return;
		}
		if ((itemBottom >= playerTop) && (itemBottom <= playerBottom))
		{
			m_pItems[0]->SetState(FALSE); return;
		}
	}

	// 처음에 item의 Left로만 충돌체크를 해보려고했는데
	// item의 left가 player의 왼쪽에 와있을때 item의 right를 체크하지않으면 안되서
	// item의 left, right 동시에 player의 y범위가 일치하는지 불필요하게 많이 확인하는것같다.
}
