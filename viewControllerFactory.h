#ifndef _VIEW_CONTROLLER_FACTORY_H
#define _VIEW_CONTROLLER_FACTORY_H

class CViewControllerFactory{
	CViewController* vc;
public:
	//static CViewController nextViewController(){}
	CViewControllerFactory(){
		vc=new CSplashViewController();	
	}
	void onTimer();
};
void CViewControllerFactory::onTimer(){
	int ret=vc->onTimer();
	vc->checkKey();
	vc->display();
	if(ret!=0){delete vc;}
	if(ret==TITLE_VIEW_CONTROLLER){
		vc=new CTitleViewController();
	}else if(ret==ENDURANCE_VIEW_CONTROLLER){
		vc=new CEnduranceViewController();
	}else if(ret==CONFIG_VIEW_CONTROLLER){
		vc=new CConfigViewController();
	}else if(ret==ENDING_VIEW_CONTROLLER){
		vc=new CEndingViewController();
	}else if(ret==SELECT_VIEW_CONTROLLER){
		vc=new CSelectViewController();
	}else if(ret==REPLAY_VIEW_CONTROLLER){
		vc=new CReplayViewController();
	}else if(ret==NAME_ENTRY_VIEW_CONTROLLER){
		vc=new CNameEntryViewController();
	}
}
#endif