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
// �Q�[���N�����ɂP�x�������s����܂�
void gameStart() {
	srand(time(0));

	SetDefaultLightParameter("directional_light_parameter.bin");

	GM::GetInstance(std::make_shared<SceneTitle>());
	//GM::GetInstance(std::make_shared<ScenePlay>());
	//GM::GetInstance(std::make_shared<SceneResult>());
}


//------------------------------------------------------------------------------------------------------------
// ���t���[�����s����܂�
void gameMain(float delta_time) {

	GM::GetInstance()->update(delta_time);


	//DrawFpsIndicator({ 10, DXE_WINDOW_HEIGHT - 10, 0 }, delta_time);

	/*SetFontSize(20);
	DrawDefaultLightGuiController();*/
}

//------------------------------------------------------------------------------------------------------------
// �Q�[���I�����ɂP�x�������s����܂�
void gameEnd() {


}
