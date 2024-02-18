#pragma once
#include "../gm_mgr/Scene_base.h"

class SceneResult : public SceneBase {
public:
	SceneResult(bool cleared = false);
	~SceneResult();

	void update(float delta_time) override;
	void draw() override;

private:
	//タイトルのフォントの大きさ
	const int title_fontsize_ = 150;
	//クリアテキストの座標
	const tnl::Vector2i CLEAR_TEXT_POS = { 180,DXE_WINDOW_HEIGHT / 2 - title_fontsize_ / 2 - 50 };
	//ゲームオーバーテキストの座標
	const tnl::Vector2i OVER_TEXT_POS = { 100,DXE_WINDOW_HEIGHT / 2 - title_fontsize_ / 2 - 50 };
	//エンターの座標
	const tnl::Vector2i CLICK_TEXT_POS = { 345,460 };
	//テキストのカラーコード
	const int TEXT_COLOR = 0xffd700;
	//const int TEXT_COLOR = 0;

	//経過時間
	float timeleft_ = 0;
	//点滅の値
	float elapsed_ = 0;
	//ゲームがクリアされたかどうか
	bool cleared_ = false;

	//ゲームクリアの効果音
	int clear_snd_;
	//ゲームオーバーの効果音
	int failure_snd_;
};