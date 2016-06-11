class CLandscapeIceNeedle:public CLandscape{
public:
	void UpdateLandscape();
};
void CLandscapeIceNeedle::UpdateLandscape(){
	RECT rc={(int)m_x-m_width/2,(int)m_y-m_height/2,(int)m_x+m_width/2,(int)m_y+m_height/2};
	if(HitRect(rc) && !mPlayer->isInvincible())mPlayer->Killed();
	if(mBulletManager->HitTestRect(rc) || mBombManager->HitTestRect(rc)){mLife--;}
}