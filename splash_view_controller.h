class CSplashViewController : public CViewController{
private:
	CImage32 logo;
	CImage32 _testImg;
	void _test();

public:
	CSplashViewController():CViewController(){
		logo.load("dat/img/nmt.bmp");
		//--test--
		_testImg.load("dat/img/landscape/st1-ship42-old.bmp");
	}
	~CSplashViewController(){}
	int onTimer();
};

void CSplashViewController::_test() {
	char str[256];
	/*
	if (m_timer == 1) {
		CCsvUtil csv("dat/dat/effect.csv",5);
		HFONT font = CreateFont(
			20,//フォント高さ
			0,//文字幅（高さと同じ）
			0,//テキストの角度
			0,//ベースラインとｘ軸との角度
			800,//フォントの重さ（太さ）
			false,//イタリック体
			false,//アンダーライン
			false,//打ち消し線
			SHIFTJIS_CHARSET,//文字セット
			OUT_DEFAULT_PRECIS,//出力精度
			CLIP_DEFAULT_PRECIS,//クリッピング精度
			PROOF_QUALITY,//出力品質
			FIXED_PITCH | FF_MODERN,  //ピッチとファミリー
			"ＭＳ Ｐ明朝"//書体名
		);
		//csv.set(0, 2, "1234");
		bg->DisplayText(font,   0,  0, csv.get(10, 0).c_str(), 0xffffff, 0x000000, 0);
		bg->DisplayText(font, 100, 20, csv.get(10, 1).c_str(), 0xffffff, 0x000000, 0);
		bg->DisplayText(font, 200, 40, csv.get(10, 2).c_str(), 0xffffff, 0x000000, 0);
		bg->DisplayText(font, 300, 60, csv.get(10, 3).c_str(), 0xffffff, 0x000000, 0);
		bg->DisplayText(font, 400, 80, csv.get(10, 4).c_str(), 0xffffff, 0x000000, 0);

		//csv.save("test.txt");
		bg->Display(0, 0);
	}
	int colors[100];
	CImageBlenderP3D::getShadow(colors, 100,0);
	RECT rc = { 0,400,960,720 };
	CImageBlenderP3D::BltFloor(bg, &_testImg, rc, 50, 960 / 2 + 200 * sin(N_PI*m_timer * 7), 0, m_timer * 12, colors, 100);
	RECT rc2 = { 0,0,960,720 };
	CImageBlenderP3D::BltRoof(bg, &_testImg, rc2, 50, 960 / 2 + 200 * sin(N_PI*m_timer * 7), 0, m_timer * 12,colors,100);

	TWaveInfo wi = { 200,300,N_PI * m_timer , 0,1.0,0,true };
	CImageBlenderWave::Spread(bg, &_testImg, BLT_MEMCOPY,rc2, wi);
	CBltInfo info(BLT_SKIP2);
	CImageBlender::Blt(bg, &_testImg, &info, rc2, 0, 0);
	
	info.type = BLT_SKIP;
	CImageBlender::Blt(bg, &_testImg, &info, rc2, 300, 0);

	info.type = BLT_KEY;
	CImageBlender::Blt(bg, &_testImg, &info, rc2, 600, 0);
	*/
	//CImageBlenderHoled::Blt(bg, &_testImg, WND_RECT, WND_RECT.right / 2 - _testImg.Width() / 2, WND_RECT.bottom / 2 - _testImg.Height() / 2, _testImg.Width(), _testImg.Height(), 0, 0, 50 + 50 * sin(m_timer*N_PI));
}

int CSplashViewController::onTimer() {
	onTimerSuper();
	CImageBlender::Blt(bg,&logo,WND_RECT.right/2-logo.Width()/2,WND_RECT.bottom/2-logo.Height()/2);
	if (m_timer>200) {//	return ENDING_VIEW_CONTROLLER;
		return TITLE_VIEW_CONTROLLER;
	}
	_test();	
	return 0;
}
