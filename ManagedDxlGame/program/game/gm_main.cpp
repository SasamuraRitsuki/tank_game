#include <time.h>
#include <string>
#include <numbers>
#include <functional>
#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"
#include "gm_mgr/gm_manager.h"
#include "scene/gm_scene_title.h"
#include "scene/gm_scene_play.h"
#include "scene/gm_scene_result.h"

//------------------------------------------------------------------------------------------------------------
// ゲーム起動時に１度だけ実行されます
void gameStart() {
	srand(time(0));

	SetDefaultLightParameter("directional_light_parameter.bin");

	GM::GetInstance(std::make_shared<SceneTitle>());
	//GM::GetInstance(std::make_shared<ScenePlay>());
	//GM::GetInstance(std::make_shared<SceneResult>());
}


//------------------------------------------------------------------------------------------------------------
// 毎フレーム実行されます
void gameMain(float delta_time) {

	GM::GetInstance()->update(delta_time);


	//DrawFpsIndicator({ 10, DXE_WINDOW_HEIGHT - 10, 0 }, delta_time);

	/*SetFontSize(20);
	DrawDefaultLightGuiController();*/
}

//------------------------------------------------------------------------------------------------------------
// ゲーム終了時に１度だけ実行されます
void gameEnd() {


}
