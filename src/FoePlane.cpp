#include "FoePlane.h"


CFoePlane::CFoePlane(void)
{
	m_hBmpFoePlane = 0;   //  位图
	m_nBlood = 0;    //  血量
	m_nShowID = 0;     //  显示的哪一块图片
	x = 0;        //  位置 
	y = 0;
}


CFoePlane::~CFoePlane(void)
{
	::DeleteObject(m_hBmpFoePlane);
	 m_hBmpFoePlane = 0;
}
