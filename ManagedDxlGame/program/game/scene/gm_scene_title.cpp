#include "../../dxlib_ext/dxlib_ext.h"
#include "gm_scene_title.h"
#include "gm_scene_play.h"
#include "../gm_mgr/gm_manager.h"
#include "../gm_mgr/resource_manager.h"

SceneTitle::SceneTitle() {
	SetBackgroundColor(32, 32, 32);

	//画像を読み込む
	back_ground_gfx_ = ResourceManager::GetInstance()->loadGraph("graphics/title_back_ground.png");
	back_black_gfx_ = ResourceManager::GetInstance()->loadGraph("graphics/black2.jpg");
	choiced_back_black_gfx_ = ResourceManager::GetInstance()->loadGraph("graphics/gray1.jpg");
	play_rule_gfx_ = ResourceManager::GetInstance()->loadGraph("graphics/play_rule.png");
	//音楽を読み込む
	bgm_snd_ = ResourceManager::GetInstance()->loadSound("sound/bgm/menu_bgm.mp3");
	pray_rule_snd_ = ResourceManager::GetInstance()->loadSound("sound/se/pray_rule_se.mp3");
	enter_snd_ = ResourceManager::GetInstance()->loadSound("sound/se/enter_se.mp3");

	

	//選択肢は選択されていない画像に変えておく
	start_choiced_gfx_ = back_black_gfx_;
	pray_rule_choiced_gfx_ = back_black_gfx_;
	pray_rule_close_choiced_gfx_ = back_black_gfx_;
	//bgmを流す
	PlaySoundMem(bgm_snd_, DX_PLAYTYPE_LOOP);

}

SceneTitle::~SceneTitle() {
	StopSoundMem(bgm_snd_);
}

void SceneTitle::update(float delta_time) {
	timeleft_ += delta_time;
	//点滅用の計算
	elapsed_ = sin(timeleft_ * 5);

	float mouse_pos_x = tnl::Input::GetMousePosition().x;
	float mouse_pos_y = tnl::Input::GetMousePosition().y;


	//マウスがスタートボタンに来ていた時
	if (mouse_pos_x >= START_BACK_POS_FIRST.x && mouse_pos_x <= START_BACK_POS_LAST.x &&
		mouse_pos_y >= START_BACK_POS_FIRST.y && mouse_pos_y <= START_BACK_POS_LAST.y) {

		start_choiced_gfx_ = choiced_back_black_gfx_;

		//遊び方が表示されていない時にクリックされた時
		if (tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT) && !play_rule_flag_) {
			//効果音を流す
			PlaySoundMem(enter_snd_, DX_PLAYTYPE_BACK);

			//プレイシーンへの遷移
			auto mgr = GM::GetInstance();
			mgr->changeScene(std::make_shared<ScenePlay>());
		}
	}
	else start_choiced_gfx_ = back_black_gfx_;

	//マウスが遊び方ボタンに来ていた時
	if (mouse_pos_x >= PLAY_RULE_BACK_POS_FIRST.x && mouse_pos_x <= PLAY_RULE_BACK_POS_LAST.x &&
		mouse_pos_y >= PLAY_RULE_BACK_POS_FIRST.y && mouse_pos_y <= PLAY_RULE_BACK_POS_LAST.y) {

		pray_rule_choiced_gfx_ = choiced_back_black_gfx_;

		//遊び方が表示されていない時にクリックされた時
		if (tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT) && !play_rule_flag_) {
			//効果音を流す
			PlaySoundMem(pray_rule_snd_, DX_PLAYTYPE_BACK);

			//遊び方の表示
			play_rule_flag_ = true;
		}
	}
	else pray_rule_choiced_gfx_ = back_black_gfx_;

	//マウスが閉じるボタンに来ていた時
	if (mouse_pos_x >= PLAY_RULE_CLOSE_BACK_POS_FIRST.x && mouse_pos_x <= PLAY_RULE_CLOSE_BACK_POS_LAST.x &&
		mouse_pos_y >= PLAY_RULE_CLOSE_BACK_POS_FIRST.y && mouse_pos_y <= PLAY_RULE_CLOSE_BACK_POS_LAST.y) {

		pray_rule_close_choiced_gfx_ = choiced_back_black_gfx_;

		//遊び方が表示されている時にクリックされた時
		if (tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT) && play_rule_flag_) {
			//効果音を流す
			PlaySoundMem(pray_rule_snd_, DX_PLAYTYPE_BACK);

			//遊び方を閉じる
			play_rule_flag_ = false;
		}
	}
	else pray_rule_close_choiced_gfx_ = back_black_gfx_;
	
	
	/*if (tnl::Input::IsKeyDownTrigger(eKeys::KB_SPACE)) {
		play_rule_flag_ = play_rule_flag_ == true ? false : true;
	}*/
}

void SceneTitle::draw() {

	//背景画像
	DrawGraphF(0,0, back_ground_gfx_,false);

	//タイトルの後ろの黒い薄い背景
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, TITLE_BACK_GFX_ALPHA);
	//タイトルの裏
	DrawExtendGraph(TITLE_BACK_POS_FIRST.x, TITLE_BACK_POS_FIRST.y,
		TITLE_BACK_POS_LAST.x, TITLE_BACK_POS_LAST.y, back_black_gfx_, false);
	//遊び方を見ている時の後ろの背景
	if (play_rule_flag_) 
		DrawExtendGraph(0, 0,DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT, back_black_gfx_, false);

	//選択肢の後ろの黒い薄い背景
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, CHOICE_BACK_GFX_ALPHA);
	//スタートの裏
	DrawExtendGraph(START_BACK_POS_FIRST.x, START_BACK_POS_FIRST.y,
		START_BACK_POS_LAST.x, START_BACK_POS_LAST.y, start_choiced_gfx_, false);
	//遊び方の裏
	DrawExtendGraph(PLAY_RULE_BACK_POS_FIRST.x, PLAY_RULE_BACK_POS_FIRST.y,
		PLAY_RULE_BACK_POS_LAST.x, PLAY_RULE_BACK_POS_LAST.y, pray_rule_choiced_gfx_, false);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	//タイトルの表示
	SetFontSize(title_fontsize_);
	DrawStringEx(TITLE_TEXT_POS.x, TITLE_TEXT_POS.y, TEXT_COLOR,"戦車でBANG!!!");
	
	//クリックテキストの表示
	SetFontSize(click_fontsize_);
	if(elapsed_ > 0)
	DrawStringEx(CLICK_TEXT_POS.x, CLICK_TEXT_POS.y, 0, "左クリックを押してネ");

	//スタートと遊び方の表示
	SetFontSize(normal_fontsize_);
	DrawStringEx(START_TEXT_POS.x, START_TEXT_POS.y, TEXT_COLOR, "スタート");
	DrawStringEx(PLAY_RULE_TEXT_POS.x, PLAY_RULE_TEXT_POS.y, TEXT_COLOR, "遊び方");

	//遊び方の表示
	if (play_rule_flag_) {
		//遊び方の画像の表示
		DrawGraphF(0, 0, play_rule_gfx_, true);

		//閉じるの後ろの黒い薄い背景
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, CHOICE_BACK_GFX_ALPHA);
		DrawExtendGraph(PLAY_RULE_CLOSE_BACK_POS_FIRST.x, PLAY_RULE_CLOSE_BACK_POS_FIRST.y,
			PLAY_RULE_CLOSE_BACK_POS_LAST.x, PLAY_RULE_CLOSE_BACK_POS_LAST.y, pray_rule_close_choiced_gfx_, false);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		//閉じるの表示
		DrawStringEx(PLAY_RULE_CLOSE_TEXT_POS.x, PLAY_RULE_CLOSE_TEXT_POS.y, TEXT_COLOR, "閉じる");
	}
	//DrawStringEx(DXE_WINDOW_WIDTH/2, DXE_WINDOW_HEIGHT/2, 0, "あ");


}