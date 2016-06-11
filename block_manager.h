#ifndef BLOCK_MANAGER_H
#define BLOCK_MANAGER_H
class CBlockManager:public CObjectManager{
	static const int BLOCKS_LEFT =12;
	static const int FRAME_BOTTOM=480-11;
	static const int BLOCK_WIDTH=28;
	static const int BLOCK_KINDS=5;
	static const int COLS=9;
	static const int LOWS=17;
	int mCreateInterval;
	int mTimer;
	double mBlockSpeed; 

	CImage32* mImages;
	std::vector<CBlock*> mBlockList[10];
	int mBlockMatrix[9][LOWS];
	bool mDestructionFlg[9][LOWS];
	bool mColDestructionFlg[COLS];
	bool mLowDestructionFlg[LOWS];
public:
	CBlockManager();
	void Create(){}
	void Update();
	void FallBlocks();
	void SeekHorizontal();
	void SeekVertical();
	void CreateMatrix();
	void SeekMatrix();
	void RevolveUp(int i);
	void RevolveDown(int i);
	void RevolveLeft(int i);
	void RevolveRight(int i);

	void delFromList(int col,int low);
	void insertIntoList(int col,int low,CBlock* block);

	void debugCommand(){
		if(mCreateInterval==2)mCreateInterval=20;
		else mCreateInterval=2;
	}
};

CBlockManager::CBlockManager():CObjectManager(){
	mCreateInterval=4;
	mTimer=0;
	mImages=new CImage32();
	CImageFactory::InitBitmap(mImages,"img/blocks.bmp");
	mBlockSpeed=40.0;
	for(int i=0;i<COLS;i++)mColDestructionFlg[i]=false;
	for(int i=0;i<LOWS;i++)mLowDestructionFlg[i]=false;
}
void CBlockManager::Update(){
	return;
	mTimer++;
	if(mTimer>=mCreateInterval){
		mTimer=0;
		CBlock* blk=new CBlock();

		int kind=rand()%BLOCK_KINDS+1;
		int col=rand()%COLS;
		int fillCounter=0;
		while(mBlockList[col].size()>=LOWS){
			col=(col+1)%COLS;
			fillCounter++;
			if(fillCounter>=COLS)return;
		}
		int exArray[3]={0,0,0};
		if(!mBlockList[col].empty()){
			CBlock* back=mBlockList[col].back();
			exArray[0]=back->GetKind();
		}
		if(col-1>=0 && mBlockList[col-1].size()>mBlockList[col].size()){
			CBlock* left=mBlockList[col-1].at(mBlockList[col].size());
			exArray[1]=left->GetKind();
		}
		if(col+1<COLS && mBlockList[col+1].size()>mBlockList[col].size()){
			CBlock* right=mBlockList[col+1].at(mBlockList[col].size());
			exArray[2]=right->GetKind();
		}

		int sz=0;
		int excludedArray[5]={0,0,0,0,0};
		for(int i=0;i<5;i++){
			int hitCounter=0;
			for(int j=0;j<3;j++){
				if(i+1==exArray[j]){
					hitCounter++;
					continue;
				}
			}
			if(hitCounter==0){
				excludedArray[sz]=i+1;
				sz++;
			}
		}
		kind=excludedArray[rand()%sz];

		blk->Create(BLOCKS_LEFT+BLOCK_WIDTH*col,0,kind,0,mBlockSpeed);
		mBlockList[col].push_back(blk);
	}	
	CreateMatrix();
	for(int i=0;i<COLS;i++){
		std::vector<CBlock*>::iterator it = mBlockList[i].begin();
		int top=FRAME_BOTTOM;
		int j=0;
		while(it!=mBlockList[i].end()){
			CBlock* block = *it;
			CBltInfo info(BLT_KEY);
			m_bg->Blt(&info,BATTLE_RECT,block->GetX(),block->GetY(),mImages,block->GetBltX(),block->GetBltY(),block->GetWidth(),block->GetHeight());
			block->SetTop(top);
			block->Update();
			int tmpTop = block->GetY();
			if(tmpTop<top)top=tmpTop;
			if(j<LOWS && block->isStable())mBlockMatrix[i][j]=block->GetKind();
			it++;
			j++;
		}
	}

	for(int i=0;i<COLS;i++){
		int hitCounter=0;
		int prevColor=0;
		for(int j=0;j<LOWS;j++){
			if(mBlockMatrix[i][j]!=0 && mBlockMatrix[i][j]==prevColor)hitCounter++;
			else hitCounter=0;
			prevColor=mBlockMatrix[i][j];
			if(hitCounter>=3){
				mDestructionFlg[i][j]=true;
				mDestructionFlg[i][j-1]=true;
				mDestructionFlg[i][j-2]=true;
				mDestructionFlg[i][j-3]=true;
				//mColDestructionFlg[i]=true;
				mLowDestructionFlg[j]=true;
				mLowDestructionFlg[j-1]=true;
				mLowDestructionFlg[j-2]=true;
				mLowDestructionFlg[j-3]=true;
			}
		}
	}

	for(int j=0;j<LOWS;j++){
		int hitCounter=0;
		int prevColor=0;
		for(int i=0;i<COLS;i++){
			if(mBlockMatrix[i][j]!=0 && mBlockMatrix[i][j]==prevColor)hitCounter++;
			else hitCounter=0;
			prevColor=mBlockMatrix[i][j];
			if(hitCounter>=3){
				mDestructionFlg[i][j]=true;
				mDestructionFlg[i-1][j]=true;
				mDestructionFlg[i-2][j]=true;
				mDestructionFlg[i-3][j]=true;
				mColDestructionFlg[i]=true;
				mColDestructionFlg[i-1]=true;
				mColDestructionFlg[i-2]=true;
				mColDestructionFlg[i-3]=true;
				//mLowDestructionFlg[j]=true;
			}
		}
	}
	for(int i=0;i<COLS;i++){
		if(mColDestructionFlg[i]){
			std::vector<CBlock*>::iterator it = mBlockList[i].begin();
			int j=0;
			while(it!=mBlockList[i].end()){
				if(mDestructionFlg[i][j])(*it)->Destroied();
				delete *it;
				it=mBlockList[i].erase(it);
				j++;
			}
		}
	}
	for(int i=0;i<COLS;i++){
		std::vector<CBlock*>::iterator it = mBlockList[i].begin();
		int j=0;
		while(it!=mBlockList[i].end()){
			if(mLowDestructionFlg[j]){	
				if(mDestructionFlg[i][j])(*it)->Destroied();
				delete *it;
				it=mBlockList[i].erase(it);
			}else{it++;}
			j++;
		}
	}
	for(int i=0;i<COLS;i++)mColDestructionFlg[i]=false;
	for(int i=0;i<LOWS;i++)mLowDestructionFlg[i]=false;
}

void CBlockManager::CreateMatrix(){
	for(int i=0;i<COLS;i++){
		for(int j=0;j<LOWS;j++){
			mBlockMatrix[i][j]=0;
			mDestructionFlg[i][j]=false;
		}
	}
}

void CBlockManager::delFromList(int col,int low){
	std::vector<CBlock*>::iterator it = mBlockList[col].begin()+low;
	delete *it;
	mBlockList[col].erase(it);
}
void CBlockManager::insertIntoList(int col,int low,CBlock* block){
	int insertLow=low;
	if(mBlockList[col].empty())insertLow=0;
	else if(insertLow>mBlockList[col].size())insertLow=mBlockList[col].size();		
	block->SetPos(BLOCKS_LEFT+BLOCK_WIDTH*col,block->GetY());
	std::vector<CBlock*>::iterator it = mBlockList[col].begin()+insertLow;
	mBlockList[col].insert(it,block);
}

void CBlockManager::RevolveUp(int i){
	if(mBlockList[i].size()>1){
		CBlock *block=mBlockList[i].back();
		if(block->isStable()){
			rotate( mBlockList[i].begin(), mBlockList[i].begin() + 1, mBlockList[i].end() );
		}else{
			rotate( mBlockList[i].begin(), mBlockList[i].begin() + 1, mBlockList[i].end()-1 );
		}
		
	}
}
void CBlockManager::RevolveDown(int i){
	if(mBlockList[i].size()<=1)return;

	CBlock *block=mBlockList[i].back();
	int fallingBlock=(block->isStable())?0:1;
	std::vector<CBlock*>::iterator back = mBlockList[i].begin()+mBlockList[i].size()-1-fallingBlock;
	(*back)->SetPos((*back)->GetX(),470);
	rotate( mBlockList[i].begin(), back, mBlockList[i].end()-fallingBlock);
	/*for(std::vector<CBlock*>::iterator it = mBlockList[i].begin();it!=mBlockList[i].end();it++){
		(*it)->SetPos((*back)->GetX(),(*back)->GetY()+BLOCK_WIDTH);
	}*/
}

void CBlockManager::RevolveLeft(int low){
	CBlock *left=NULL;
	for(int i=-1;i<COLS;i++){
		if(mBlockList[i+1].empty())continue;
		CBlock* tmp= new CBlock();
		CBlock* top= mBlockList[i+1].back();
		if(mBlockList[i+1].size()>low+1 || (mBlockList[i+1].size()==low+1 && top->isStable())){
			if(i!=-1){
				*tmp=*mBlockList[i+1].at(low);
				delFromList(i+1,low);
				insertIntoList(i,low,tmp);
			} else {
				left=new CBlock();
				*left=*mBlockList[0].at(low);
				delFromList(0,low);
			}
		}
	}
	if(left!=NULL){ insertIntoList(COLS-1,low,left); }
}
void CBlockManager::RevolveRight(int low){
	CBlock *right=NULL;
	for(int i=COLS;i>0;i--){
		if(mBlockList[i-1].empty())continue;
		CBlock* tmp= new CBlock();
		CBlock* top= mBlockList[i-1].back();
		if(mBlockList[i-1].size()>low+1 || (mBlockList[i-1].size()==low+1 && top->isStable())){
			if(i!=COLS){
				*tmp=*mBlockList[i-1].at(low);
				delFromList(i-1,low);
				insertIntoList(i,low,tmp);
			}else {
				right=new CBlock();
				*right=*mBlockList[COLS-1].at(low);
				delFromList(COLS-1,low);
			}
		}
	}
	if(right!=NULL){ insertIntoList(0,low,right); }
}

void CBlockManager::SeekHorizontal(){}
void CBlockManager::SeekVertical(){}

#endif