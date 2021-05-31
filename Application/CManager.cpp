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
	// Player �� �������� Jelly�� ��ġ�� üũ
	// Player�� �����϶����� Jelly�� �� �𼭸���
	// player ���� �ȿ��ִ��� üũ
	// player ������ spriteSize�� üũ����, sprite �ȿ��ִ� ��Ű�� ũ������� ���
	// ��Ű	left 360, right 470, range 110
	//		top 410, bottom 545, range 135

	// item�� player�� x����(360,470)�� �������� item�� top, bottom��
	// player�� y����(410,545) ���̿� �ִ��� üũ�����ν� �浹üũ�Ѵ�.
	
	// player �� ��ǥ�� �������
	D2D_RECT_F	playerRect = m_pPlayer->GetRect();
	FLOAT		playerLeft = playerRect.left;
	FLOAT		playerTop = playerRect.top;
	FLOAT		playerRight = playerRect.right;
	FLOAT		playerBottom = playerRect.bottom;

	// item �� ��ǥ�� �������
	D2D_RECT_F	itemRect = m_pItems[0]->GetRect();
	FLOAT		itemLeft = itemRect.left;
	FLOAT		itemTop = itemRect.top;
	FLOAT		itemRight = itemRect.right;
	FLOAT		itemBottom = itemRect.bottom;

	// left�� player�� x������ �ִٸ�
	if ((itemLeft >= playerLeft) && (itemLeft <= playerRight))
	{
		// item�� y������ ��ġ�°��� �ִ��� ��
		if ((itemTop >= playerTop) && (itemLeft <= playerBottom))
		{
			m_pItems[0]->SetState(FALSE); return;
		}
		if ((itemBottom >= playerTop) && (itemBottom <= playerBottom))
		{
			m_pItems[0]->SetState(FALSE); return;
		}
	}

	// right�� player�� y������ �ִٸ�
	if ((itemRight >= playerLeft) && (itemRight <= playerRight))
	{
		// item�� y������ ��ġ�°��� �ִ��� ��
		if ((itemTop >= playerTop) && (itemLeft <= playerBottom))
		{
			m_pItems[0]->SetState(FALSE); return;
		}
		if ((itemBottom >= playerTop) && (itemBottom <= playerBottom))
		{
			m_pItems[0]->SetState(FALSE); return;
		}
	}

	// ó���� item�� Left�θ� �浹üũ�� �غ������ߴµ�
	// item�� left�� player�� ���ʿ� �������� item�� right�� üũ���������� �ȵǼ�
	// item�� left, right ���ÿ� player�� y������ ��ġ�ϴ��� ���ʿ��ϰ� ���� Ȯ���ϴ°Ͱ���.
}
