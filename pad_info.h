class CPadInfo{
protected:
	static CPadInfo* instance;
	int bit_key_shot;
	int bit_key_bomb;
	int bit_key_change;
	int bit_key_esc;
	static const char CONFIG_FILE_NAME[16];
public:
	CPadInfo(){
		bit_key_shot=PAD_INPUT_1;
		bit_key_bomb=PAD_INPUT_2;
		bit_key_change=PAD_INPUT_3;
		bit_key_esc=PAD_INPUT_9;
	}
	static CPadInfo* GetInstance(){return instance;}
	const int GetKeyShot(){return bit_key_shot;}
	const int GetKeyBomb(){return bit_key_bomb;}
	const int GetKeyChange(){return bit_key_change;}
	const int GetKeyEsc(){return bit_key_esc;}

	const int GetKeyShotInt();
	const int GetKeyBombInt();
	const int GetKeyChangeInt();
	const int GetKeyEscInt();

	void SetKeyShot(int k){bit_key_shot=k;}
	void SetKeyBomb(int k){bit_key_bomb=k;}
	void SetKeyChange(int k){bit_key_change=k;}
	void SetKeyEsc(int k){bit_key_esc=k;}

	void LoadConfig();
	void SaveConfig();
	void GetKeyConfig(int& shot,int& bomb,int& change,int& esc);
};
CPadInfo* CPadInfo::instance=new CPadInfo();
const char CPadInfo::CONFIG_FILE_NAME[16]="config.txt";

void CPadInfo::GetKeyConfig(int& shot,int& bomb,int& change,int& esc){
	shot=GetKeyShotInt()-3;
	bomb=GetKeyBombInt()-3;
	change=GetKeyChangeInt()-3;
	esc=GetKeyEscInt()-3;
}
void CPadInfo::SaveConfig(){
	csv_fprintf(CONFIG_FILE_NAME,"%d,%d,%d,%d",GetKeyShotInt()-3,GetKeyBombInt()-3,GetKeyChangeInt()-3,GetKeyEscInt()-3);	
}
void CPadInfo::LoadConfig(){
	if(!csv_exist(CONFIG_FILE_NAME))
		csv_fprintf(CONFIG_FILE_NAME,"%d,%d,%d,%d",1,2,3,9);	
	int shot,bomb,change,esc;
	csv_fread_once(CONFIG_FILE_NAME,"%d,%d,%d,%d",&shot,&bomb,&change,&esc);	
	bit_key_shot=1<<(shot+3);
	bit_key_bomb=1<<(bomb+3);
	bit_key_change=1<<(change+3);
	bit_key_esc=1<<(esc+3);
}

const int CPadInfo::GetKeyShotInt(){
	for(int i=4;i<24;i++){
		if((bit_key_shot>>i)==1){ return i; }
	}
	return 4;
}

const int CPadInfo::GetKeyBombInt(){
	for(int i=4;i<24;i++){
		if((bit_key_bomb>>i)==1){ return i; }
	}
	return 5;
}
const int CPadInfo::GetKeyChangeInt(){
	for(int i=4;i<24;i++){
		if((bit_key_change>>i)==1){ return i; }
	}
	return 6;
}
const int CPadInfo::GetKeyEscInt(){
	for(int i=4;i<24;i++){
		if((bit_key_esc>>i)==1){ return i; }
	}
	return 9+3;
}
