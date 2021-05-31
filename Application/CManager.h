#pragma once
#include <d2d1.h>
#include "CFloor.h"
#include "CPlayer.h"
#include "CItems.h"

class CManager
{
private:
	CFloor*		m_pFloor;
	CPlayer*	m_pPlayer;
	CItems*		m_pItems[1];
public:
	CManager(HWND _hWnd);
	~CManager();

	void Update(void);
	void Render(void);
	void ConflictCheck(void);
};