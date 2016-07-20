#pragma once
#include <Windows.h>
#include <string>
#include "img32.h"
#include "image_blender.h"

using namespace std;

typedef struct _TChatScene {
	string str[4];
	int anm_in;
	int anm_out;
	int img_id;
} TChatScene;


class CChat {
private:
	CImage32 mImgBord;
	CImage32 mImgCharactor[4];
	string mChatStr[7][4];
	TChatScene mScene[7];
	static const int MGN_BOTTOM=40;
	
public:
	void showChat(CImage32* bg, int stage, int num) {
		int x=(BATTLE_LEFT+BATTLE_RIGHT)/2 - mImgBord->Width()/2;
		int y = BATTLE_BOTTOM-MGN_BOTTOM-mImgBord->Height();
		CImageBlender::Blt(bg, &mImgBord, x, y);
	}
    
	CChat() {
		mImgBord.load("dat/img/chat/bord.bmp");
		mImgCharactor[0].load("dat/img/dummy.bmp");
		mImgCharactor[1].load("dat/img/dummy.bmp");
		mImgCharactor[2].load("dat/img/dummy.bmp");
		mImgCharactor[3].load("dat/img/dummy.bmp");
		
		
		
		
		mChatStr[0][0] = "奴等め、よくも我々の地球を……\n許さんぞ侵略者ども。";
		mChatStr[0][1] = "一人残らず八つ裂きにしてやる！！";
		mChatStr[0][2] = "";
		mChatStr[0][3] = "";
		mChatStr[1][0] = "まさか、あれだけのミサイルを受けて\n生存者がいるとはな。";
		mChatStr[1][1] = "姉様達に報告するか……\nいやその前に貴様を殺す！！";
		mChatStr[1][2] = "";
		mChatStr[1][3] = "";
		mChatStr[2][0] = "貴様か。過去2回の人類滅亡危機を救った亡霊。";
		mChatStr[2][1] = "まあ良い。\n貴様を殺し、今度こそすべての生命を根絶やしにする。";
		mChatStr[2][2] = "小汚く青い生命の星、地球。\nその全てを！我々は許さない！！";
		mChatStr[2][3] = "";
		mChatStr[3][0] = "";
		mChatStr[3][1] = "";
		mChatStr[3][2] = "";
		mChatStr[3][3] = "";
		mChatStr[4][0] = "";
		mChatStr[4][1] = "";
		mChatStr[4][2] = "";
		mChatStr[4][3] = "";
		mChatStr[5][0] = "ああああ50";
		mChatStr[5][1] = "ああああ51";
		mChatStr[5][2] = "ああああ52";
		mChatStr[5][3] = "ああああ53";
		mChatStr[6][0] = "ああああ60";
		mChatStr[6][1] = "まだ終わりではない。";
		mChatStr[6][2] = "";
		mChatStr[6][3] = "";
	}
};


