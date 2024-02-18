#pragma once
#include "../gm_mgr/Scene_base.h"

class SceneResult : public SceneBase {
public:
	SceneResult(bool cleared = false);
	~SceneResult();

	void update(float delta_time) override;
	void draw() override;

private:
	//�^�C�g���̃t�H���g�̑傫��
	const int title_fontsize_ = 150;
	//�N���A�e�L�X�g�̍��W
	const tnl::Vector2i CLEAR_TEXT_POS = { 180,DXE_WINDOW_HEIGHT / 2 - title_fontsize_ / 2 - 50 };
	//�Q�[���I�[�o�[�e�L�X�g�̍��W
	const tnl::Vector2i OVER_TEXT_POS = { 100,DXE_WINDOW_HEIGHT / 2 - title_fontsize_ / 2 - 50 };
	//�G���^�[�̍��W
	const tnl::Vector2i CLICK_TEXT_POS = { 345,460 };
	//�e�L�X�g�̃J���[�R�[�h
	const int TEXT_COLOR = 0xffd700;
	//const int TEXT_COLOR = 0;

	//�o�ߎ���
	float timeleft_ = 0;
	//�_�ł̒l
	float elapsed_ = 0;
	//�Q�[�����N���A���ꂽ���ǂ���
	bool cleared_ = false;

	//�Q�[���N���A�̌��ʉ�
	int clear_snd_;
	//�Q�[���I�[�o�[�̌��ʉ�
	int failure_snd_;
};