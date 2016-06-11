class CLandscapeNull1:public CLandscape{
public:
	void UpdateLandscape(){
		mAutoDelFlg=false;
		if(m_y-m_height/2>BATTLE_BOTTOM)mDelFlg=true;
	}
};

class CLandscapeBlock1:public CLandscape{
public:
	void UpdateLandscape();
};
void CLandscapeBlock1::UpdateLandscape(){
	RECT rc={(int)m_x-m_width/2,(int)m_y-m_height/2,(int)m_x+m_width/2,(int)m_y+m_height/2};	
	bool roofFlg=(mImgSubId==0)?false:true;
	if(HitRect(rc)){
		bool movedFlg = false;
		int ppx = mPlayer->GetPrevX();
		int ppy = mPlayer->GetPrevY();
		if (mPrevX + m_width / 2 < ppx) {/////       | |  ppx
			int f = abs((int)(m_x - (mPlayer->GetX() + m_width / 2)));
			mPlayer->ForcePlayer(20, 0);
			movedFlg = true;
		}
		if (ppx < mPrevX - m_width / 2) {/////    ppx   | |
			int f = abs((int)(m_x - (mPlayer->GetX() - m_width / 2)));
			mPlayer->ForcePlayer(-20, 0);
			movedFlg = true;
		}
		if (mPrevY + m_height / 2 < ppy) {/////       | |  ppy
			int f = abs((int)(m_y - (mPlayer->GetY() + m_height / 2)));
			mPlayer->ForcePlayer(0, f);
			movedFlg = true;
		}
		if (ppy < mPrevY - m_height / 2) {/////    ppy   | |
			int f = abs((int)(m_y - (mPlayer->GetY() - m_height / 2)));
			mPlayer->ForcePlayer(0,-f);
			movedFlg = true;
		}
		if (movedFlg == false) {
			double fx = (mPlayer->GetX() < BATTLE_MIDDLE_X) ? 30 : -30;
			double fy = (mPlayer->GetY() < BATTLE_MIDDLE_Y) ? 30 : -30;
			mPlayer->ForcePlayer(fx,fy);
		}
	}
}