#include "SmallFoePlane.h"

CSmallFoePlane::CSmallFoePlane(void)
{
	m_hBmpFoePlane = 0;    //  位图
	m_nBlood = 1;         //  血量
	m_nShowID = 1;         //  显示的哪一块图片
	x = rand()%(380-34);        //  位置 
	y = -28;
}


CSmallFoePlane::~CSmallFoePlane(void)
{
}

bool CSmallFoePlane::IsHitPlayerPlane(CPlayerPlane& plane)
{
	//  选取玩家飞机的  3个点   和敌人飞机的句型判断
	//  x+30,y
	if(plane.x+30 >= this->x && plane.x+30 <= this->x+34
		&& plane.y >= this->y && plane.y <= this->y+28)
	{
		return true;
	}
	//  x,y+50
	if(plane.x >= this->x && plane.x <= this->x+34
		&& plane.y+50 >= this->y && plane.y+50 <= this->y+28)
	{
		return true;
	}
	//  x+60,y+50
	if(plane.x+60 >= this->x && plane.x+60 <= this->x+34
		&& plane.y+50 >= this->y && plane.y+50 <= this->y+28)
	{
		return true;
	}
	return false;
}
bool CSmallFoePlane::IsGunnerHitFoePlane(CGunner* pGunner)
{
	//  用炮弹的坐标  判断  是否在敌人飞机的矩形框的范围
	if(pGunner->x >= this->x && pGunner->x <= this->x+34 
		&& pGunner->y >= this->y && pGunner->y <= this->y+28 )
	{
		return true;
	}
	return false;
}
void CSmallFoePlane::FoePlaneInit(HINSTANCE hIns)
{
	m_hBmpFoePlane = ::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_SMALL));
}
void CSmallFoePlane::FoePlaneMove()
{
	y+=6;
}
void CSmallFoePlane::FoePlaneShow(HDC hMemDC)
{
	HDC hTempDC = ::CreateCompatibleDC(hMemDC);
	::SelectObject(hTempDC,m_hBmpFoePlane);
	::BitBlt(hMemDC,x,y,34,28,hTempDC,0,(1-m_nShowID)*28,SRCAND);
	::DeleteDC(hTempDC); 
} 