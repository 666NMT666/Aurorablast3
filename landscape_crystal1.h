class CLandscapeCrystal1:public CLandscape{
public:
	void UpdateLandscape();
};

void CLandscapeCrystal1::UpdateLandscape(){
	RECT rc={(int)m_x-m_width/2+30,(int)m_y-m_height/2,(int)m_x+m_width/2-30,(int)m_y+m_height/2};
	if(m_x0>BATTLE_MIDDLE_X){
		mBltY=m_height;
		if(HitRect(rc))mPlayer->ForcePlayer(-20,0);
	}else{
		if(HitRect(rc))mPlayer->ForcePlayer(20,0);
	}
}
class CLandscapeCrystal2:public CLandscapeCrystal1{};
class CLandscapeCrystal3:public CLandscapeCrystal1{};

class CLandscapeIce1:public CLandscapeCrystal1{};
class CLandscapeIce2:public CLandscapeCrystal1{};
class CLandscapeIce3:public CLandscapeCrystal1{};