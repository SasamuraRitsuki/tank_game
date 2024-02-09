#pragma once

#include "../dxlib_ext/dxlib_ext.h"
#include "gm_manager.h"
#include "Scene_base.h"

GM::GM(std::shared_ptr<SceneBase> start_scene):now_scene_(start_scene) {

}

GM::~GM() {

}

GM* GM::GetInstance(std::shared_ptr<SceneBase> start_scene) {
	static GM* gm = nullptr;
	if (!gm) {
		gm = new GM(start_scene);
	}
	return gm;
}

void GM::Destroy() {
	delete GetInstance();
}

// next_scene_‚ðƒZƒbƒg
void GM::changeScene(std::shared_ptr<SceneBase> next_scene) {
	next_scene_ = next_scene;
	now_scene_ = next_scene_;
}


void GM::update(float delta_time) {

	if (now_scene_) { 
		now_scene_->update(delta_time);
		now_scene_->draw(); 
	}
}
