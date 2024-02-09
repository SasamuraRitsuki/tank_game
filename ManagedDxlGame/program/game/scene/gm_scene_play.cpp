#include "../../dxlib_ext/dxlib_ext.h"
#include "gm_scene_result.h"
#include "gm_scene_play.h"
#include "../gm_mgr/gm_manager.h"
#include "../gm_mgr/resource_manager.h"



ScenePlay::ScenePlay() {
	ChangeLightTypeDir(VGet(0.0f, -1.0f, 0.0f)); 
	SetBackgroundColor(50, 50, 50);
	tank_ = std::make_shared<Tank>(); 
	floor_ = std::make_shared<Floor>();
	wall_ = std::make_shared<Wall>();

	camera_ = std::make_shared<dxe::Camera>(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT);

	camera_->pos_ = FIRST_CAMERA_POS;

	//�G�̐���
	enemy_.emplace_back(std::make_shared<Enemy>(FIRST_ENEMY1_POS, ENEMY1_ANGLE));
	enemy_.emplace_back(std::make_shared<Enemy>(FIRST_ENEMY2_POS, ENEMY2_ANGLE));
	enemy_.emplace_back(std::make_shared<Enemy>(FIRST_ENEMY3_POS, ENEMY2_ANGLE));

	SetDefaultLightParameter("directional_light_parameter.bin");

	skybox_ = dxe::Mesh::CreateCubeMV(30000, 20, 20);
	skybox_->setTexture(dxe::Texture::CreateFromFile("graphics/skybox/_skybox_c.png"));
	skybox_->loadMaterial("material.bin");

	skybox_->rot_ = tnl::Quaternion::RotationAxis({ 0, 1, 0 }, tnl::ToRadian(90));
	
	//�摜��ǂݍ���
	//back_gfx_ = ResourceManager::GetInstance()->loadGraph("graphics/white.bmp");
	back_gfx_ = ResourceManager::GetInstance()->loadGraph("graphics/black2.jpg");
	//���y��ǂݍ���
	bgm_snd_ = ResourceManager::GetInstance()->loadSound("sound/bgm/battle_bgm.mp3");
	damage_snd_ = ResourceManager::GetInstance()->loadSound("sound/se/damage_se.mp3");

	PlaySoundMem(bgm_snd_, DX_PLAYTYPE_LOOP);
	//�X�^�[�g�̍��}�i�ꎞ�I�j
	start_ = true;
}

ScenePlay::~ScenePlay() {

}

void ScenePlay::update(float delta_time) {

	if (!finished_) {
		tank_->update(delta_time);

		enemy_it_ = enemy_.begin();
		//�c��̓G�̐�
		int enemy_count = 0;
		while (enemy_it_ != enemy_.end()) {
			if (start_) {
				(*enemy_it_)->update(delta_time);
			}

			CollisionSetEnemy(*enemy_it_);

			// �e���X�g���`�F�b�N
			for ((*enemy_it_)->bullet_it_ = (*enemy_it_)->bullet.begin(); (*enemy_it_)->bullet_it_ !=
				(*enemy_it_)->bullet.end(); ++(*enemy_it_)->bullet_it_) {

				//�e�����˒��̎�
				if ((*enemy_it_)->bullet_it_->get()->bullet_reflection_) {
					// �e�ƓG�̓����蔻��̏���
					if (tnl::IsIntersectAABB((*enemy_it_)->tank_pos_, (*enemy_it_)->tank_size_v, (*enemy_it_)->bullet_it_->get()->mesh_->pos_, (*enemy_it_)->bullet_it_->get()->bullet_size_v)) {

						if ((*enemy_it_)->tank_hp_ > 0) {
							(*enemy_it_)->tank_hp_--;
							//���ʉ�
							PlaySoundMem(damage_snd_, DX_PLAYTYPE_BACK);
						}
						(*enemy_it_)->hp_calc_ = true;
						(*enemy_it_)->is_alive_bullet_ = true;
					}
				}
			}
			
			//�{�̓��m�Ԃ������玩�@���_���[�W
			if (tnl::IsIntersectAABB((*enemy_it_)->tank_pos_, (*enemy_it_)->tank_size_v, tank_->tank_pos_, tank_->tank_size_v)) {
				tank_->damaged_ = true;
				tank_damged_ = true;
				if (tank_->tank_hp_ > 0)
					//���ʉ�
					PlaySoundMem(damage_snd_, DX_PLAYTYPE_BACK);
			}
			if ((*enemy_it_)->dead_) {	//dead�t���O�ŏ���
				enemy_it_ = enemy_.erase(enemy_it_);
				continue;
			}
			enemy_it_++;
			enemy_count++;
		}

		if (enemy_count <= 0) {
			cleared_ = true;
			finished_ = true;
		}


		if (tank_->damaged_ == true)tank_damged_ = true;
		else tank_damged_ = false;

		floor_->update(delta_time);

		wall_->update(delta_time);

		skybox_->rot_ *= tnl::Quaternion::RotationAxis({ 0, 1, 0 }, tnl::ToRadian(0.06f));

		camera_->update();


		CollisionSet();

		draw();

		//DrawStringEx(100, 100, 0, "tank mesh x = %.1f ,y = %.1f ,z = %.1f", tank_->mesh_->pos_.x, tank_->mesh_->pos_.y, tank_->mesh_->pos_.z);


		//�ړ��������̃J�����ʒu
		tnl::Vector3 NEXT_CAMERA_POS = { tank_->mesh_->pos_.x - FIRST_CAMERA_POS.x,FIRST_CAMERA_POS.y,tank_->mesh_->pos_.z + FIRST_CAMERA_POS.z };

		//�J�����Ǐ]
		camera_->pos_ -= (camera_->pos_ - NEXT_CAMERA_POS) * 0.1f;
		camera_->target_ -= (camera_->target_ - tnl::Vector3{ tank_->mesh_->pos_.x, 0,tank_->mesh_->pos_.z }) * 0.1f;

		if (tank_->dead_) {
			finished_ = true;
		}
	}

	//���U���g�ɔ��
	if (finished_ ) {
		/*auto mgr = GM::GetInstance();
			mgr->changeScene(std::make_shared<SceneResult>(cleared_));*/

		//1�x�����s���鏈��
		if (!result_start_) {
			result_start_ = true;

			StopSoundMem(bgm_snd_);
			result_ = std::make_shared<SceneResult>(cleared_);
		}
		//���ʉ�ʂ�update
		result_->update(delta_time);
	}

}

void ScenePlay::draw() {

	skybox_->render(camera_);

	wall_->draw(camera_);

	floor_->draw(camera_);
	
	for (auto enemy : enemy_) {
		enemy->draw(camera_);
	}

	tank_->draw(camera_);

	if (result_start_) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, BACK_GFX_ALPHA);
		//���̔��������w�i
		DrawExtendGraph(0, 0,
			DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT, back_gfx_, false);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		//���ʉ�ʂ�draw
		result_->draw();
	}
}

void ScenePlay::CollisionSet() {

	FloorCollision(FLOOR_SORT::STOP_FLOOR, floor_->floor1_mesh_->pos_, floor_->floor1_size_v);
	FloorCollision(FLOOR_SORT::STOP_FLOOR, floor_->floor2_mesh_->pos_, floor_->floor2_size_v);
	FloorCollision(FLOOR_SORT::MOVE_FLOOR1, floor_->move_floor1_mesh_->pos_, floor_->move_floor_size_v);
	FloorCollision(FLOOR_SORT::MOVE_FLOOR2, floor_->move_floor2_mesh_->pos_, floor_->move_floor_size_v);
	TankWallCollision(wall_->wall1_mesh_->pos_, wall_->wall1_size_v);
	TankWallCollision(wall_->wall2_mesh_->pos_, wall_->wall2_size_v);
	TankWallCollision(wall_->wall3_mesh_->pos_, wall_->wall3_size_v);
	TankWallCollision(wall_->wall4_mesh_->pos_, wall_->wall4_size_v);
	TankWallCollision(wall_->wall5_mesh_->pos_, wall_->wall5_size_v);
}

void ScenePlay::CollisionSetEnemy(std::shared_ptr<Enemy> enemy) {
	EnemyWallCollision(enemy, wall_->wall1_mesh_->pos_, wall_->wall1_size_v);
	EnemyWallCollision(enemy, wall_->wall2_mesh_->pos_, wall_->wall2_size_v);
	EnemyWallCollision(enemy, wall_->wall3_mesh_->pos_, wall_->wall3_size_v);
	EnemyWallCollision(enemy, wall_->wall4_mesh_->pos_, wall_->wall4_size_v);
	EnemyWallCollision(enemy, wall_->wall5_mesh_->pos_, wall_->wall5_size_v);
	EnemyWallCollision(enemy, wall_->wall_virtual_pos_, wall_->wall_virtual_size_v);
}


void ScenePlay::FloorCollision(
	int move_floor,				//�ǂ̏��ɏ���Ă��邩
	tnl::Vector3 floorpos,		//���̍��W
	tnl::Vector3 floorsize) {	//���̑傫���̃T�C�Y

	if (tnl::IsIntersectAABB(tank_->tank_pos_, tank_->tank_size_v, floorpos, floorsize)) {
		//DrawStringEx(100, 400, 0, "�Փ�");

		tnl::eCorrResAABB n = tnl::CorrectPositionAABB(
			tank_->tank_pos_,
			floorpos,
			tank_->tank_size_v,
			floorsize,
			tank_->tank_pos_,
			floorpos,
			tnl::eCorrTypeAABB::PWRFL_B,
			tnl::eCorrTypeAABB::PWRFL_B,
			tnl::eCorrTypeAABB::PWRFL_B, 0.1f);

		//���n���̏���
		if (tnl::eCorrResAABB::UP == n) {
			tank_->jump_value_ = 0;
			tank_->jumped_ = false;			
		
			// �����Ȃ����ɏ������
			if (move_floor == FLOOR_SORT::STOP_FLOOR) {
				tank_->ride_move_floor1_ = false;
				tank_->ride_move_floor2_ = false;
			}
			//������1�ɏ������
			if (move_floor == FLOOR_SORT::MOVE_FLOOR1) {
				tank_->ride_move_floor1_ = true;
				tank_->ride_move_floor2_ = false;
			}
			//������2�ɏ������
			if (move_floor == FLOOR_SORT::MOVE_FLOOR2) {
				tank_->ride_move_floor1_ = false;
				tank_->ride_move_floor2_ = true;
			}
		
		}
		/*if (move_floor) {
			if (tnl::eCorrResAABB::UP == n) {
				tank_->ride_move_floor1_ = true;
				tank_->ride_move_floor2_ = true;
			}
			else {
				tank_->ride_move_floor1_ = false;
				tank_->ride_move_floor2_ = false;
			}				
		}*/
	}
	else {
		if (move_floor) {
			//tank_->ride_move_floor_ = false;
		}

		
	}

	//DrawStringEx(100, 400, 0, "�Փ˂��Ă��Ȃ�");

	tank_->mesh_->pos_.y = tank_->tank_pos_.y;
}


void ScenePlay::TankWallCollision(tnl::Vector3 wall_pos, tnl::Vector3 wall_size) {

	if (tnl::IsIntersectAABB(tank_->tank_pos_, tank_->tank_size_v, wall_pos, wall_size)) {
		//DrawStringEx(100, 400, 0, "�Փ�");

		tnl::eCorrResAABB n = tnl::CorrectPositionAABB(
			tank_->tank_pos_, 
			wall_pos,tank_->tank_size_v, 
			wall_size,
			tank_->tank_pos_, 
			wall_pos,
			tnl::eCorrTypeAABB::PWRFL_B,
			tnl::eCorrTypeAABB::PWRFL_B,
			tnl::eCorrTypeAABB::PWRFL_B,
			0.1f);
	}
}

void ScenePlay::EnemyWallCollision(std::shared_ptr<Enemy> enemy, tnl::Vector3 wall_pos, tnl::Vector3 wall_size) {

	if (tnl::IsIntersectAABB(enemy->tank_pos_, enemy->tank_size_v, wall_pos, wall_size)) {

		tnl::eCorrResAABB n = tnl::CorrectPositionAABB(enemy->tank_pos_,
			wall_pos,
			enemy->tank_size_v,
			wall_size,
			enemy->tank_pos_,
			wall_pos,
			tnl::eCorrTypeAABB::PWRFL_B,
			tnl::eCorrTypeAABB::PWRFL_B,
			tnl::eCorrTypeAABB::PWRFL_B, 0.1f);
	}
}