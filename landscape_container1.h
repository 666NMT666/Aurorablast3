class CLandscapeContainer1:public CLandscape{
public:
	CLandscapeContainer1():CLandscape(){}
	void UpdateLandscape();
};
void CLandscapeContainer1::UpdateLandscape(){
	RECT rc={(int)m_x-m_width/2,(int)m_y-m_height/2,(int)m_x+m_width/2,(int)m_y+m_height/2};
	if(HitRect(rc)){
		if(m_x0>480) mPlayer->ForcePlayer(-20,0);
		else mPlayer->ForcePlayer(20,0);
	}
	if(mBulletManager->HitTestRect(rc) || mBombManager->HitTestRect(rc)){mLife--;}
}