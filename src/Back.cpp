#include "Back.h"


CBack::CBack(void)
{
	m_hBmpBackDown = 0;   //  背景图片
	m_hBmpBackUp = 0;
	x = 0;
	y = 0;
}


CBack::~CBack(void)
{
	::DeleteObject(m_hBmpBackDown);   // 删除图片
	::DeleteObject(m_hBmpBackUp);
	m_hBmpBackDown = 0;   //  背景图片
	m_hBmpBackUp = 0;
}
void CBack::BackInit(HINSTANCE hIns)
{
	//  加载位图
	m_hBmpBackUp = ::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_BACK));
	m_hBmpBackDown = ::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_BACK)); 
}
void CBack::BackMove()
{
	if(y == 550)
		y = 0;
	else
		y++;
}
void CBack::BackShow(HDC hMemDC)
{
	//  创建一个兼容性DC
	HDC hTempDC = ::CreateCompatibleDC(hMemDC);
	//  选入一张位图
	::SelectObject(hTempDC,m_hBmpBackUp);
	//  拷贝位图
	::BitBlt(hMemDC,x,y-550,380,550,hTempDC,0,0,SRCCOPY);
	//  选入一张位图
	::SelectObject(hTempDC,m_hBmpBackDown);
	//  拷贝位图
	::BitBlt(hMemDC,x,y,380,550,hTempDC,0,0,SRCCOPY);
	//  删除DC
	::DeleteDC(hTempDC);
}