class CVacuumedStar:public CLandscape{
public:
	void UpdateLandscape();
};

void CVacuumedStar::UpdateLandscape(){
	mCounter=500*(mTimer-1);
	mBltInfo.alpha=500-(int)(500*pow(mBltInfo.zoom,0.25));
	mBltInfo.type=BLT_KEYBLACKEN;
	if(mBltInfo.alpha<0)mBltInfo.alpha=0;
	if(mBltInfo.alpha>255)mBltInfo.alpha=255;
	mBltInfo.zoom=ExMath3D::zoomByDistanc(mCounter);
	m_x=BATTLE_MIDDLE_X-(BATTLE_MIDDLE_X-m_x0)*mBltInfo.zoom;
	m_y=BATTLE_MIDDLE_Y-(BATTLE_MIDDLE_Y-m_y0)*mBltInfo.zoom;
	if(mBltInfo.alpha>=245)mDelFlg=true;
	else mDelFlg=false;
}