class CMBTreeNode{
protected:
	int mCurrentNodes,mMaxNodes;
public:
	CMBTreeNode* mNext;
	CMBTreeNode* mParent;
	CMBTreeNode():mCurrentNodes(0),mMaxNodes(0){}
	virtual ~CMBTreeNode(){
		if(mCurrentNodes>0)delete[] mNext;
	}
	void InitNode(int N){
		mCurrentNodes=0;
		if(N>0){
			mMaxNodes=N;
			mNext=new CMBTreeNode[N];
		}
	}
	void AddNode(CMBTreeNode* node){
		if(mCurrentNodes<mMaxNodes){
			mNext[mCurrentNodes]=*node;
			mNext[mCurrentNodes].mParent=this;
			mCurrentNodes++;
		}
	}
	CMBTreeNode* GetNode(int i){
		return &mNext[i];
	}
	void read(){
		for(int i=0;i<mCurrentNodes;i++){
			mNext[i].read();
		}
	}
};