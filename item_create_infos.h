
class CCreateInfoFactory{
public:
	static CCreateInfo GetItemBltInfo();
	static CCreateInfo GetEffectBltInfo(int motion,int subId,int interval,int end,int delta);
};

CCreateInfo CCreateInfoFactory::GetItemBltInfo(){
	int p[5]={0,0,2,0,0};
	CBltInfo bi(BLT_KEY);
	CCreateInfo info(p,bi);
	return info;
}

CCreateInfo CCreateInfoFactory::GetEffectBltInfo(int motion,int subId,int interval,int end,int delta){
	int p[5]={motion,subId,interval,end,delta};
	CCreateInfo info(p);
	return info;
}

