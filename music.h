class CMusic{
	public:
	static int soundHandle;
	CMusic(){}
	~CMusic(){}
	static void Play(){PlaySoundMem( soundHandle , DX_PLAYTYPE_BACK ,true) ;}
	static void Restart(){PlaySoundMem( soundHandle , DX_PLAYTYPE_BACK ,false) ;}
	static void Stop(){StopSoundMem(soundHandle);}
	static void initMusic(char* str){soundHandle=LoadSoundMem(str);}
	static void Change(char* str);
};
int CMusic::soundHandle=0;

void CMusic::Change(char* str){
	Stop();
	soundHandle=LoadSoundMem(str);
}


