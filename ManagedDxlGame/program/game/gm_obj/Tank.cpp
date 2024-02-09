#pragma once

#define _USE_MATH_DEFINES 
#include <time.h>
#include <iostream>
#include <string>
#include <numbers>
#include <functional>
#include "../dxlib_ext/dxlib_ext.h"
#include "Tank.h"
#include "../gm_mgr/gm_manager.h"
#include "../scene/gm_scene_play.h"
#include "../gm_mgr/resource_manager.h"


Tank::Tank() {
	tank_size_v = TANK_FORM * TANK_SIZE;

	tank_pos_ = FIRST_POS;
	tank_hp_ = TANK_HP;
	mesh_ = dxe::Mesh::CreateBoxMV(tank_size_v,
		dxe::Texture::CreateFromFile("graphics/tank/tank_side.jpg"),
		dxe::Texture::CreateFromFile("graphics/tank/tank_side.jpg"),
		dxe::Texture::CreateFromFile("graphics/tank/tank_up.jpg"),
		dxe::Texture::CreateFromFile("graphics/tank/tank_down.jpg"),
		dxe::Texture::CreateFromFile("graphics/tank/tank_side_front.jpg"),
		dxe::Texture::CreateFromFile("graphics/tank/tank_side_front.jpg")
		);
	mesh_->scl_ = TANK_FORM;
	mesh_->pos_ = FIRST_POS;
	mesh_->setCullingMode(DX_CULLING_RIGHT);

	//回転を可能状態にしておく
	rotatable_ = true;
	//スピンゲージのチャージ
	rolling_elapsed_ = ROTATABLE_TIME;
	//画像を読み込む
	hp_gfx_ = ResourceManager::GetInstance()->loadGraph("graphics/green1.jpg");
	hp_back_gfx_ = ResourceManager::GetInstance()->loadGraph("graphics/black2.jpg");
	spin_gfx_ = ResourceManager::GetInstance()->loadGraph("graphics/yellow1.jpg");
	back_gfx_ = ResourceManager::GetInstance()->loadGraph("graphics/white.bmp");
	//音楽を読み込む
	damage_snd_ = ResourceManager::GetInstance()->loadSound("sound/se/damage_se.mp3");
	rolling_snd_ = ResourceManager::GetInstance()->loadSound("sound/se/rolling.mp3");
	jump_snd_ = ResourceManager::GetInstance()->loadSound("sound/se/jump.mp3");
	shot_snd_ = ResourceManager::GetInstance()->loadSound("sound/se/tank_shot.mp3");


	SetFontSize(50);
}

Tank::~Tank() {

}

void Tank::update(float delta_time) {
	
	auto scene_play = std::dynamic_pointer_cast<ScenePlay>(GM::GetInstance()->getSceneInstance());

	//--------------------------------------動く床に乗った時の処理-------------------------------------------------------

	MoveFloorCalc(scene_play->MOVE_FLOOR1, ride_move_floor1_, ride_calc1_,scene_play->floor_->delta_move_floor1_pos_);
	MoveFloorCalc(scene_play->MOVE_FLOOR2, ride_move_floor2_, ride_calc2_,scene_play->floor_->delta_move_floor2_pos_);
	/*MoveFloorCalc(ride_move_floor2_, ride_calc2_,prev_tank_pos2_,
		prev_delta_move_floor2_pos_, scene_play->floor_->delta_move_floor2_pos_);*/

	//------------------------------------------------移動----------------------------------------------------------------
	//死んだら動けない
	if (tank_hp_ <= 0) move_stop_ = true;

	if (!move_stop_) {
		int Dir_value = 0;
		//右
		if (tnl::Input::IsKeyDown(eKeys::KB_A)) {
			Dir_value -= 90;
		}
		//左
		if (tnl::Input::IsKeyDown(eKeys::KB_D)) {
			Dir_value += 90;
		}
		//手前
		if (tnl::Input::IsKeyDown(eKeys::KB_S)) {
			Dir_value += 180;
		}
		//右奥と左奥と右手前
		if ((tnl::Input::IsKeyDown(eKeys::KB_W) && (tnl::Input::IsKeyDown(eKeys::KB_A) || tnl::Input::IsKeyDown(eKeys::KB_D))) ||
			(tnl::Input::IsKeyDown(eKeys::KB_S) && (tnl::Input::IsKeyDown(eKeys::KB_D)))) {
			Dir_value /= 2;
		}
		//左手前
		if (tnl::Input::IsKeyDown(eKeys::KB_S) && tnl::Input::IsKeyDown(eKeys::KB_A)) {
			Dir_value = -135;
			//右手前左の三方向を押した時は手前方向に
			if (tnl::Input::IsKeyDown(eKeys::KB_D))Dir_value = 180;
		}
		//ボタンが押されてる時は前進処理
		if (tnl::Input::IsKeyDown(eKeys::KB_W) || tnl::Input::IsKeyDown(eKeys::KB_A) || tnl::Input::IsKeyDown(eKeys::KB_S) || tnl::Input::IsKeyDown(eKeys::KB_D)) {

			//奥手前と左右同時押しは停止
			if (!(
				((tnl::Input::IsKeyDown(eKeys::KB_W) && tnl::Input::IsKeyDown(eKeys::KB_S))) ||
				(
					tnl::Input::IsKeyDown(eKeys::KB_A) && tnl::Input::IsKeyDown(eKeys::KB_D) && !(
						(tnl::Input::IsKeyDown(eKeys::KB_W) || tnl::Input::IsKeyDown(eKeys::KB_S))
						)
					)
				))
				//死んでない時に動ける
				if (!dead_)
					DirChange(Dir_value);
		}

		//向いてる向き
		tnl::Vector3 move_dir = tnl::Vector3::TransformCoord({ 0,0,1 }, mesh_->rot_);


		//--------------------------------------弾の発射--------------------------------------------------------

		AngleCalcToMouse();

		if (tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT)) {
			//弾の向きを自機に向ける
			tnl::Vector3 move_dir = tnl::Vector3::TransformCoord({ 0,0,1 },
				tnl::Quaternion::RotationAxis({ 0, 1, 0 }, tnl::ToRadian(angle_to_mouse_)));
			bullet.emplace_back(std::make_shared<Bullet>(tank_pos_, move_dir, angle_to_mouse_, false));

			//効果音
			PlaySoundMem(shot_snd_, DX_PLAYTYPE_BACK);
		}

		//----------------------------------回転する--------------------------------------------------
		if (tnl::Input::IsMouseTrigger(eMouseTrigger::IN_RIGHT) &&	//右クリックが押されて
			rotatable_) {											//回転可能な時に
			rolling_ = true;
			rotatable_ = false;
			rolling_elapsed_ = 0;
			//効果音
			PlaySoundMem(rolling_snd_, DX_PLAYTYPE_BACK);
		}
		if (!rotatable_)TankRolling(delta_time);

		//----------------------------------初期位置に戻る-------------------------------------------
		if (tank_pos_.y <= DEAD_Y ||//落下したら
			damaged_) {				//ダメージ受けたら
			if (tank_hp_ > 1) {//HPが0になった時は初期値に戻らない
				tank_pos_ = FIRST_POS;
				mesh_->rot_ = { 0, 0, 0 ,1 };
				jump_value_ = 0;
			}
			ride_move_floor1_ = false;
			ride_move_floor2_ = false;
			damaged_ = false;
			hp_calc_ = true;
			tank_hp_--;
			//効果音
			PlaySoundMem(damage_snd_, DX_PLAYTYPE_BACK);
		}

		//-------------------------------------ジャンプの処理-------------------------------------------------------
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_SPACE) && !(jumped_)) {
			jump_value_ = JUMP_VALUE;
			jumped_ = true;
			//効果音
			PlaySoundMem(jump_snd_, DX_PLAYTYPE_BACK);
		}
	}
		tank_pos_.y += jump_value_;

		//落下処理
		if (tank_pos_.y > DEAD_Y) {
			jump_value_ -= GRAVITY_VALUE;
		}
		//落下中のジャンプを防ぐ
		if (jump_value_ <= -GRAVITY_VALUE * 2)jumped_ = true;

		if (tank_pos_.y < -10) {
			ride_move_floor1_ = false;
			ride_calc1_ = false;
			ride_move_floor2_ = false;
			ride_calc2_ = false;
		}

//------------------------------------------摩擦などの計算-------------------------------------------------------------------------------------
		tnl::EasyAdjustObjectVelocity(centroid_radius_, mass_, friction_, past_move_vel_, move_vel_, center_of_gravity_);

		
		tank_pos_ += move_vel_ * MOVE_SPEED;
		if (ride_move_floor1_) {
			prev_tank_pos1_ += move_vel_.x * MOVE_SPEED;
		}
		if (ride_move_floor2_) {
			prev_tank_pos2_ += move_vel_.x * MOVE_SPEED;
		}
		//実際にtankの位置をtank_pos_の位置にする。
		mesh_->pos_ = tank_pos_;
	
		//--------------------------------------------------弾の発射など-------------------------------------------------------------------


	auto it = bullet.begin();

	int blt_count = 0;
	while (it != bullet.end()) {
		
		(*it)->update(delta_time);

		// 敵リストを3周
		for (scene_play->enemy_it_ = scene_play->enemy_.begin(); scene_play->enemy_it_ !=
			scene_play->enemy_.end(); ++scene_play->enemy_it_) {

			tnl::Vector3 enemy_pos = scene_play->enemy_it_->get()->tank_pos_;
			tnl::Vector3 enemy_size = scene_play->enemy_it_->get()->tank_size_v;

			// 弾と敵の当たり判定の処理
			if (TryEnemyCollision((*it), enemy_pos, enemy_size)) {
				scene_play->enemy_it_->get()->hp_calc_ = true;
				//敵がhp0の時に当たったら
				if (scene_play->enemy_it_->get()->tank_hp_ > 0) {
					scene_play->enemy_it_->get()->tank_hp_--;
					//効果音
					PlaySoundMem(damage_snd_, DX_PLAYTYPE_BACK);
				}
				is_alive_bullet_ = true;
			}
		}
		if (blt_count >= BULLET_MAX) {
			StopSoundMem(shot_snd_);
		}
		if (
			//TryTargetCollision(*it) ||
			is_alive_bullet_||				//敵に弾が当たったら
			blt_count >= BULLET_MAX ||		//弾の最大値を超えたら
			TryWallCollision(*it) ||		//壁に当たったら
			scene_play->tank_damged_){		//ダメージを食らったら(死んで戻されたときにクリアしたら何か変だから)
			it = bullet.erase(it);
			is_alive_bullet_ = false;
			continue;
		}
		it++;
		blt_count++;
	}
	//--------------------------------------hpバーの処理------------------------------------------------
	if (hp_calc_) {
		hp_elapsed_ += delta_time;
	}
	int next_hp_bar_right = hp_gauge_pos_.x + ((DXE_WINDOW_WIDTH * tank_hp_) / (3 * TANK_HP));

	//hpの減り方に工夫
	hp_bar_right_ = tnl::SmoothLerp(hp_bar_right_, next_hp_bar_right, HP_ELAPSED_LIMIT, hp_elapsed_,0);

	if (hp_elapsed_ >= HP_ELAPSED_LIMIT) {
		hp_calc_ = false;
		hp_elapsed_ = 0;
	}

	//hpが減り切ったら死亡
	if (hp_bar_right_ <= hp_gauge_pos_.x) {
		dead_ = true;
	}

	//死亡の際の顔を入れる
	/*if (!(dead_anime_) && move_stop_) {
		mesh_->setTexture(dxe::Texture::CreateFromFile("graphics/tank/tank_side.jpg"),
			dxe::Texture::CreateFromFile("graphics/tank/tank_side.jpg"),
			dxe::Texture::CreateFromFile("graphics/tank/tank_up.jpg"),
			dxe::Texture::CreateFromFile("graphics/tank/tank_down.jpg"),
			dxe::Texture::CreateFromFile("graphics/tank/tank_side_front.jpg"),
			dxe::Texture::CreateFromFile("graphics/tank/tank_side_front.jpg"));
		dead_anime_ = true;
	}*/
}


void Tank::draw(Shared<dxe::Camera> camera) {

	spin_bar_right_ = 0.5f * rolling_elapsed_*(DXE_WINDOW_WIDTH / (3 * ROLLING_TIME)) + spin_gauge_pos_.x;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	//後ろの白い薄い背景
	DrawExtendGraph(BACK_POS_FIRST.x, BACK_POS_FIRST.y,
		BACK_POS_LAST.x, BACK_POS_LAST.y, back_gfx_, false);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND,255);

	//背景の黒いバー
	DrawExtendGraph(hp_gauge_pos_.x, hp_gauge_pos_.y,
		hp_gauge_pos_.x + DXE_WINDOW_WIDTH / 3, hp_gauge_pos_.y + 40, hp_back_gfx_, false);
	//緑バー
	DrawExtendGraph(hp_gauge_pos_.x, hp_gauge_pos_.y,
		hp_bar_right_, hp_gauge_pos_.y + 40, hp_gfx_,false);

	//背景の黒いバー
	DrawExtendGraph(spin_gauge_pos_.x, spin_gauge_pos_.y,
		spin_gauge_pos_.x + DXE_WINDOW_WIDTH / 3, spin_gauge_pos_.y + 40, hp_back_gfx_, false);
	//黄バー
	DrawExtendGraph(spin_gauge_pos_.x, spin_gauge_pos_.y,
		spin_bar_right_, spin_gauge_pos_.y + 40, spin_gfx_, false);

	//文字表示
	DrawStringEx(HP_TEXT_POS.x, HP_TEXT_POS.y, TEXT_COLOR, "HP");
	DrawStringEx(SPIN_TEXT_POS.x, SPIN_TEXT_POS.y, TEXT_COLOR, "SPIN");
	DrawStringEx(SPIN_CLICK_TEXT_POS.x, SPIN_CLICK_TEXT_POS.y, TEXT_COLOR, "右クリック");

	//DrawStringEx(500, 100, 0x0000ff, "posx = %.2f", tank_pos_.x);
	//DrawStringEx(500, 200, 0x0000ff, "posz = %.2f", tank_pos_.z);


	//DrawStringEx(0, 200, 0x0000ff, "ride_move_floor1_ = %d", ride_move_floor1_);
	//DrawStringEx(0, 250, 0x0000ff, "ride_move_floor2_ = %d", ride_move_floor2_);

	//DrawStringEx(500, 100, 0x00ffff, "pos = %.2f", tank_pos_.x);
	//DrawStringEx(500, 200, 0x00ffff, "prev_tank = %.2f", prev_tank_pos1_);
	////DrawStringEx(500, 300, 0x00ffff, "test = %.2f", test);
	//DrawStringEx(500, 400, 0x00ffff, "prev_floor = %.2f", prev_delta_move_floor1_pos_);
	//DrawStringEx(500, 500, 0x00ffff, "ride_calc_ = %d", ride_calc1_);
	//DrawStringEx(SPIN_CLICK_TEXT_POS.x, SPIN_CLICK_TEXT_POS.y - 200, TEXT_COLOR, "tankpos = %f", tank_pos_.y);
	//if(ride_move_floor_)
	/*DrawStringEx(SPIN_CLICK_TEXT_POS.x, SPIN_CLICK_TEXT_POS.y - 100, TEXT_COLOR, "はい");
	DrawStringEx(SPIN_CLICK_TEXT_POS.x, SPIN_CLICK_TEXT_POS.y - 200, TEXT_COLOR, "%f",tank_pos_.y);*/

	//弾の描画
	mesh_->render(camera);
	for (auto blt : bullet) {
		blt->draw(camera);
	}
}

void Tank::DirChange(int dir) {
	tnl::Quaternion now_rot_ = tnl::Quaternion::RotationAxis({ 0, 1, 0 }, tnl::ToRadian(dir));

	//回転中は見た目はここでは動かさない
	if(!rolling_)
	mesh_->rot_ = now_rot_;

	move_vel_ += tnl::Vector3::TransformCoord({ 0, 0, 1.0f }, now_rot_);
}

void Tank::AngleCalcToMouse() {
	mouse_pos_.x = tnl::Input::GetMousePosition().x - DXE_WINDOW_WIDTH / 2;
	mouse_pos_.y = tnl::Input::GetMousePosition().y - DXE_WINDOW_HEIGHT / 2;

	angle_to_mouse_ = atan2(mouse_pos_.y, mouse_pos_.x) * (180.0 / M_PI) + 90;
}

void Tank::TankRolling(float delta_time) {
	rolling_elapsed_ += delta_time;

	// 正規化
	float normalizedTime = static_cast<float>(rolling_elapsed_) / ROLLING_TIME;

	// イージング関数を適用
	float easedTime = EaseInOut(normalizedTime);

	
	//ぐるぐる回転
	if (rolling_) {
		// y の変化
		rolling_speed_ = easedTime * 30.0f;
		mesh_->rot_ *= tnl::Quaternion::RotationAxis({ 0, 1, 0 }, tnl::ToRadian(rolling_speed_));
	}

	if (rolling_elapsed_ >= ROLLING_TIME && rolling_) {
		rolling_ = false;//回転中をoffに
	}
	if (rolling_elapsed_ >= ROTATABLE_TIME) {
		rolling_elapsed_ = ROTATABLE_TIME;
		rotatable_ = true;//回転可能をonに
	}
}

float Tank::EaseInOut(float t) {
	// t は時間（0.0 から 1.0 の範囲で変化する値）

	
	// 2乗のべき乗を使った急加速から減速への変化
	/*float easedValue = t < 0.5 ? 2.0f * t * t : 1.0f - pow(-2.0f * t + 2.0f, 2) / 2.0f;

	return easedValue;*/

	float easedValue = tnl::DecelLerp(0, 1, 1, t);

	return easedValue;
}

void Tank::MoveFloorCalc(int move_floor_sort, bool ride_move_floor, bool ride_calc,float delta_move_floor_pos) {

	auto scene_play = std::dynamic_pointer_cast<ScenePlay>(GM::GetInstance()->getSceneInstance());

	if (ride_move_floor) {

		if (!ride_calc) {
			if (move_floor_sort == scene_play->MOVE_FLOOR1) {
				prev_tank_pos1_ = tank_pos_.x;
				prev_delta_move_floor1_pos_ = delta_move_floor_pos;
			}
			//if (move_floor_sort == scene_play->MOVE_FLOOR2) {
			else{
				prev_tank_pos2_ = tank_pos_.x;
				prev_delta_move_floor2_pos_ = delta_move_floor_pos;
			}
		}
		if (move_floor_sort == scene_play->MOVE_FLOOR1) {
			ride_calc1_ = true;
		}
		else {
			ride_calc2_ = true;
		}
		
		if (move_floor_sort == scene_play->MOVE_FLOOR1) {
			tank_pos_.x = prev_tank_pos1_ + delta_move_floor_pos - prev_delta_move_floor1_pos_;
		}
		//if (move_floor_sort == scene_play->MOVE_FLOOR2) {
		else {
			tank_pos_.x = prev_tank_pos2_ + delta_move_floor_pos - prev_delta_move_floor2_pos_;
		}
		//test = prev_tank_pos_ + scene_play->floor_->delta_move_floor_pos_ - prev_delta_move_floor_pos_;
	}
	else {
		if (move_floor_sort == scene_play->MOVE_FLOOR1) {
			ride_calc1_ = false;
		}
		else {
			ride_calc2_ = false;
		}
	}
}

bool Tank::TryWallCollision(std::shared_ptr<Bullet> blt) {

	auto scene_play = std::dynamic_pointer_cast<ScenePlay>(GM::GetInstance()->getSceneInstance());

	if (tnl::IsIntersectAABB(blt->mesh_->pos_, blt->bullet_size_v,scene_play->wall_->wall1_mesh_->pos_, scene_play->wall_->wall1_size_v) ||
		tnl::IsIntersectAABB(blt->mesh_->pos_, blt->bullet_size_v, scene_play->wall_->wall2_mesh_->pos_, scene_play->wall_->wall2_size_v) ||
		tnl::IsIntersectAABB(blt->mesh_->pos_, blt->bullet_size_v, scene_play->wall_->wall3_mesh_->pos_, scene_play->wall_->wall3_size_v) ||
		tnl::IsIntersectAABB(blt->mesh_->pos_, blt->bullet_size_v, scene_play->wall_->wall4_mesh_->pos_, scene_play->wall_->wall4_size_v) ||
		tnl::IsIntersectAABB(blt->mesh_->pos_, blt->bullet_size_v, scene_play->wall_->wall5_mesh_->pos_, scene_play->wall_->wall5_size_v)
		) {
		return true;
	}
	else return false;
}

bool Tank::TryEnemyCollision(std::shared_ptr<Bullet> blt, tnl::Vector3 enemy_pos, tnl::Vector3 enemy_size) {

	if (tnl::IsIntersectAABB(enemy_pos, enemy_size, blt->mesh_->pos_, blt->bullet_size_v)
		) {
		return true;
	}
	else return false;
}