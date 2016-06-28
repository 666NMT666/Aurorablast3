class CEffectThrash :public CEffect {
public:
	DWORD mColor;
	int mAngle;
	void Update();
	void Create(int x, int y, int w, int h, int angle, DWORD color);
};

void CEffectThrash::Update() {
	CShapeBlender::fillRhombus(m_bg, BATTLE_RECT, (int)m_x, (int)m_y, m_width, m_height, mAngle, mColor);
	mDelFlg = true;
}

void CEffectThrash::Create(int x, int y, int w, int h, int angle, DWORD color) {
	CreateGameObject(x, y, 0, 0, 0.0, 0.0);
	mColor = color;
	mImgId = 0;
	mDelFlg = false;
	m_width = w;
	m_height = h;
	mAngle = angle;
}

class CEffectLine :public CEffect {
public:
	DWORD mColor;
	void Update();
	void Create(int x1, int y1, int x2, int y2, DWORD color);
	void CreateWithAngle(int x1, int y1, int length, int angle, DWORD color);
};

void CEffectLine::Update() {
	CLine::drawLine(m_bg,m_x0,m_y0,m_x,m_y,mColor,BATTLE_RECT);
	mDelFlg = true;
}

void CEffectLine::Create(int x1, int y1, int x2, int y2, DWORD color) {
	CreateGameObject(x1, y1, 0, 0, 0.0, 0.0);
	m_x = x2;
	m_y = y2;
	mColor = color;
	mImgId = 0;
	mDelFlg = false;
}

void CEffectLine::CreateWithAngle(int x1, int y1, int length, int angle, DWORD color) {
	Create(x1, y1, length*cos(N_PI*angle), length*sin(N_PI*angle), color);
}
