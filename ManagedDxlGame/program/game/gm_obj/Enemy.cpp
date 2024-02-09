#pragma once

#define _USE_MATH_DEFINES
#include <time.h>
#include <iostream>
#include <string>
#include <numbers>
#include <functional>
#include "../dxlib_ext/dxlib_ext.h"
#include "Enemy.h"
#include "../gm_mgr/gm_manager.h"
#include "../scene/gm_scene_play.h"
#include "../gm_mgr/resource_manager.h"


Enemy::Enemy(const tnl::Vector3& spawn_pos, const int& dir_angle) {
	tank_size_v = TANK_FORM * TANK_SIZE;
	tank_pos_ = spawn_pos;
	dir_angle_ = dir_angle;

	mesh_ = dxe::Mesh::CreateBoxMV(tank_size_v,
		dxe::Texture::CreateFromFile("graphics/tank/enemy_tank_side.jpg"),
		dxe::Texture::CreateFromFile("graphics/tank/enemy_tank_side.jpg"),
		dxe::Texture::CreateFromFile("graphics/tank/enemy_tank_up.jpg"),
		dxe::Texture::CreateFromFile("graphics/tank/enemy_tank_down.jpg"),
		dxe::Texture::CreateFromFile("graphics/tank/enemy_tank_side_front.jpg"),
		dxe::Texture::CreateFromFile("graphics/tank/enemy_tank_side_front.jpg")
	);
	mesh_->scl_ = TANK_FORM;
	mesh_->pos_ = spawn_pos;
	mesh_->setCullingMode(DX_CULLING_RIGHT);

	//�ŏ��Ɉ�񃉃��_���œ�����
	RandomDirChange();

	//hp�̐ݒ�
	tank_hp_ = TANK_HP;

	//�e�����Ԋu�̒��I
	shot_count_ = 3 + (((rand() % 20) + 1)* 0.1f);

	//�摜�f�[�^��ǂݍ���
	hp_gfx_ = ResourceManager::GetInstance()->loadGraph("graphics/green1.jpg");
	hp_back_gfx_ = ResourceManager::GetInstance()->loadGraph("graphics/black2.jpg");
	//���y�f�[�^��ǂݍ���
	shot_snd_ = ResourceManager::GetInstance()->loadSound("sound/se/enemy_shot.mp3");
	dead_snd_ = ResourceManager::GetInstance()->loadSound("sound/se/enemy_dead.mp3");
	reflection_snd_ = ResourceManager::GetInstance()->loadSound("sound/se/reflection_shot.mp3");

}

Enemy::~Enemy() {
	//���ʉ�
	PlaySoundMem(dead_snd_, DX_PLAYTYPE_BACK);
}

void Enemy::update(float delta_time) {

	//���񂾂瓮���Ȃ�
	if (tank_hp_ <= 0 && !move_stop_) {
		move_stop_ = true;
	}
		

	if (!move_stop_) {
		//�e���˒��ȊO�Ŏ��Ԍo��
		if (!shoted_) {
			random_elapsed_ += delta_time;
			shot_elapsed_ += delta_time;
		}

		if (random_elapsed_ >= DIR_CHANGE_COUNT) {
			RandomDirChange();
			random_elapsed_ = 0;
		}
		dir_angle_ += dir_value_;

		//����
		if (!shoted_)
			mesh_->rot_ = tnl::Quaternion::RotationAxis({ 0, 1, 0 }, tnl::ToRadian(dir_angle_));
		//�i��
		if (go_judge_ && !shoted_)
			move_vel_ += tnl::Vector3::TransformCoord({ 0, 0, 1.0f }, mesh_->rot_);


		//--------------------------------------�e�̔���--------------------------------------------------------
		AngleCalcToTank();

		if (shot_elapsed_ >= shot_count_) {


			//�e�̌��������@�Ɍ�����
			tnl::Vector3 move_dir = tnl::Vector3::TransformCoord({ 0,0,1 },
				tnl::Quaternion::RotationAxis({ 0, 1, 0 }, tnl::ToRadian(angle_to_tank_)));
			//���������@�Ɍ�����
			mesh_->rot_ = tnl::Quaternion::RotationAxis({ 0, 1, 0 }, tnl::ToRadian(angle_to_tank_));

			//�e����
			bullet.emplace_back(std::make_shared<Bullet>(tank_pos_, move_dir, angle_to_tank_, true));
			shot_elapsed_ = 0;
			shoted_ = true;
			//���ʉ�
			PlaySoundMem(shot_snd_, DX_PLAYTYPE_BACK);

			//�e�����Ԋu�̒��I
			shot_count_ = 3 + (((rand() % 20) + 1) * 0.1f);

		}
		BulletShot(delta_time);



		//���C�Ȃǂ̌v�Z
		tnl::EasyAdjustObjectVelocity(centroid_radius_, mass_, friction_, past_move_vel_, move_vel_, center_of_gravity_);


		tank_pos_ += move_vel_ * MOVE_SPEED;
		//���ۂ�tank�̈ʒu��tank_pos_�̈ʒu�ɂ���B
		mesh_->pos_ = tank_pos_;
	}


	auto scene_play = std::dynamic_pointer_cast<ScenePlay>(GM::GetInstance()->getSceneInstance());
	bool tank_damaded = scene_play->tank_damged_;

	bullet_it_ = bullet.begin();
	while (bullet_it_ != bullet.end()) {

		(*bullet_it_)->update(delta_time);

		bool bullet_reflection = false;
		//�e�����@�Ɠ���������
		if (TryBulletCollision(*bullet_it_)) {
			//��]���Ă�����
			if (scene_play->tank_->rolling_) {
				bullet_reflection = true;
				//���ʉ�
				PlaySoundMem(reflection_snd_, DX_PLAYTYPE_BACK);
			}
			else
				//���@���_���[�W
				scene_play->tank_->damaged_ = true;
		}
		(*bullet_it_)->DirCheck(bullet_reflection);

		if (TryWallCollision(*bullet_it_) ||	//�ǂɓ���������
			scene_play->tank_damged_ ||			//���@���_���[�W���󂯂���
			is_alive_bullet_) {					//�G�ɒe������������

			bullet_it_ = bullet.erase(bullet_it_);
			is_alive_bullet_ = false;
			continue;
		}
		bullet_it_++;
	}

	//--------------------------------------hp�o�[�̏���------------------------------------------------
	if (hp_calc_) {
		hp_elapsed_ += delta_time;
	}

	//hp������؂����玀�S
	if (hp_bar_right_ <= screen_hp_bar_pos_.x) {
		dead_ = true;
	}

}


void Enemy::draw(Shared<dxe::Camera> camera) {

	screen_hp_bar_pos_ = tnl::Vector3::ConvertToScreen(
	{ mesh_->pos_.x - (HP_BAR_MAX/2), 100, mesh_->pos_.z}
	, DXE_WINDOW_WIDTH
		, DXE_WINDOW_HEIGHT
		, camera->view_
		, camera->proj_);

	int next_hp_bar_length = HP_BAR_MAX - ((tank_hp_ - TANK_HP) * -(HP_BAR_MAX / TANK_HP));

	//hp�̌�����ɍH�v
	hp_bar_length_ = tnl::SmoothLerp(hp_bar_length_, next_hp_bar_length, HP_ELAPSED_LIMIT, hp_elapsed_, 0);

	hp_bar_right_ = screen_hp_bar_pos_.x + hp_bar_length_;

	if (hp_elapsed_ >= HP_ELAPSED_LIMIT) {
		hp_calc_ = false;
		hp_elapsed_ = 0;
	}
	//�w�i�̍����o�[
	DrawExtendGraph(screen_hp_bar_pos_.x, screen_hp_bar_pos_.y,
		screen_hp_bar_pos_.x + HP_BAR_MAX, screen_hp_bar_pos_.y + 10, hp_back_gfx_, false);
	//�΃o�[
	DrawExtendGraph(screen_hp_bar_pos_.x, screen_hp_bar_pos_.y,
		hp_bar_right_, screen_hp_bar_pos_.y + 10, hp_gfx_, false);


	mesh_->render(camera);
	for (auto blt : bullet) {
		blt->draw(camera);
	}
}

void Enemy::RandomDirChange() {
	dir_value_ = ((rand() % 5) - 2) * RANDOM_DIR_POWER;
	go_judge_ = rand() % 2;
}

void Enemy::AngleCalcToTank() {
	auto scene_play = std::dynamic_pointer_cast<ScenePlay>(GM::GetInstance()->getSceneInstance());
	distance_to_tank_.x = tank_pos_.x - scene_play->tank_->tank_pos_.x;
	distance_to_tank_.y = tank_pos_.z - scene_play->tank_->tank_pos_.z;

	//b = atan2(distance_to_tank_.x,distance_to_tank_.y);

	angle_to_tank_ = atan2(distance_to_tank_.x, distance_to_tank_.y) * (180.0 / M_PI) + 180;
}

void Enemy::BulletShot(float delta_time) {
	if (shoted_) {
		shot_interval_ += delta_time;

		if (shot_interval_ >= SHOT_INTERVAL) {
			shoted_ = false;
			shot_interval_ = 0;
		}

	}
}

bool Enemy::TryWallCollision(std::shared_ptr<Bullet> blt) {

	auto scene_play = std::dynamic_pointer_cast<ScenePlay>(GM::GetInstance()->getSceneInstance());

	if (tnl::IsIntersectAABB(blt->mesh_->pos_, blt->bullet_size_v, scene_play->wall_->wall1_mesh_->pos_, scene_play->wall_->wall1_size_v) ||
		tnl::IsIntersectAABB(blt->mesh_->pos_, blt->bullet_size_v, scene_play->wall_->wall2_mesh_->pos_, scene_play->wall_->wall2_size_v) ||
		tnl::IsIntersectAABB(blt->mesh_->pos_, blt->bullet_size_v, scene_play->wall_->wall3_mesh_->pos_, scene_play->wall_->wall3_size_v) ||
		tnl::IsIntersectAABB(blt->mesh_->pos_, blt->bullet_size_v, scene_play->wall_->wall4_mesh_->pos_, scene_play->wall_->wall4_size_v)||
		tnl::IsIntersectAABB(blt->mesh_->pos_, blt->bullet_size_v, scene_play->wall_->wall5_mesh_->pos_, scene_play->wall_->wall5_size_v)
		) {
		return true;
	}
	else return false;
}

bool Enemy::TryBulletCollision(std::shared_ptr<Bullet> blt) {

	auto scene_play = std::dynamic_pointer_cast<ScenePlay>(GM::GetInstance()->getSceneInstance());

	if (tnl::IsIntersectAABB(blt->mesh_->pos_, blt->bullet_size_v, scene_play->tank_->tank_pos_, scene_play->tank_->tank_size_v)
		) {
		return true;
	}
	else return false;
}