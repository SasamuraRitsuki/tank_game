#pragma once
#include "Bullet.h"

class Enemy {
public:
	Enemy(const tnl::Vector3& spawn_pos,const int& dir_angle);
	~Enemy();

	void update(float delta_time);
	void draw(Shared<dxe::Camera> camera);
	Shared<dxe::Mesh> mesh_ = nullptr;

	//�ǂƂ̓����蔻��
	bool TryWallCollision(std::shared_ptr<Bullet> blt);

	//���݂�tank�̈ʒu
	tnl::Vector3 tank_pos_;
	//tank�̔���p�̑傫��
	tnl::Vector3 tank_size_v;
	//�W�����v�̒l
	float jump_value_ = 0;
	//�W�����v����
	bool jumped_ = false;
	//�c��HP
	int tank_hp_;
	//�e�̐���
	bool is_alive_bullet_ = false;
	//hp�v�Z��
	bool hp_calc_ = false;
	//���S����
	bool dead_ = false;

	//�e�̃C�e���[�^�[
	std::list<std::shared_ptr<Bullet>>::iterator bullet_it_;
	//�e�̃��X�g
	std::list<std::shared_ptr<Bullet>> bullet;

private:
	//�����_���Ō�����ς���
	void RandomDirChange();
	//�e�̔��˂̏���
	void BulletShot(float delta_time);
	//��Ԃւ̊p�x�v�Z
	void AngleCalcToTank();
	//�e�Ƃ̓����蔻��
	bool TryBulletCollision(std::shared_ptr<Bullet> blt);

	//tank�̌`
	const tnl::Vector3 TANK_FORM = { 1.0f, 0.75f, 1.0f };
	//����HP
	const int TANK_HP = 3;
	//�ړ���
	const int MOVE_SPEED = 3;
	//tank�̑傫��
	const float TANK_SIZE = 80;
	//�W�����v��
	const int JUMP_VALUE = 10;
	//�d�͂̏����l
	const float GRAVITY_VALUE = 0.49f;
	//�������S���C��
	const int DEAD_Y = -500;
	//�e�̔��ˉ\��
	const int BULLET_MAX = 10;
	//�����_���Ō�����ς���b��
	const int DIR_CHANGE_COUNT = 1;
	//�e�������Ă��瓮���o���܂ł̕b��
	const int SHOT_INTERVAL = 1;
	//�����̔{��
	const float RANDOM_DIR_POWER = 0.5f;
	//HP�o�[�̒���
	const int HP_BAR_MAX = 60;
	//hp�����肫�鎞��
	const int HP_ELAPSED_LIMIT = 1;


	//��Ԃւ̋���
	tnl::Vector2i distance_to_tank_;
	//��ʏ��hp�o�[�̍��W
	tnl::Vector3 screen_hp_bar_pos_;
	//�e���˗p�̕b���̃J�E���g
	float shot_elapsed_ = 0;
	//�e���˂̃C���^�[�o��
	float shot_interval_ = 0;
	//�����_���p�̕b���̃J�E���g
	float random_elapsed_ = 0;
	//�����p�x�̒l
	int dir_value_ = 0;
	//�����Ă���p�x
	int dir_angle_ = 0;
	//�i�ނ��~�܂邩
	bool go_judge_ = false;
	//�e�𔭎˂��Ă��邩�ǂ���
	bool shoted_ = false;
	//��Ԃւ̊p�x
	int angle_to_tank_ = 0;
	//HP�o�[�̉E�[
	float hp_bar_right_ = screen_hp_bar_pos_.x + HP_BAR_MAX;
	//hp�o�[�̌o�ߎ���
	float hp_elapsed_ = 0;
	//hp��0�ɂȂ������ɓ������~�߂�
	bool move_stop_ = false;
	//hp�o�[�̒���
	float hp_bar_length_ = HP_BAR_MAX;
	//�e�����܂ł̕b��
	float shot_count_;

	//HP�̉摜�p�X
	int hp_gfx_;
	//�o�[�̔w�i�摜�p�X
	int hp_back_gfx_;
	//�e�̔��˂̉��y�p�X
	int shot_snd_;
	//���ꂽ���̉��y�p�X
	int dead_snd_;
	//���˂̉��y�p�X
	int reflection_snd_;

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

};