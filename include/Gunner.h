#pragma once
#include "sys.h"

class CGunner
{
public:
	HBITMAP m_hBmpGunner;
	int x;
	int y;
public:
	CGunner(void);
	~CGunner(void);
public:
	void GunnerInit(HINSTANCE hIns, int x, int y);
	void GunnerMove();
	void GunnerShow(HDC hMemDC);
};

