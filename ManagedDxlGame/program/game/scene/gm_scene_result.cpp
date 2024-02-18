#include "../../dxlib_ext/dxlib_ext.h"
#include "gm_scene_result.h"
#include "gm_scene_title.h"
#include "../gm_mgr/gm_manager.h"
#include "../gm_mgr/resource_manager.h"

SceneResult::SceneResult(bool cleared) {
	SetBackgroundColor(32, 32, 32);
	//SetBackgroundColor(255, 255, 255);
	//background_hdl_ = LoadGraph("graphics/back_ground.jpg");

	cleared_ = cleared;

	//�Q�[���N���A��
	if (cleared_) {
		clear_snd_ = ResourceManager::GetInstance()->loadSound("sound/se/game_clear.mp3");
		//���ʉ�
		PlaySoundMem(clear_snd_, DX_PLAYTYPE_BACK);
	}
	//�Q�[���I�[�o�[��
	else {
		failure_snd_ = ResourceManager::GetInstance()->loadSound("sound/se/enemy_dead.mp3");
		//���ʉ�
		PlaySoundMem(failure_snd_, DX_PLAYTYPE_BACK);
	}
}

SceneResult::~SceneResult() {

}

void SceneResult::update(float delta_time) {
	timeleft_ += delta_time;
	elapsed_ = sin(timeleft_ * 5);


	if (tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT)) {
		auto mgr = GM::GetInstance();
		tnl::Input::GetMousePosition;
		mgr->changeScene(std::make_shared<SceneTitle>());
	}
}

void SceneResult::draw() {
	SetFontSize(title_fontsize_);
	if (cleared_) {
		DrawStringEx(CLEAR_TEXT_POS.x, CLEAR_TEXT_POS.y, TEXT_COLOR, "�Q�[���N���A");
	}
	else {
		DrawStringEx(OVER_TEXT_POS.x, OVER_TEXT_POS.y, TEXT_COLOR, "�Q�[���I�[�o�[");
	}
	SetFontSize(50);
	if (elapsed_ > 0)
		DrawStringEx(CLICK_TEXT_POS.x, CLICK_TEXT_POS.y, TEXT_COLOR, "���N���b�N���@�����ăl");
		//DrawStringEx(ENTER_TEXT_POS.x, ENTER_TEXT_POS.y, -1, "Space���@�����ăl");
	//DrawStringEx(ENTER_TEXT_POS.x, ENTER_TEXT_POS.y + 100, -1, "%f",elapsed_);
}