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

	//最初に一回ランダムで動かす
	RandomDirChange();

	//hpの設定
	tank_hp_ = TANK_HP;

	//弾を撃つ間隔の抽選
	shot_count_ = 3 + (((rand() % 20) + 1)* 0.1f);

	//画像データを読み込む
	hp_gfx_ = ResourceManager::GetInstance()->loadGraph("graphics/green1.jpg");
	hp_back_gfx_ = ResourceManager::GetInstance()->loadGraph("graphics/black2.jpg");
	//音楽データを読み込む
	shot_snd_ = ResourceManager::GetInstance()->loadSound("sound/se/enemy_shot.mp3");
	dead_snd_ = ResourceManager::GetInstance()->loadSound("sound/se/enemy_dead.mp3");
	reflection_snd_ = ResourceManager::GetInstance()->loadSound("sound/se/reflection_shot.mp3");

}

Enemy::~Enemy() {
	//効果音
	PlaySoundMem(dead_snd_, DX_PLAYTYPE_BACK);
}

void Enemy::update(float delta_time) {

	//死んだら動けない
	if (tank_hp_ <= 0 && !move_stop_) {
		move_stop_ = true;
	}
		

	if (!move_stop_) {
		//弾発射中以外で時間経過
		if (!shoted_) {
			random_elapsed_ += delta_time;
			shot_elapsed_ += delta_time;
		}

		if (random_elapsed_ >= DIR_CHANGE_COUNT) {
			RandomDirChange();
			random_elapsed_ = 0;
		}
		dir_angle_ += dir_value_;

		//向き
		if (!shoted_)
			mesh_->rot_ = tnl::Quaternion::RotationAxis({ 0, 1, 0 }, tnl::ToRadian(dir_angle_));
		//進み
		if (go_judge_ && !shoted_)
			move_vel_ += tnl::Vector3::TransformCoord({ 0, 0, 1.0f }, mesh_->rot_);


		//--------------------------------------弾の発射--------------------------------------------------------
		AngleCalcToTank();

		if (shot_elapsed_ >= shot_count_) {


			//弾の向きを自機に向ける
			tnl::Vector3 move_dir = tnl::Vector3::TransformCoord({ 0,0,1 },
				tnl::Quaternion::RotationAxis({ 0, 1, 0 }, tnl::ToRadian(angle_to_tank_)));
			//向きを自機に向ける
			mesh_->rot_ = tnl::Quaternion::RotationAxis({ 0, 1, 0 }, tnl::ToRadian(angle_to_tank_));

			//弾生成
			bullet.emplace_back(std::make_shared<Bullet>(tank_pos_, move_dir, angle_to_tank_, true));
			shot_elapsed_ = 0;
			shoted_ = true;
			//効果音
			PlaySoundMem(shot_snd_, DX_PLAYTYPE_BACK);

			//弾を撃つ間隔の抽選
			shot_count_ = 3 + (((rand() % 20) + 1) * 0.1f);

		}
		BulletShot(delta_time);



		//摩擦などの計算
		tnl::EasyAdjustObjectVelocity(centroid_radius_, mass_, friction_, past_move_vel_, move_vel_, center_of_gravity_);


		tank_pos_ += move_vel_ * MOVE_SPEED;
		//実際にtankの位置をtank_pos_の位置にする。
		mesh_->pos_ = tank_pos_;
	}


	auto scene_play = std::dynamic_pointer_cast<ScenePlay>(GM::GetInstance()->getSceneInstance());
	bool tank_damaded = scene_play->tank_damged_;

	bullet_it_ = bullet.begin();
	while (bullet_it_ != bullet.end()) {

		(*bullet_it_)->update(delta_time);

		bool bullet_reflection = false;
		//弾が自機と当たった時
		if (TryBulletCollision(*bullet_it_)) {
			//回転していたら
			if (scene_play->tank_->rolling_) {
				bullet_reflection = true;
				//効果音
				PlaySoundMem(reflection_snd_, DX_PLAYTYPE_BACK);
			}
			else
				//自機がダメージ
				scene_play->tank_->damaged_ = true;
		}
		(*bullet_it_)->DirCheck(bullet_reflection);

		if (TryWallCollision(*bullet_it_) ||	//壁に当たったら
			scene_play->tank_damged_ ||			//自機がダメージを受けたら
			is_alive_bullet_) {					//敵に弾が当たったら

			bullet_it_ = bullet.erase(bullet_it_);
			is_alive_bullet_ = false;
			continue;
		}
		bullet_it_++;
	}

	//--------------------------------------hpバーの処理------------------------------------------------
	if (hp_calc_) {
		hp_elapsed_ += delta_time;
	}

	//hpが減り切ったら死亡
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

	//hpの減り方に工夫
	hp_bar_length_ = tnl::SmoothLerp(hp_bar_length_, next_hp_bar_length, HP_ELAPSED_LIMIT, hp_elapsed_, 0);

	hp_bar_right_ = screen_hp_bar_pos_.x + hp_bar_length_;

	if (hp_elapsed_ >= HP_ELAPSED_LIMIT) {
		hp_calc_ = false;
		hp_elapsed_ = 0;
	}
	//背景の黒いバー
	DrawExtendGraph(screen_hp_bar_pos_.x, screen_hp_bar_pos_.y,
		screen_hp_bar_pos_.x + HP_BAR_MAX, screen_hp_bar_pos_.y + 10, hp_back_gfx_, false);
	//緑バー
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