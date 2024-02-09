//#pragma once
//
//#include <time.h>
//#include <string>
//#include <numbers>
//#include <functional>
//#include "../dxlib_ext/dxlib_ext.h"
//#include "Target.h"
//
//
//
//Target::Target() {
//	mesh_ = dxe::Mesh::CreateCubeMV(TARGET_SIZE);
//	mesh_->setTexture(dxe::Texture::CreateFromFile("graphics/red1.bmp"));
//	mesh_->scl_ = TARGET_FORM;
//	mesh_->pos_ = target_pos_;
//
//	target_size_v = TARGET_FORM * TARGET_SIZE;
//	//”–‚·‚¬‚é‚©‚ç”»’è‘¾‚­
//	target_size_v.z = TARGET_FORM.z * TARGET_SIZE * 3;
//}
//
//Target::~Target() {
//
//}
//
//void Target::update(float delta_time) {
//	timeleft_ += delta_time;
//	
//	target_pos_.x = sin(timeleft_) * 600 + 1200;
//
//	mesh_->pos_ = target_pos_;
//}
//
//void Target::draw(Shared<dxe::Camera> camera) {
//	mesh_->render(camera);
//}