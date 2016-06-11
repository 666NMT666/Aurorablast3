#include <math.h>
#include <string>
#include <stdlib.h>

class CBigInt{
protected:
	static const int NUM_BLOCKS=20;
	static const int INT_LIMIT=10000;
	int mIntBlocks[NUM_BLOCKS];
public:
	CBigInt(){}
	CBigInt(int p){Init(p);}
	CBigInt(int num[NUM_BLOCKS]){Init(num);}
	CBigInt(char* str){Init(str);}
	~CBigInt(){} 
	///‰‰ŽZŽq‚ÆƒRƒs[ƒRƒ“ƒXƒgƒ‰ƒNƒ^‚É‚Â‚¢‚Ä—pŠwK
	CBigInt(const CBigInt& b){
		memcpy(mIntBlocks,b.mIntBlocks,NUM_BLOCKS*sizeof(int));
	}
	CBigInt& CBigInt::operator=(const CBigInt& b){
		if (this == &b) return *this;
		memcpy(mIntBlocks,b.mIntBlocks,NUM_BLOCKS*sizeof(int));
		return *this;
	}
	void Init(int num);
	void Init(char* str);
	void Init(int num[NUM_BLOCKS]);
	
	const int GetInt(int lank){return mIntBlocks[lank];}
	const int GetMaxBlock();
	const int Cmp(CBigInt* b);

	void Add(int num);
	void Add(CBigInt& bigInt);

	void Minus(int num);
	void Minus(CBigInt& bigInt);

	void Mul(int num);
	void Mul(CBigInt& bigInt);
	void MulSmall(int num);

	void Shift(int num);

	void GetStr(string *str) {
		char tmp[8];
		int maxBlock = GetMaxBlock();
		for (int j = maxBlock; j >= 0; j--) {
			if (j == maxBlock)sprintf_s(tmp, 8, "%d", mIntBlocks[j]);
			else sprintf_s(tmp, 8, "%04d", mIntBlocks[j]);
			*str += tmp;
		}
	}
	void GetStr4S(string *str) {
		char tmp[8];
		static const char keta[18][16] = {
			" –œ "," ‰­ "," ’› ", " ‹ž "," š´ "," ž` "," õ "," a "," ŠÀ "," ³ "," Ú "," ‹É "," P‰Í¹ "," ˆ¢‘m‹_ "," “ß—R‘¼ "," •s‰ÂŽv‹c "," –³—Ê‘å” "
		};
		int maxBlock = GetMaxBlock();
		for (int j = maxBlock; j >= 0; j--) {
			if (j == maxBlock)sprintf_s(tmp, 8, "%d", mIntBlocks[j]);
			else sprintf_s(tmp, 8, "%04d", mIntBlocks[j]);
			
			*str += tmp; 
			if(j!=0)*str += keta[j-1];
			
		}
	}

};

const int CBigInt::GetMaxBlock(){ // index‚ð•Ô‚·‚Ì‚ÅA-1‚Í•s—v
	for(int i=NUM_BLOCKS-1;i>0;i--){
		if(mIntBlocks[i]!=0)return i;
	}
	return 0;
}

const int CBigInt::Cmp(CBigInt* b){
	//return 1(this is large), -1(b is large)
	int maxA=GetMaxBlock();
	int maxB=b->GetMaxBlock();
	if(maxA>maxB)return 1;
	else if(maxA<maxB)return -1;

	for(int i=maxA;i>0;i--){
		if(mIntBlocks[i] > b->GetInt(i))return 1;
		else if(mIntBlocks[i]<b->GetInt(i))return -1;
	}

	return 0;
}
	
void CBigInt::Init(int num){
	if(num<0)num=0;
	for(int i=0;i<NUM_BLOCKS;i++){
		mIntBlocks[i]=num%INT_LIMIT;
		num/=INT_LIMIT;
	}
}

void CBigInt::Init(int num[NUM_BLOCKS]){
	for(int i=0;i<NUM_BLOCKS;i++){
		mIntBlocks[i]=num[i]%INT_LIMIT;
	}
}

void CBigInt::Init(char* str){
	for(int i=0;i<NUM_BLOCKS;i++)mIntBlocks[i]=0;
	int length=strlen(str);
	for(int j=0,i=length-1;i>=0;j++,i-=4){
		int pos=i-3;
		if (pos<0)pos=0;
		for(;pos<=i;pos++)mIntBlocks[j]=mIntBlocks[j]*10+str[pos]-'0';
	}
}

void CBigInt::Add(CBigInt& bigInt){
	int carry=0;
	for(int i=0;i<NUM_BLOCKS;i++){
		mIntBlocks[i]+=bigInt.GetInt(i)+carry;
		if(mIntBlocks[i]>INT_LIMIT){
			carry=1;
			mIntBlocks[i]-=INT_LIMIT;
			if(mIntBlocks[i]>=INT_LIMIT)MessageBox(NULL, TEXT("Stand by Ready!!"), TEXT("Set up"), MB_OK);
		}else{ carry=0; }
	}
}

void CBigInt::Add(int num){
	int i=0;
	int addNext=0;
	while(num>0){
		mIntBlocks[i]+=num%INT_LIMIT+addNext;
		addNext=mIntBlocks[i]/INT_LIMIT;
		mIntBlocks[i]%=INT_LIMIT;
		num/=INT_LIMIT;
		i++;
	}
}

void CBigInt::Minus(CBigInt& bigInt){
	int borrow=0;
	for(int i=0;i<NUM_BLOCKS;i++){
		mIntBlocks[i]-=bigInt.GetInt(i)-borrow;
		if(mIntBlocks[i]<0){
			borrow=1;
			mIntBlocks[i]+=INT_LIMIT;
		}else{ borrow=0; }
	}
	if(borrow>0){
		for(int i=0;i<NUM_BLOCKS;i++)mIntBlocks[i]=0;
	}
}

void CBigInt::Minus(int num){
	int i=0;
	int borrow=0;
	while(num>0){
		mIntBlocks[i]-=num%INT_LIMIT-borrow;
		if(mIntBlocks[i]<0){
			borrow=1;
			mIntBlocks[i]=INT_LIMIT+mIntBlocks[i];
		}
		num/=INT_LIMIT;
		i++;
	}
	if(borrow>0){
		for(int i=0;i<NUM_BLOCKS;i++)mIntBlocks[i]=0;
	}
}


void CBigInt::Mul(int num){
	CBigInt bigInt(num);
	Mul(bigInt);
}

void CBigInt::Mul(CBigInt& bigInt){
	CBigInt ans(0);
	for(int i=0;i<NUM_BLOCKS;i++){
		int carry=0;
		CBigInt tmp(mIntBlocks);
		tmp.MulSmall(bigInt.GetInt(i));
		tmp.Shift(i);
		ans.Add(tmp);
	}
	for (int i = 0; i < NUM_BLOCKS; i++) {
		mIntBlocks[i] = ans.GetInt(i);
	}
}

void CBigInt::MulSmall(int num){
	if(num<0){return;}
	if(num>INT_LIMIT)num%=INT_LIMIT;
	int carry=0;
	for(int i=0;i<NUM_BLOCKS;i++){
		mIntBlocks[i]=mIntBlocks[i]*(num%INT_LIMIT)+carry;
		carry=mIntBlocks[i]/INT_LIMIT;
		mIntBlocks[i]%=INT_LIMIT;
	}	
}

void CBigInt::Shift(int num){
	for(int j=0;j<num;j++){ 
		for(int i=NUM_BLOCKS-1;i>0;i--){
			mIntBlocks[i]=mIntBlocks[i-1];
		}
		mIntBlocks[0]=0;
	}
}


/*
   10000**17
=  10 **64
=  17 shift
=  100 ** 32
=  1000 ** 27
*/

