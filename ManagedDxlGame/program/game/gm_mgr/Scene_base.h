#pragma once

class SceneBase {
public:
	//cpp�ɏ��������Ȃ��̂ŁA
	// �����Ő錾���I��点�Ă�
	virtual void update(float delta_time) {};
	virtual void draw() = 0;
};