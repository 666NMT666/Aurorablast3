
class CGameEntity{
protected:
	double m_x,m_y,m_vx,m_vy;
	int m_kind;
	int m_timer;
	bool m_exist;
public:
	CGameEntity(){killed();}
	virtual void process(){}
	virtual void killed(){}
	virtual void created(){}
};

class CBlock:public CGameEntity{

}

class CEffect:public CGameEntity{

}

class CPlayer:public CGameEntity{

}
