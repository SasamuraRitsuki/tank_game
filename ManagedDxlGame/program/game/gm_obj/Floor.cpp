#pragma once

#include <time.h>
#include <string>
#include <numbers>
#include <functional>
#include "../dxlib_ext/dxlib_ext.h"
#include "floor.h"



Floor::Floor() {
	//--------------------------------°1-----------------------------------------
	floor1_mesh_ = dxe::Mesh::CreateCubeMV(FLOOR_SIZE);
	floor1_mesh_->setTexture(dxe::Texture::CreateFromFile("graphics/gray3.jpg"));
	floor1_mesh_->scl_ = FLOOR1_FORM;
	floor1_mesh_->pos_ = floor1_pos_;
	floor1_mesh_->setCullingMode(DX_CULLING_RIGHT);

	floor1_size_v = FLOOR1_FORM * FLOOR_SIZE;
	//--------------------------------°2-----------------------------------------
	floor2_mesh_ = floor1_mesh_->createClone();
	floor2_mesh_->scl_ = FLOOR2_FORM;
	floor2_mesh_->pos_ = floor2_pos_;
	floor2_mesh_->setCullingMode(DX_CULLING_RIGHT);

	floor2_size_v = FLOOR2_FORM * FLOOR_SIZE;
	//--------------------------------“®‚­°1-----------------------------------------
	move_floor1_mesh_ = dxe::Mesh::CreateCubeMV(MOVE_FLOOR_SIZE);
	move_floor1_mesh_->setTexture(dxe::Texture::CreateFromFile("graphics/gray1.jpg"));
	move_floor1_mesh_->scl_ = MOVE_FLOOR_FORM;
	move_floor1_mesh_->pos_ = MOVE_FLOOR1_POS;
	move_floor1_mesh_->setCullingMode(DX_CULLING_RIGHT);
	//--------------------------------“®‚­°2-----------------------------------------
	move_floor2_mesh_ = move_floor1_mesh_->createClone();
	move_floor2_mesh_->scl_ = MOVE_FLOOR_FORM;
	move_floor2_mesh_->pos_ = MOVE_FLOOR2_POS;
	move_floor2_mesh_->setCullingMode(DX_CULLING_RIGHT);


	move_floor_size_v = MOVE_FLOOR_FORM * MOVE_FLOOR_SIZE;
}

Floor::~Floor() {

}

void Floor::update(float delta_time) {
	elapsed_ += delta_time;

	delta_move_floor1_pos_ = sin(elapsed_ * MOVE_FLOOR_SPEED) * MOVE_FLOOR_DISTANCE;

	move_floor1_mesh_->pos_.x = MOVE_FLOOR1_POS.x + delta_move_floor1_pos_;

	delta_move_floor2_pos_ = -sin(elapsed_ * MOVE_FLOOR_SPEED) * MOVE_FLOOR_DISTANCE;

	move_floor2_mesh_->pos_.x = MOVE_FLOOR2_POS.x + delta_move_floor2_pos_;

}

void Floor::draw(Shared<dxe::Camera> camera) {
	floor2_mesh_->render(camera);

	move_floor2_mesh_->render(camera);

	move_floor1_mesh_->render(camera);

	floor1_mesh_->render(camera);
}
