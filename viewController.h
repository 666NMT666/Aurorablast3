class CViewController{
protected:
	int m_timer;
	CImageDIB* bg;
	bool m_on_key[7];
	bool m_prev_key[7];
	CPadInfo* mPad;
	CSoundEffect *mSE;
	int mNextPage;
public:
	CViewController();
	virtual ~CViewController(){}
	virtual int onTimer(){return 0;}
	void onTimerSuper(){
		m_timer++;
	}
	void checkKey();
	virtual void display();
	virtual void onKeyDownDown(){}
	virtual void onKeyDownUp(){}
	virtual void onKeyDownRight(){}
	virtual void onKeyDownLeft(){}
	virtual void onKeyDownZ(){}
	virtual void onKeyDownX(){}
	virtual void onKeyDownC(){}
	virtual void onKeyUpDown(){}
	virtual void onKeyUpUp(){}
	virtual void onKeyUpRight(){}
	virtual void onKeyUpLeft(){}
	virtual void onKeyUpZ(){}
	virtual void onKeyUpX(){}
	virtual void onKeyUpC(){}
	virtual void onKeyDownEsc(){}
	void (CViewController::*keyDown[7])();
	void (CViewController::*keyUp[7])();
	void showDialog(){
		RECT rc={BATTLE_MIDDLE_X-180,BATTLE_MIDDLE_Y-200,BATTLE_MIDDLE_X+180,BATTLE_MIDDLE_Y+200};
		CShapeBlender::fillRoundRect(bg,rc,20,0x00001188,BLT_MUL);
		CShapeBlender::drawRoundRect(bg,rc,20,0x00AAAAAA);
	}
	void showDialog(int marginY) {
		RECT rc = { BATTLE_MIDDLE_X - 180,BATTLE_TOP + marginY,BATTLE_MIDDLE_X + 180,BATTLE_BOTTOM - marginY };
		CShapeBlender::fillRoundRect(bg, rc, 20, 0x00001188, BLT_MUL);////////////////color
		CShapeBlender::drawRoundRect(bg, rc, 20, 0x00AAAAAA);
	}
	void showDialog(RECT rc) {
		CShapeBlender::fillRoundRect(bg, rc, 20, 0x00001188, BLT_MUL);////////////////color
		CShapeBlender::drawRoundRect(bg, rc, 20, 0x00AAAAAA);
	}
};

void CViewController::checkKey(){
	for(int i=0;i<7;i++){m_prev_key[i]=m_on_key[i];}
	int Pad = GetJoypadInputState( DX_INPUT_PAD1 );
	if(CheckHitKey(KEY_INPUT_UP) || (Pad & PAD_INPUT_UP) )m_on_key[0]=true; else m_on_key[0]=false;
	if(CheckHitKey(KEY_INPUT_DOWN) || (Pad & PAD_INPUT_DOWN))m_on_key[1]=true; else m_on_key[1]=false;
	if(CheckHitKey(KEY_INPUT_LEFT) || (Pad & PAD_INPUT_LEFT))m_on_key[2]=true; else m_on_key[2]=false;
	if(CheckHitKey(KEY_INPUT_RIGHT) || (Pad & PAD_INPUT_RIGHT))m_on_key[3]=true; else m_on_key[3]=false;
	if(CheckHitKey(KEY_INPUT_Z) || (Pad & mPad->GetKeyShot())) m_on_key[4]=true; else m_on_key[4]=false;
	if(CheckHitKey(KEY_INPUT_X) || (Pad & mPad->GetKeyBomb())) m_on_key[5]=true; else m_on_key[5]=false;
	if(CheckHitKey(KEY_INPUT_C) || (Pad & mPad->GetKeyChange())) m_on_key[6]=true; else m_on_key[6]=false;
	if(CheckHitKey(KEY_INPUT_DELETE)) {PostQuitMessage(0);}
	if(CheckHitKey(KEY_INPUT_ESCAPE)  || (Pad & mPad->GetKeyEsc())){
		onKeyDownEsc();
	}
	for(int i=0;i<7;i++){
		if(!m_prev_key[i] && m_on_key[i]){(this->*keyDown[i])();}
		if(m_prev_key[i] && !m_on_key[i]){(this->*keyUp[i])();}
	}
}
CViewController::CViewController():mNextPage(0){
	m_timer=0;
	for(int i=0;i<7;i++){
		m_on_key[i]=false;
		m_prev_key[i]=false;
	}
	mPad=CPadInfo::GetInstance();
	mSE=CSoundEffect::GetInstance();
	bg=CImageDIB::GetInstance();
	bg->Resize(WND_RECT.right,WND_RECT.bottom);
	keyDown[0]=&CViewController::onKeyDownUp;
	keyDown[1]=&CViewController::onKeyDownDown;
	keyDown[2]=&CViewController::onKeyDownLeft;
	keyDown[3]=&CViewController::onKeyDownRight;
	keyDown[4]=&CViewController::onKeyDownZ;
	keyDown[5]=&CViewController::onKeyDownX;
	keyDown[6]=&CViewController::onKeyDownC;
	keyUp[0]=&CViewController::onKeyUpUp;
	keyUp[1]=&CViewController::onKeyUpDown;
	keyUp[2]=&CViewController::onKeyUpLeft;
	keyUp[3]=&CViewController::onKeyUpRight;
	keyUp[4]=&CViewController::onKeyUpZ;
	keyUp[5]=&CViewController::onKeyUpX;
	keyUp[6]=&CViewController::onKeyUpC;
}
void CViewController::display(){
	bg->Display(0,0,0,0,WND_RECT.right,WND_RECT.bottom);
}
