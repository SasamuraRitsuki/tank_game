#pragma once
#include "../gm_mgr/Scene_base.h"

class SceneTitle : public SceneBase {
public:
	SceneTitle();
	~SceneTitle();

	void update(float delta_time) override;
	void draw() override;

private:
	//タイトルのフォントの大きさ
	const int title_fontsize_ = 150;
	//通常フォントの大きさ
	const int normal_fontsize_ = 50;
	//クリックフォントの大きさ
	const int click_fontsize_ = 40;
	//テキストのカラーコード
	const int TEXT_COLOR = 0xffd700;
	//タイトルの黒い背景の画像の透明度
	const int TITLE_BACK_GFX_ALPHA = 50;
	//選択肢の黒い背景の画像の透明度
	const int CHOICE_BACK_GFX_ALPHA = 150;

	//タイトルのテキストの座標
	const tnl::Vector2i TITLE_TEXT_POS = { 150,50 };
	//スタートのテキストの座標
	const tnl::Vector2i START_TEXT_POS = { DXE_WINDOW_WIDTH / 2 - (50 * 2),470 };
	//遊び方のテキストの座標
	const tnl::Vector2i PLAY_RULE_TEXT_POS = { DXE_WINDOW_WIDTH / 2 - 75,555 };
	//閉じるのテキストの座標
	const tnl::Vector2i PLAY_RULE_CLOSE_TEXT_POS = { 970,120 };
	//クリックのテキストの座標
	const tnl::Vector2i CLICK_TEXT_POS = { DXE_WINDOW_WIDTH / 2 - (click_fontsize_ * 5),640 };

	//タイトルの黒背景の位置の左上の位置
	const tnl::Vector2i TITLE_BACK_POS_FIRST = { 140,30 };
	//タイトルの黒背景の位置の右下の位置
	const tnl::Vector2i TITLE_BACK_POS_LAST = { DXE_WINDOW_WIDTH - 140,210 };
	//スタートの黒背景の位置の左上の位置
	const tnl::Vector2i START_BACK_POS_FIRST = { START_TEXT_POS.x - 5,START_TEXT_POS.y - 5 };
	//スタートの黒背景の位置の右下の位置
	const tnl::Vector2i START_BACK_POS_LAST = { START_TEXT_POS.x + (normal_fontsize_ * 4) + 5,START_TEXT_POS.y + normal_fontsize_ + 5 };
	//遊び方の黒背景の位置の左上の位置
	const tnl::Vector2i PLAY_RULE_BACK_POS_FIRST = { PLAY_RULE_TEXT_POS.x - 5,PLAY_RULE_TEXT_POS.y - 5 };
	//遊び方の黒背景の位置の右下の位置
	const tnl::Vector2i PLAY_RULE_BACK_POS_LAST = { PLAY_RULE_TEXT_POS.x + (normal_fontsize_ * 3) + 5,PLAY_RULE_TEXT_POS.y + normal_fontsize_ + 5 };
	//閉じるの黒背景の位置の左上の位置
	const tnl::Vector2i PLAY_RULE_CLOSE_BACK_POS_FIRST = { PLAY_RULE_CLOSE_TEXT_POS.x - 10,PLAY_RULE_CLOSE_TEXT_POS.y - 10 };
	//閉じるの黒背景の位置の右下の位置
	const tnl::Vector2i PLAY_RULE_CLOSE_BACK_POS_LAST = { PLAY_RULE_CLOSE_TEXT_POS.x + (normal_fontsize_ * 3) + 10,PLAY_RULE_CLOSE_TEXT_POS.y + normal_fontsize_ + 10 };


	//背景の画像パス
	int back_ground_gfx_;
	//後ろの黒い背景の画像パス
	int back_black_gfx_;
	//選択されてる黒い背景の画像パス
	int choiced_back_black_gfx_;
	//遊び方の画像パス
	int play_rule_gfx_;
	//bgmの音楽パス
	int bgm_snd_;
	//遊び方の選択音の音楽パス
	int pray_rule_snd_;
	//決定音の音楽パス
	int enter_snd_;
	//スタートボタンにマウスが来ている時の表示画像
	int start_choiced_gfx_;
	//遊び方ボタンにマウスが来ている時の表示画像
	int pray_rule_choiced_gfx_;
	//閉じるボタンにマウスが来ている時の表示画像
	int pray_rule_close_choiced_gfx_;
	//遊び方を表示するフラグ
	bool play_rule_flag_ = false;
	//経過時間
	float timeleft_ = 0;
	//点滅の値
	float elapsed_ = 0;
};