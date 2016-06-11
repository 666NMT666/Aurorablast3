class CEffectUtil{
public:
	static void spreadWaterParticles(CEffectManager* efm,int x,int y);
};

void CEffectUtil::spreadWaterParticles(CEffectManager* efm,int x,int y){
	for(int i=0;i<10;i++){
		efm->CreateEffect(x,y,EFFECT_EXPLOSION_40,3+rand()%2,
			-0.001*(rand()%((int)(40*1000))),
			0.001*(rand()%((int)(10*1000)))-7,
			0,1+rand()%2,0,0);
	}
}
