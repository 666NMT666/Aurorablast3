class CPassingStar1:public CLandscape{
public:
	void UpdateLandscape();
};
void CPassingStar1::UpdateLandscape(){
	if(mBltInfo.zoom==1.0)mBltInfo.zoom=(double)(0.999-0.01*(rand()%50));
}

class CPassingStar2:public CLandscape{
public:
	void UpdateLandscape();
};
void CPassingStar2::UpdateLandscape(){
	if(mBltInfo.zoom==1.0)mBltInfo.zoom=(double)(0.999-0.01*(rand()%80));
}