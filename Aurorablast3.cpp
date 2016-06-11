#include "DxLib.h"
#include <mmsystem.h>
#include <list>
#pragma comment (lib, "winmm.lib")

int testa=0;
int test_fo=0;

void NLog(char* log){
	errno_t error;
	FILE *fout;
	error=fopen_s(&fout,"logPh.txt","w+");
	fprintf(fout,log);
	fclose(fout);
}
#include "csv_util.h"
#include "util_method.h"
#include "string_util.h"
#include "ex_math.h"
#include "ex_math_3d.h"
#include "ex_rect.h"
#include "music.h"
#include "sound_effect.h"

#include "img32.h"
#include "imgdib.h"
#include "image_blender.h"
#include "image_filter.h"
#include "image_blender_wave.h"
#include "image_blender_stretch.h"
#include "image_blender_texmap.h"
#include "image_blender_p3d.h"
#include "image_blender_holed.h"
#include "image_factory.h"
#include "image_number.h"
#include "shaped_image.h"

#include "hit_test.h"
#include "color_mixer.h"
#include "shape.h"
#include "line.h"
#include "line_gradation.h"
#include "line_fade.h"
#include "triangle.h"
#include "eclipsed_circle.h"
#include "eclipsed_elipse.h"
#include "view.h"
#include "gage_view.h"
#include "text_view.h"
#include "count_view.h"

#include <vector>
static const CBltInfo BLT_INFO_KEY(BLT_KEY);
static const CBltInfo BLT_INFO_ADD(BLT_ADD);
#include "game_info.h"
#include "score.h"
#include "game_object.h"
#include "object_manager.h"
#include "game_object.h"

#include "item_create_infos.h"

#include "effect.h"
#include "effect_eclipsed_circle.h"
#include "effect_eclipsed_elipse.h"
#include "effect_thrash.h"
#include "effect_manager.h"
#include "effect_util.h"
#include "debris.h"
#include "debris_manager.h"

#include "bullet.h"
#include "bullet_manager.h"
#include "bomb.h"
#include "bomb_manager.h"
#include "missile.h"
#include "missile_manager.h"
#include "option.h"
#include "player.h"


#include "enemy_side_object.h"

#include "item_manager.h"
#include "enemy_bullet.h"
#include "enemy_bullet_manager.h"
#include "lazer_bullet.h"
#include "enemy_lazer_manager.h"
#include "killershot.h"
#include "killershot_manager.h"
#include "enemy_missile.h"
#include "enemy_missile_manager.h"

#include "multiple_branch_tree.h"
#include "enemy_parts.h"
#include "enemy_parts_manager.h"
#include "enemy.h"
#include "enemy_manager.h"
#include "enemy_generator.h"
#include "enemy_generator_manager.h"
#include "boss.h"
#include "boss1.h"
#include "boss2.h"
#include "boss3.h"
#include "boss4.h"
#include "boss5.h"
#include "boss6.h"
#include "boss7.h"
#include "boss_manager.h"

#include "landscape.h"
#include "landscape_vacuumed_star.h"
#include "landscape_passing_star.h"
#include "landscape_crystal1.h"
#include "landscape_floor1.h"
#include "landscape_container1.h"
#include "landscape_gas_tank1.h"
#include "landscape_ice_needle.h"
#include "landscape_manager.h"
#include "stage_manager.h"

#include "battle_frame.h"
#include "background_manager.h"
#include "stage1_background_manager.h"
#include "stage2_background_manager.h"
#include "stage3_background_manager.h"
#include "stage4_background_manager.h"
#include "stage5_background_manager.h"
#include "stage6_background_manager.h"
#include "stage7_background_manager.h"

#include "pad_info.h"
#include "viewController.h"
#include "splash_view_controller.h"
#include "title_view_controller.h"
#include "endurance_view_controller.h"
#include "replay_view_controller.h"
#include "ending_view_controller.h"
#include "select_view_controller.h"
#include "config_view_controller.h"
#include "name_entry_view_controller.h"

#include "viewControllerFactory.h"


int GAME_RUNNING=1;
DWORD WINAPI ThreadFunc(LPVOID vdParam){
	CSoundEffect* mSE=CSoundEffect::GetInstance();
	mSE->initSE();
	SetUseSoftwareMixingSoundFlag(false);
	SetEnableSoundCaptureFlag(false);

	while(GAME_RUNNING){
		Sleep(60);
		mSE->UpdateSingleSE();
		mSE->UpdateLoopSE();
	}
	return 1;
}

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow ){
	CImageDIB::hInst=hInstance;
	SetMainWindowText("Aurorablast3");
	ChangeWindowMode(true);
	SetWindowSize(960,720);
	if( DxLib_Init() == -1 )return -1; // ＤＸライブラリ初期化処理 // エラーが起きたら直ちに終了			
	SetDrawScreen(DX_SCREEN_BACK);
	
	DWORD dwID;
	CreateThread(NULL,0,ThreadFunc,NULL,0,&dwID);	

	CViewControllerFactory vcf;
	timeBeginPeriod(1);	
	static DWORD fpsTime=0;
	DWORD dwTime=timeGetTime()+17;
	DWORD tmpTime;
	static int f_counter=1;
	while(!ProcessMessage() && !ClearDrawScreen()){
		tmpTime=timeGetTime();
		if(dwTime>tmpTime){Sleep(1);continue;}
		dwTime=tmpTime+17;
		f_counter++;
		if(tmpTime>fpsTime+1000){
			fpsTime=tmpTime;
			//f_counted=f_counter; f_counter=1;FPS実相寺に解禁
		}
		vcf.onTimer();
	}
	timeBeginPeriod(1);
	GAME_RUNNING=0;
	DxLib_End() ;				// ＤＸライブラリ使用の終了処理
	return 0 ;				// ソフトの終了 
}
