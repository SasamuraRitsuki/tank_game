#include "../../dxlib_ext/dxlib_ext.h"
#include "gm_scene_title.h"
#include "gm_scene_play.h"
#include "../gm_mgr/gm_manager.h"
#include "../gm_mgr/resource_manager.h"

SceneTitle::SceneTitle() {
	SetBackgroundColor(32, 32, 32);

	//�摜��ǂݍ���
	back_ground_gfx_ = ResourceManager::GetInstance()->loadGraph("graphics/title_back_ground.png");
	back_black_gfx_ = ResourceManager::GetInstance()->loadGraph("graphics/black2.jpg");
	choiced_back_black_gfx_ = ResourceManager::GetInstance()->loadGraph("graphics/gray1.jpg");
	play_rule_gfx_ = ResourceManager::GetInstance()->loadGraph("graphics/play_rule.png");
	//���y��ǂݍ���
	bgm_snd_ = ResourceManager::GetInstance()->loadSound("sound/bgm/menu_bgm.mp3");
	pray_rule_snd_ = ResourceManager::GetInstance()->loadSound("sound/se/pray_rule_se.mp3");
	enter_snd_ = ResourceManager::GetInstance()->loadSound("sound/se/enter_se.mp3");

	

	//�I�����͑I������Ă��Ȃ��摜�ɕς��Ă���
	start_choiced_gfx_ = back_black_gfx_;
	pray_rule_choiced_gfx_ = back_black_gfx_;
	pray_rule_close_choiced_gfx_ = back_black_gfx_;
	//bgm�𗬂�
	PlaySoundMem(bgm_snd_, DX_PLAYTYPE_LOOP);

}

SceneTitle::~SceneTitle() {
	StopSoundMem(bgm_snd_);
}

void SceneTitle::update(float delta_time) {
	timeleft_ += delta_time;
	//�_�ŗp�̌v�Z
	elapsed_ = sin(timeleft_ * 5);

	float mouse_pos_x = tnl::Input::GetMousePosition().x;
	float mouse_pos_y = tnl::Input::GetMousePosition().y;


	//�}�E�X���X�^�[�g�{�^���ɗ��Ă�����
	if (mouse_pos_x >= START_BACK_POS_FIRST.x && mouse_pos_x <= START_BACK_POS_LAST.x &&
		mouse_pos_y >= START_BACK_POS_FIRST.y && mouse_pos_y <= START_BACK_POS_LAST.y) {

		start_choiced_gfx_ = choiced_back_black_gfx_;

		//�V�ѕ����\������Ă��Ȃ����ɃN���b�N���ꂽ��
		if (tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT) && !play_rule_flag_) {
			//���ʉ��𗬂�
			PlaySoundMem(enter_snd_, DX_PLAYTYPE_BACK);

			//�v���C�V�[���ւ̑J��
			auto mgr = GM::GetInstance();
			mgr->changeScene(std::make_shared<ScenePlay>());
		}
	}
	else start_choiced_gfx_ = back_black_gfx_;

	//�}�E�X���V�ѕ��{�^���ɗ��Ă�����
	if (mouse_pos_x >= PLAY_RULE_BACK_POS_FIRST.x && mouse_pos_x <= PLAY_RULE_BACK_POS_LAST.x &&
		mouse_pos_y >= PLAY_RULE_BACK_POS_FIRST.y && mouse_pos_y <= PLAY_RULE_BACK_POS_LAST.y) {

		pray_rule_choiced_gfx_ = choiced_back_black_gfx_;

		//�V�ѕ����\������Ă��Ȃ����ɃN���b�N���ꂽ��
		if (tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT) && !play_rule_flag_) {
			//���ʉ��𗬂�
			PlaySoundMem(pray_rule_snd_, DX_PLAYTYPE_BACK);

			//�V�ѕ��̕\��
			play_rule_flag_ = true;
		}
	}
	else pray_rule_choiced_gfx_ = back_black_gfx_;

	//�}�E�X������{�^���ɗ��Ă�����
	if (mouse_pos_x >= PLAY_RULE_CLOSE_BACK_POS_FIRST.x && mouse_pos_x <= PLAY_RULE_CLOSE_BACK_POS_LAST.x &&
		mouse_pos_y >= PLAY_RULE_CLOSE_BACK_POS_FIRST.y && mouse_pos_y <= PLAY_RULE_CLOSE_BACK_POS_LAST.y) {

		pray_rule_close_choiced_gfx_ = choiced_back_black_gfx_;

		//�V�ѕ����\������Ă��鎞�ɃN���b�N���ꂽ��
		if (tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT) && play_rule_flag_) {
			//���ʉ��𗬂�
			PlaySoundMem(pray_rule_snd_, DX_PLAYTYPE_BACK);

			//�V�ѕ������
			play_rule_flag_ = false;
		}
	}
	else pray_rule_close_choiced_gfx_ = back_black_gfx_;
	
	
	/*if (tnl::Input::IsKeyDownTrigger(eKeys::KB_SPACE)) {
		play_rule_flag_ = play_rule_flag_ == true ? false : true;
	}*/
}

void SceneTitle::draw() {

	//�w�i�摜
	DrawGraphF(0,0, back_ground_gfx_,false);

	//�^�C�g���̌��̍��������w�i
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, TITLE_BACK_GFX_ALPHA);
	//�^�C�g���̗�
	DrawExtendGraph(TITLE_BACK_POS_FIRST.x, TITLE_BACK_POS_FIRST.y,
		TITLE_BACK_POS_LAST.x, TITLE_BACK_POS_LAST.y, back_black_gfx_, false);
	//�V�ѕ������Ă��鎞�̌��̔w�i
	if (play_rule_flag_) 
		DrawExtendGraph(0, 0,DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT, back_black_gfx_, false);

	//�I�����̌��̍��������w�i
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, CHOICE_BACK_GFX_ALPHA);
	//�X�^�[�g�̗�
	DrawExtendGraph(START_BACK_POS_FIRST.x, START_BACK_POS_FIRST.y,
		START_BACK_POS_LAST.x, START_BACK_POS_LAST.y, start_choiced_gfx_, false);
	//�V�ѕ��̗�
	DrawExtendGraph(PLAY_RULE_BACK_POS_FIRST.x, PLAY_RULE_BACK_POS_FIRST.y,
		PLAY_RULE_BACK_POS_LAST.x, PLAY_RULE_BACK_POS_LAST.y, pray_rule_choiced_gfx_, false);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	//�^�C�g���̕\��
	SetFontSize(title_fontsize_);
	DrawStringEx(TITLE_TEXT_POS.x, TITLE_TEXT_POS.y, TEXT_COLOR,"��Ԃ�BANG!!!");
	
	//�N���b�N�e�L�X�g�̕\��
	SetFontSize(click_fontsize_);
	if(elapsed_ > 0)
	DrawStringEx(CLICK_TEXT_POS.x, CLICK_TEXT_POS.y, 0, "���N���b�N�������ăl");

	//�X�^�[�g�ƗV�ѕ��̕\��
	SetFontSize(normal_fontsize_);
	DrawStringEx(START_TEXT_POS.x, START_TEXT_POS.y, TEXT_COLOR, "�X�^�[�g");
	DrawStringEx(PLAY_RULE_TEXT_POS.x, PLAY_RULE_TEXT_POS.y, TEXT_COLOR, "�V�ѕ�");

	//�V�ѕ��̕\��
	if (play_rule_flag_) {
		//�V�ѕ��̉摜�̕\��
		DrawGraphF(0, 0, play_rule_gfx_, true);

		//����̌��̍��������w�i
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, CHOICE_BACK_GFX_ALPHA);
		DrawExtendGraph(PLAY_RULE_CLOSE_BACK_POS_FIRST.x, PLAY_RULE_CLOSE_BACK_POS_FIRST.y,
			PLAY_RULE_CLOSE_BACK_POS_LAST.x, PLAY_RULE_CLOSE_BACK_POS_LAST.y, pray_rule_close_choiced_gfx_, false);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		//����̕\��
		DrawStringEx(PLAY_RULE_CLOSE_TEXT_POS.x, PLAY_RULE_CLOSE_TEXT_POS.y, TEXT_COLOR, "����");
	}
	//DrawStringEx(DXE_WINDOW_WIDTH/2, DXE_WINDOW_HEIGHT/2, 0, "��");


}