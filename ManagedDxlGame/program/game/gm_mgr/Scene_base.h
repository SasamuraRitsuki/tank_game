#pragma once

class SceneBase {
public:
	//cppに書きたくないので、
	// ここで宣言を終わらせてる
	virtual void update(float delta_time) {};
	virtual void draw() = 0;
};