#pragma once
#include "../gm_mgr/Scene_base.h"

class SceneTitle : public SceneBase {
public:
	SceneTitle();
	~SceneTitle();

	void update(float delta_time) override;
	void draw() override;

private:
	//�^�C�g���̃t�H���g�̑傫��
	const int title_fontsize_ = 150;
	//�^�C�g���̍��W
	const tnl::Vector2i TITLE_TEXT_POS = { 150,DXE_WINDOW_HEIGHT / 2 - title_fontsize_ / 2 - 100 };
	//�N���b�N�̍��W
	const tnl::Vector2i CLICK_TEXT_POS = { 390,460 };
	//bgm�̉��y�p�X
	int bgm_snd_;
	//�o�ߎ���
	float timeleft_ = 0;
	//�_�ł̒l
	float elapsed_ = 0;

};