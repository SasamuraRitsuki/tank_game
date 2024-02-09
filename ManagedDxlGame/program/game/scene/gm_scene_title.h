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
	//タイトルの座標
	const tnl::Vector2i TITLE_TEXT_POS = { 150,DXE_WINDOW_HEIGHT / 2 - title_fontsize_ / 2 - 100 };
	//クリックの座標
	const tnl::Vector2i CLICK_TEXT_POS = { 390,460 };
	//bgmの音楽パス
	int bgm_snd_;
	//経過時間
	float timeleft_ = 0;
	//点滅の値
	float elapsed_ = 0;

};