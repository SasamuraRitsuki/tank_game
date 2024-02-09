#include "../../dxlib_ext/dxlib_ext.h"
#include "gm_scene_title.h"
#include "gm_scene_play.h"
#include "../gm_mgr/gm_manager.h"
#include "../gm_mgr/resource_manager.h"

SceneTitle::SceneTitle() {
	SetBackgroundColor(32, 32, 32);

	//音楽を読み込む
	bgm_snd_ = ResourceManager::GetInstance()->loadSound("sound/bgm/menu_bgm.mp3");

	PlaySoundMem(bgm_snd_, DX_PLAYTYPE_LOOP);

}

SceneTitle::~SceneTitle() {
	StopSoundMem(bgm_snd_);
}

void SceneTitle::update(float delta_time) {
	timeleft_ += delta_time;
	elapsed_ = sin(timeleft_ * 5);

	/*if (GetMouseInput() & MOUSE_INPUT_LEFT) {
		clicked_ = true;
	}
	else {
		clicked_ = false;
	}*/
	if (tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT)) {
		auto mgr = GM::GetInstance();
		mgr->changeScene(std::make_shared<ScenePlay>());
	}
}

void SceneTitle::draw() {
	SetFontSize(title_fontsize_);
	//DrawStringEx(TITLE_TEXT_POS.x, TITLE_TEXT_POS.y,-1,"Tank Game");
	DrawStringEx(TITLE_TEXT_POS.x, TITLE_TEXT_POS.y,-1,"戦車でBANG!!!");
	SetFontSize(50);
	if(elapsed_ > 0)
	DrawStringEx(CLICK_TEXT_POS.x, CLICK_TEXT_POS.y, -1, "左クリックを押してネ");
	//DrawStringEx(ENTER_TEXT_POS.x, ENTER_TEXT_POS.y, -1, "Spaceを　押してネ");
	//DrawStringEx(ENTER_TEXT_POS.x, ENTER_TEXT_POS.y + 100, -1, "%f",elapsed_);
}