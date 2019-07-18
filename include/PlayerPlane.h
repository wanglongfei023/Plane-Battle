#pragma once
#include "Sys.h"
#include "Gunner.h"
class CPlayerPlane
{
public:
	CPlayerPlane(void);
	~CPlayerPlane(void);
public:
	HBITMAP m_hPlayerPlane;
	int x;
	int y;
public:
	void PlayerPlaneInit(HINSTANCE hIns);
	void PlayerPlaneMove(int FX);
	void PlayerPlaneShow(HDC hMemDC);
	void SendGunner(list<CGunner*>& lstGunner,HINSTANCE hIns);

};

