#pragma once
#include "Bullet.h"

class Tank {
public:
	Tank();
	~Tank();

	void update(float delta_time);
	void draw(Shared<dxe::Camera> camera);
	Shared<dxe::Mesh> mesh_ = nullptr;

	//�ǂƂ̓����蔻��
	bool TryWallCollision(std::shared_ptr<Bullet> blt);
	//�G�ƒe�̓����蔻��
	bool TryEnemyCollision(std::shared_ptr<Bullet> blt, tnl::Vector3 enemy_pos, tnl::Vector3 enemy_size);


	//���݂�tank�̈ʒu
	tnl::Vector3 tank_pos_;
	//tank�̔���p�̑傫��
	tnl::Vector3 tank_size_v;
	//�W�����v�̒l
	float jump_value_ = 0;
	//�W�����v����
	bool jumped_ = false;
	//�_���[�W���󂯂�
	bool damaged_ = false;
	//�c��HP
	int tank_hp_;
	//��]��
	bool rolling_ = false;
	//���S����
	bool dead_ = false;
	//������1�ɏ���Ă��邩�ǂ���
	bool ride_move_floor1_ = false;
	//������2�ɏ���Ă��邩�ǂ���
	bool ride_move_floor2_ = false;

private:
	//������ς���
	void DirChange(int dir);
	//�}�E�X�ւ̊p�x�v�Z
	void AngleCalcToMouse();
	//��]����
	void TankRolling(float delta_time);
	//�������v�Z
	float EaseInOut(float t);
	//���̏����v�Z
	void MoveFloorCalc(int move_floor_sort,bool ride_move_floor,bool ride_calc,float delta_move_floor_pos);

	//�X�^�[�g�ʒu
	const tnl::Vector3 FIRST_POS = { 0,50,0 };
	//const tnl::Vector3 FIRST_POS = { 0,50,2000 };
	//tank�̌`
	const tnl::Vector3 TANK_FORM = { 1.0f, 0.75f, 1.0f };
	//�e�̉摜�̈ʒu�Ƒ傫��
	const tnl::Vector3 BULLET_POS = { 32, 50, 0.8f };
	//HP�̃Q�[�W�ʒu
	const tnl::Vector2i hp_gauge_pos_ = { DXE_WINDOW_WIDTH / 3 ,DXE_WINDOW_HEIGHT * 4 / 5 };
	//�X�s���Q�[�W�ʒu
	const tnl::Vector2i spin_gauge_pos_ = { hp_gauge_pos_.x ,hp_gauge_pos_.y + 60 };
	//�e�L�X�g�̈ʒu
	const tnl::Vector2i HP_TEXT_POS = { hp_gauge_pos_.x - 90, hp_gauge_pos_.y };
	const tnl::Vector2i SPIN_TEXT_POS = { spin_gauge_pos_.x - 150, spin_gauge_pos_.y - 5 };
	const tnl::Vector2i SPIN_CLICK_TEXT_POS = { SPIN_TEXT_POS.x + 600, SPIN_TEXT_POS.y };
	//���̔����w�i�̈ʒu�̍���̈ʒu
	const tnl::Vector2i DOWN_BACK_POS_FIRST = { 140,hp_gauge_pos_.y - 20 };
	//���̔����w�i�̈ʒu�̉E���̈ʒu
	const tnl::Vector2i DOWN_BACK_POS_LAST = { DXE_WINDOW_WIDTH - 140,spin_gauge_pos_.y + 60 };
	//��̔����w�i�̈ʒu�̍���̈ʒu
	const tnl::Vector2i UP_BACK_POS_FIRST = { 0,0 };
	//��̔����w�i�̈ʒu�̉E���̈ʒu
	const tnl::Vector2i UP_BACK_POS_LAST = { 64 * 5,104 };
	//����HP
	const int TANK_HP = 3;
	//�ړ���
	const int MOVE_SPEED = 5;
	//tank�̑傫��
	const float TANK_SIZE = 80;
	//�W�����v��
	const int JUMP_VALUE = 10;
	//�d�͂̏����l
	const float GRAVITY_VALUE = 0.49f;
	//�������S���C��
	const int DEAD_Y = -500;
	//�e�̔��ˉ\��
	const int BULLET_MAX = 5;
	//��]����
	const float ROLLING_TIME = 0.8f;
	//��]�\����
	const float ROTATABLE_TIME = ROLLING_TIME * 2;
	//��]���x
	const int ROLLING_SPEED = 25;
	//hp�����肫�鎞��
	const int HP_ELAPSED_LIMIT = 1;
	//�e�L�X�g�̃J���[�R�[�h
	const int TEXT_COLOR = 0;


	//�}�E�X�ŃN���b�N�������ǂ���
	bool clicked_ = false;
	//1�N���b�N��1����������
	bool shoted_ = false;
	//�}�E�X�̍��W
	tnl::Vector3 mouse_pos_;
	//�}�E�X�ւ̊p�x
	int angle_to_mouse_;
	int blt_count_ = 0;
	//�e�̐���
	bool is_alive_bullet_ = false;
	//��]�̌o�ߎ���
	float rolling_elapsed_ = 0;
	//��]�\���ǂ���
	bool rotatable_;
	//HP�o�[�̉E�[
	float hp_bar_right_ = hp_gauge_pos_.x + DXE_WINDOW_WIDTH / 3;
	//�X�s���o�[�̉E�[
	int spin_bar_right_ = spin_gauge_pos_.x + DXE_WINDOW_WIDTH / 3;
	//��]�̑���
	float rolling_speed_ = 0;
	//hp�o�[�̌o�ߎ���
	float hp_elapsed_ = 0;
	//hp�v�Z��
	bool hp_calc_ = false;
	//hp��0�ɂȂ������ɓ������~�߂�
	bool move_stop_ = false;
	//���S�A�j������ꂽ��
	bool dead_anime_ = false;
	//������1�̊����v�Z��
	bool ride_calc1_ = false;
	//������2�̊����v�Z��
	bool ride_calc2_ = false;
	//������1�ɏ�����u�Ԃ̐�Ԃ̍��W
	float prev_tank_pos1_;
	//������2�ɏ�����u�Ԃ̐�Ԃ̍��W
	float prev_tank_pos2_;
	//�u������1�ɏ�����u�Ԃ̏����ʒu�v���瓮�����A�������̈ړ�����
	float prev_delta_move_floor1_pos_;
	//������2�ɏ�����u�Ԃ́A�����ʒu���瓮�����������̈ړ�����
	float prev_delta_move_floor2_pos_;


	//HP�̉摜�p�X
	int hp_gfx_;
	//�X�s���Q�[�W�̉摜�p�X
	int spin_gfx_;
	//�o�[�̔w�i�摜�p�X
	int hp_back_gfx_;
	//���̔����w�i�̉摜�p�X
	int back_gfx_;
	//�e�̉摜�p�X
	int bullet_gfx_;
	//�_���[�W�̉��y�p�X
	int damage_snd_;
	//��]�̉��y�p�X
	int rolling_snd_;
	//�W�����v�̉��y�p�X
	int jump_snd_;
	//�e�̔��˂̉��y�p�X
	int shot_snd_;

	//--------���C�������--------
	float centroid_radius_ = 20;
	float mass_ = 98;
	//���C
	float friction_ = 1;
	//�����̗�
	tnl::Vector3 move_vel_;
	//1�O�̓����̗�
	tnl::Vector3 past_move_vel_;
	//�d�S
	tnl::Vector3 center_of_gravity_;
	//----------------------------


	std::list<std::shared_ptr<Bullet>> bullet;

};