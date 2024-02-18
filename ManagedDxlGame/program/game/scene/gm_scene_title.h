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
	//�ʏ�t�H���g�̑傫��
	const int normal_fontsize_ = 50;
	//�N���b�N�t�H���g�̑傫��
	const int click_fontsize_ = 40;
	//�e�L�X�g�̃J���[�R�[�h
	const int TEXT_COLOR = 0xffd700;
	//�^�C�g���̍����w�i�̉摜�̓����x
	const int TITLE_BACK_GFX_ALPHA = 50;
	//�I�����̍����w�i�̉摜�̓����x
	const int CHOICE_BACK_GFX_ALPHA = 150;

	//�^�C�g���̃e�L�X�g�̍��W
	const tnl::Vector2i TITLE_TEXT_POS = { 150,50 };
	//�X�^�[�g�̃e�L�X�g�̍��W
	const tnl::Vector2i START_TEXT_POS = { DXE_WINDOW_WIDTH / 2 - (50 * 2),470 };
	//�V�ѕ��̃e�L�X�g�̍��W
	const tnl::Vector2i PLAY_RULE_TEXT_POS = { DXE_WINDOW_WIDTH / 2 - 75,555 };
	//����̃e�L�X�g�̍��W
	const tnl::Vector2i PLAY_RULE_CLOSE_TEXT_POS = { 970,120 };
	//�N���b�N�̃e�L�X�g�̍��W
	const tnl::Vector2i CLICK_TEXT_POS = { DXE_WINDOW_WIDTH / 2 - (click_fontsize_ * 5),640 };

	//�^�C�g���̍��w�i�̈ʒu�̍���̈ʒu
	const tnl::Vector2i TITLE_BACK_POS_FIRST = { 140,30 };
	//�^�C�g���̍��w�i�̈ʒu�̉E���̈ʒu
	const tnl::Vector2i TITLE_BACK_POS_LAST = { DXE_WINDOW_WIDTH - 140,210 };
	//�X�^�[�g�̍��w�i�̈ʒu�̍���̈ʒu
	const tnl::Vector2i START_BACK_POS_FIRST = { START_TEXT_POS.x - 5,START_TEXT_POS.y - 5 };
	//�X�^�[�g�̍��w�i�̈ʒu�̉E���̈ʒu
	const tnl::Vector2i START_BACK_POS_LAST = { START_TEXT_POS.x + (normal_fontsize_ * 4) + 5,START_TEXT_POS.y + normal_fontsize_ + 5 };
	//�V�ѕ��̍��w�i�̈ʒu�̍���̈ʒu
	const tnl::Vector2i PLAY_RULE_BACK_POS_FIRST = { PLAY_RULE_TEXT_POS.x - 5,PLAY_RULE_TEXT_POS.y - 5 };
	//�V�ѕ��̍��w�i�̈ʒu�̉E���̈ʒu
	const tnl::Vector2i PLAY_RULE_BACK_POS_LAST = { PLAY_RULE_TEXT_POS.x + (normal_fontsize_ * 3) + 5,PLAY_RULE_TEXT_POS.y + normal_fontsize_ + 5 };
	//����̍��w�i�̈ʒu�̍���̈ʒu
	const tnl::Vector2i PLAY_RULE_CLOSE_BACK_POS_FIRST = { PLAY_RULE_CLOSE_TEXT_POS.x - 10,PLAY_RULE_CLOSE_TEXT_POS.y - 10 };
	//����̍��w�i�̈ʒu�̉E���̈ʒu
	const tnl::Vector2i PLAY_RULE_CLOSE_BACK_POS_LAST = { PLAY_RULE_CLOSE_TEXT_POS.x + (normal_fontsize_ * 3) + 10,PLAY_RULE_CLOSE_TEXT_POS.y + normal_fontsize_ + 10 };


	//�w�i�̉摜�p�X
	int back_ground_gfx_;
	//���̍����w�i�̉摜�p�X
	int back_black_gfx_;
	//�I������Ă鍕���w�i�̉摜�p�X
	int choiced_back_black_gfx_;
	//�V�ѕ��̉摜�p�X
	int play_rule_gfx_;
	//bgm�̉��y�p�X
	int bgm_snd_;
	//�V�ѕ��̑I�����̉��y�p�X
	int pray_rule_snd_;
	//���艹�̉��y�p�X
	int enter_snd_;
	//�X�^�[�g�{�^���Ƀ}�E�X�����Ă��鎞�̕\���摜
	int start_choiced_gfx_;
	//�V�ѕ��{�^���Ƀ}�E�X�����Ă��鎞�̕\���摜
	int pray_rule_choiced_gfx_;
	//����{�^���Ƀ}�E�X�����Ă��鎞�̕\���摜
	int pray_rule_close_choiced_gfx_;
	//�V�ѕ���\������t���O
	bool play_rule_flag_ = false;
	//�o�ߎ���
	float timeleft_ = 0;
	//�_�ł̒l
	float elapsed_ = 0;
};