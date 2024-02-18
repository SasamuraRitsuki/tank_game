#pragma once
#include "../gm_mgr/Scene_base.h"
#include "../gm_obj/Tank.h"
#include "../gm_obj/Enemy.h"
#include "../gm_obj/Floor.h"
#include "../gm_obj/Wall.h"
#include "gm_scene_result.h"


class ScenePlay : public SceneBase {
public:
	ScenePlay();
	~ScenePlay();

	void update(float delta_time) override;
	void draw() override;

	//�����蔻����܂Ƃ߂�����
	void CollisionSet();
	//�����蔻����܂Ƃ߂�����(�G�p)
	void CollisionSetEnemy(std::shared_ptr<Enemy> enemy);
	//���Ƃ̓����蔻��
	void FloorCollision(int move_floor, tnl::Vector3 floorpos, tnl::Vector3 floorsize);
	//�ǂƂ̓����蔻��(���@)
	void TankWallCollision(tnl::Vector3 wall_pos, tnl::Vector3 wall_size);
	//�ǂƂ̓����蔻��(�G)
	void EnemyWallCollision(std::shared_ptr<Enemy> enemy,tnl::Vector3 wall_pos, tnl::Vector3 wall_size);

	//�Q�[���N���A�̔���
	bool cleared_ = false;
	//�Q�[���I���̔���
	bool finished_ = false;
	//���@���_���[�W���󂯂����ɓG�̒e�������p�̔���
	//���X�L���h�~
	bool tank_damged_ = false;

	//�G�̃C�e���[�^�[
	std::list<std::shared_ptr<Enemy>>::iterator enemy_it_;

	Shared<Tank> tank_ = nullptr;
	Shared<Wall> wall_ = nullptr;
	Shared<Floor> floor_ = nullptr;
	std::list<std::shared_ptr<Enemy>> enemy_;

	//���̎��
	const enum FLOOR_SORT {
		STOP_FLOOR,
		MOVE_FLOOR1,
		MOVE_FLOOR2
	};
private:
	//���U���g�V�[���̏���
	void ResultSceneProcess(float delta_time);
	
	//�J�����̏����l
	tnl::Vector3 FIRST_CAMERA_POS = { 0, 650, -500 };
	//tnl::Vector3 FIRST_CAMERA_POS = { -200, 300, -300 };
	//1�̖ڂ̓G�̍��W
	const tnl::Vector3 FIRST_ENEMY1_POS = { 1200,0.1f,500 };
	//2�̖ڂ̓G�̍��W
	const tnl::Vector3 FIRST_ENEMY2_POS = { 200,0.1f,2000 };
	//3�̖ڂ̓G�̍��W
	const tnl::Vector3 FIRST_ENEMY3_POS = { 1000,0.1f,2000 };
	//�G1�̏�������
	const int ENEMY1_ANGLE = 270;
	//�G2��3�̏�������
	const int ENEMY2_3_ANGLE = 180;
	//�����w�i�̉摜�̓����x
	const int BACK_GFX_ALPHA = 125;
	//���U���g�V�[���ɓ���܂ł̎���
	const float RESULT_SCENE_CHANGE_COUNT = 0.4f;

	//�Q�[���X�^�[�g�̃t���O
	bool start_ = false;
	//���U���g���Ăяo���t���O
	bool result_start_ = false;

	//���̍����w�i�̉摜�p�X
	int back_gfx_;
	//bgm�̉��y�p�X
	int bgm_snd_;
	//�_���[�W�̉��y�p�X
	int damage_snd_;

	//���U���g�̌o�ߎ���
	float elapsed_ = 0;


	Shared<dxe::Camera> camera_ = nullptr;
	Shared<dxe::Mesh> skybox_ = nullptr;

	Shared<SceneResult>result_ = nullptr;

};