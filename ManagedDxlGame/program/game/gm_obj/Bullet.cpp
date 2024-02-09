#pragma once

#include <time.h>
#include <string>
#include <numbers>
#include <functional>
#include "../dxlib_ext/dxlib_ext.h"
#include "Bullet.h"
#include "../gm_mgr/gm_manager.h"
#include "../scene/gm_scene_play.h"


Bullet::Bullet(const tnl::Vector3& spawn_pos, const tnl::Vector3& move_dir,const int& dir_value, const bool& enemy) {
	//“G‚È‚ç
	if (enemy) {
		texture = dxe::Texture::CreateFromFile("graphics/black1.bmp");
	}
	//–¡•û‚È‚ç
	else {
		texture = dxe::Texture::CreateFromFile("graphics/yellow1.jpg");
	}
	mesh_ = dxe::Mesh::CreateCubeMV(BULLET_SIZE);
	mesh_->setTexture(texture);
	mesh_->scl_ = BULLET_FORM;
	mesh_->pos_ = spawn_pos;
	move_dir_ = move_dir;
	//’e‚Ì•ûŒü‚ðŒ‚‚Á‚½•ûŒü‚É
	mesh_->rot_ = tnl::Quaternion::RotationAxis({ 0, 1, 0 }, tnl::ToRadian(dir_value));

	mesh_->setCullingMode(DX_CULLING_RIGHT);


	bullet_size_v = BULLET_FORM * BULLET_SIZE;

	//’e‚ªo‚Ä‚­‚é‚Æ‚±‚ë‚Í­‚µ‘O‘¤
	mesh_->pos_ += move_dir_ * BULLET_SPEED * 7;
}

void Bullet::update(float delta_time) {

	mesh_->pos_ += move_dir_ * BULLET_SPEED * bullet_dir_;

}

void Bullet::draw(Shared<dxe::Camera> camera) {
	mesh_->render(camera);
}

void Bullet::DirCheck(bool bullet_reflection) {

	if (bullet_reflection) {
		bullet_dir_ = BULLET_REFLECT_SPEED;
		bullet_reflection_ = true;
	}
}