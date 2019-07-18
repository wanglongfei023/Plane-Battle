#include "PlaneApp.h"
IMPLEMENT(CPlaneApp)
CPlaneApp::CPlaneApp(void)
{
	dc = 0;
	hMemDC = 0;
	hBitmap = 0;
}

CPlaneApp::~CPlaneApp(void)
{
		::DeleteObject(hBitmap);
        ::DeleteDC(hMemDC);
		::ReleaseDC(m_hMainWnd,dc);

		//删除炮弹
		list<CGunner*>::iterator it = m_lstGunner.begin();
		while(it != m_lstGunner.end())
			{
				delete *it;
				it++;
		}
		//删除所有敌人飞机
		list<CFoePlane*>::iterator ite = m_lstFoePlane.begin();
		while(ite != m_lstFoePlane.end())
		   {
				delete *ite;
				ite++;
		}

		list<CFoePlane*>::iterator iter = m_lstBlastFoePlane.begin();
		while(iter != m_lstBlastFoePlane.end())
		   {
				delete *iter;
				iter++;
		}
}

void CPlaneApp::OnCreateGame()   // WM_CREATE
	{

		//0.加载资源
		dc = ::GetDC(m_hMainWnd);//获取窗口DC
		hMemDC = ::CreateCompatibleDC(dc);// 创建一个兼容性DC
		hBitmap = ::CreateCompatibleBitmap(dc,380,550);//创建位图
		::SelectObject(hMemDC,hBitmap); 

		//1.初始化背景
		back.BackInit(m_hIns);

		//2.初始化玩家飞机
		plane.PlayerPlaneInit(m_hIns);

		//3.启动定时器
		::SetTimer(m_hMainWnd,BACK_MOVE_TIME_ID,25,NULL);
		::SetTimer(m_hMainWnd,KEY_STATE_TIME_ID,1,NULL);//监测键盘的状态
		::SetTimer(m_hMainWnd,SEND_GUNNER_TIME_ID,100,NULL);
		::SetTimer(m_hMainWnd,GUNNER_MOVE_TIME_ID,20,NULL);
		::SetTimer(m_hMainWnd,FOEPLANE_MOVE_TIME_ID,30,NULL);
		::SetTimer(m_hMainWnd,FOEPLANE_CREATE_TIME_ID,400,NULL);
         ::SetTimer(m_hMainWnd,CHANGE_SHOWID_TIME_ID,150,NULL);
	}
void CPlaneApp::OnGameDraw()     // WM_PAINT
	{
		
		back.BackShow(hMemDC);
		plane.PlayerPlaneShow(hMemDC);
		this->AllGunnerShow(hMemDC); 
		this->AllFoePlaneShow(hMemDC);
		this->AllBlastFoePlaneShow(hMemDC);
		::BitBlt(dc,0,0,380,550,hMemDC,0,0,SRCCOPY);

}

void CPlaneApp::OnGameRun(WPARAM nTimerID)      // WM_TIMER
{
	if(nTimerID == KEY_STATE_TIME_ID)
	{
		if(::GetAsyncKeyState(VK_LEFT))
		plane.PlayerPlaneMove(VK_LEFT);
		if(::GetAsyncKeyState(VK_RIGHT))
		plane.PlayerPlaneMove(VK_RIGHT);
		if(::GetAsyncKeyState(VK_UP))
		plane.PlayerPlaneMove(VK_UP);		
		if(::GetAsyncKeyState(VK_DOWN))
		plane.PlayerPlaneMove(VK_DOWN);			
	}
	if(nTimerID == BACK_MOVE_TIME_ID)
	{
		back.BackMove();
	}

	if(nTimerID == SEND_GUNNER_TIME_ID)
	{
		plane.SendGunner(m_lstGunner,m_hIns);
	}

	if(nTimerID == GUNNER_MOVE_TIME_ID)
	{
		this->AllGunnerMove();
		this->GunnerHitFoePlane();
	}

	if(nTimerID == FOEPLANE_MOVE_TIME_ID)
	{
		this->AllFoePaneMove();
		if(this->IsGameOver() == true)
		{
	    ::KillTimer(m_hMainWnd,BACK_MOVE_TIME_ID);
		::KillTimer(m_hMainWnd,KEY_STATE_TIME_ID);//监测键盘的状态
		::KillTimer(m_hMainWnd,SEND_GUNNER_TIME_ID);
		::KillTimer(m_hMainWnd,GUNNER_MOVE_TIME_ID);
		::KillTimer(m_hMainWnd,FOEPLANE_MOVE_TIME_ID);
		::KillTimer(m_hMainWnd,FOEPLANE_CREATE_TIME_ID);
        ::KillTimer(m_hMainWnd,CHANGE_SHOWID_TIME_ID);
		MessageBox(NULL,"游戏结束","提示",MB_OK);
		return;
		}
	}

	if(nTimerID == FOEPLANE_CREATE_TIME_ID)
	{
		this->CreateFoePlane();
	}
	if(nTimerID == CHANGE_SHOWID_TIME_ID)
	{
		this->ChangeFoePlaneShowID();
	}
	//重绘
	this->OnGameDraw();
  }

void CPlaneApp::OnKeyDown(WPARAM nKey)
	{
		/*plane.PlayerPlaneMove(nKey);
		this->OnGameDraw();*/
	}


void CPlaneApp::AllGunnerMove()
{
		list<CGunner*>::iterator it = m_lstGunner.begin();
		while(it != m_lstGunner.end())
			{ 
				if((*it)->y < 0)
				{
					delete *it;
					it = m_lstGunner.erase(it);
				}else{
				(*it)->GunnerMove();
				it++;
				}
		}
}

void CPlaneApp::AllGunnerShow(HDC hMemDC)
{
		list<CGunner*>::iterator it = m_lstGunner.begin();
		while(it != m_lstGunner.end())
			{
				(*it)->GunnerShow(hMemDC);
				it++;
		}
}

void CPlaneApp::CreateFoePlane()
{
	CFoePlane* foePlane = NULL;
	 int index = rand()%12;
	 if(index >= 0 && index <= 1)
		 foePlane = new CBigFoePlane;
	 if(index >= 2 && index <= 5)
		 foePlane = new CMidFoePlane;
	 if(index >= 6 && index <= 11)
		 foePlane = new CSmallFoePlane;
	 foePlane->FoePlaneInit(m_hIns);
	 m_lstFoePlane.push_back(foePlane);
}

void CPlaneApp::AllFoePaneMove()
{
		list<CFoePlane*>::iterator ite = m_lstFoePlane.begin();
		while(ite != m_lstFoePlane.end())
		   {
			   if((*ite)->y > 550)
			   {
				   delete (*ite);
				   ite = m_lstFoePlane.erase(ite);
			   }else{
			   (*ite)->FoePlaneMove();
				ite++;
			   }
		}
}

void CPlaneApp::AllFoePlaneShow(HDC hMemDC)
{
		list<CFoePlane*>::iterator ite = m_lstFoePlane.begin();
		while(ite != m_lstFoePlane.end())
		   {
			   (*ite)->FoePlaneShow(hMemDC);
				ite++;
		}
}

void CPlaneApp::GunnerHitFoePlane()
{
	bool bflag = false;    //  标记 是否删除炮弹

	//  遍历所有的炮弹
	list<CGunner*>::iterator iteGunner = m_lstGunner.begin();
	while(iteGunner != m_lstGunner.end())
	{
		//-------------------------------------------------------
		//  遍历所有的敌人飞机
		list<CFoePlane*>::iterator iteFoePlane = m_lstFoePlane.begin();
		while(iteFoePlane != m_lstFoePlane.end())
		{
			//-----------------------------------------------------------
			// 用iteGunner  这个炮弹  和 iteFoePlane 这个敌人飞机比较
			if( (*iteFoePlane)->IsGunnerHitFoePlane(*iteGunner) == true )
			{
				bflag = true;
				//  删除炮弹对象和炮弹节点
				delete (*iteGunner);
				iteGunner = m_lstGunner.erase(iteGunner);
				//  敌人飞掉血
				(*iteFoePlane)->DownBlood();
				//  判断敌人飞机是否爆炸
				if((*iteFoePlane)->IsBoom() == true)
				{
					// 爆炸了 放到另一个链表里  切换爆炸的效果
					m_lstBlastFoePlane.splice(m_lstBlastFoePlane.end(),m_lstFoePlane,iteFoePlane);
				}
				break;
			}
			//-----------------------------------------------------------
			++iteFoePlane;
		}
		//-------------------------------------------------------
		if(bflag == false)
			++iteGunner;
		else
			bflag = false;
	}
}

void CPlaneApp::AllBlastFoePlaneShow(HDC hMemDC)
{
		list<CFoePlane*>::iterator iter = m_lstBlastFoePlane.begin();
		while(iter != m_lstBlastFoePlane.end())
		   {
			   (*iter)->FoePlaneShow(hMemDC);
				iter++;
		}
}
void CPlaneApp::ChangeFoePlaneShowID()
{
	  list<CFoePlane*>::iterator iter = m_lstBlastFoePlane.begin();
		while(iter != m_lstBlastFoePlane.end())
		   {
			   if((*iter)->m_nShowID == 0)
			   {
				   delete (*iter);
				   iter = m_lstBlastFoePlane.erase(iter);
			   }else{
				 (*iter)->m_nShowID--;
				iter++;

			   }
		}
}

bool CPlaneApp::IsGameOver()
{
		list<CFoePlane*>::iterator ite = m_lstFoePlane.begin();
		while(ite != m_lstFoePlane.end())
		   {
			   if((*ite)->IsHitPlayerPlane(plane) == true)
				   return true;
			   ++ite;
		}
		return false;
}
