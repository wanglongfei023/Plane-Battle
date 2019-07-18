#include "PlayerPlane.h"


CPlayerPlane::CPlayerPlane(void)
{
  m_hPlayerPlane = 0;
  x = 160;
  y = 490;
}


CPlayerPlane::~CPlayerPlane(void)
{
	::DeleteObject(m_hPlayerPlane);
	m_hPlayerPlane = 0;
}
void CPlayerPlane::PlayerPlaneInit(HINSTANCE hIns){
	m_hPlayerPlane = ::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_PLAYER));
}
void CPlayerPlane::PlayerPlaneMove(int FX)
	{
		if(FX == VK_LEFT)
		{
			if(x > 0)
			x -= 4;
		}

		if(FX == VK_RIGHT)
		{
			if(x < 320)
			x += 4;
		}

    	if(FX == VK_UP)
		{
			if(y > 0)
			y -= 4;
		}

    	if(FX == VK_DOWN)
		{
			if(y < 490)
			y += 4;
		}
	}
void CPlayerPlane::PlayerPlaneShow(HDC hMemDC)
{
	HDC hTempDC = ::CreateCompatibleDC(hMemDC);
	::SelectObject(hTempDC,m_hPlayerPlane);
	::BitBlt(hMemDC,x,y,60,60,hTempDC,0,0,SRCAND);
	DeleteDC(hTempDC);
}
void CPlayerPlane::SendGunner(list<CGunner*>& lstGunner,HINSTANCE hIns)
{
	CGunner* pGunner = new CGunner;
	pGunner->GunnerInit(hIns,this->x+27,this->y-9);
	lstGunner.push_back(pGunner);

}