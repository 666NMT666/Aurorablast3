class CLandscapeGasTank1:public CLandscape{
public:
	void UpdateLandscape();
};
void CLandscapeGasTank1::UpdateLandscape(){
	if(m_x0>480)mBltY=m_height;
	RECT rc={(int)m_x-m_width/2,(int)m_y-m_height/2,(int)m_x+m_width/2,(int)m_y+m_height/2};
	if(HitRect(rc)){
		if(m_x0>480) mPlayer->ForcePlayer(-20,0);
		else mPlayer->ForcePlayer(20,0);
	}
	if(mBulletManager->HitTestRect(rc) || mBombManager->HitTestRect(rc)){mLife--;}
}

class CLandscapeGasTank2:public CLandscapeGasTank1{};