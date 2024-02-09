#pragma once

class SceneBase {
public:
	//cpp‚É‘‚«‚½‚­‚È‚¢‚Ì‚ÅA
	// ‚±‚±‚ÅéŒ¾‚ğI‚í‚ç‚¹‚Ä‚é
	virtual void update(float delta_time) {};
	virtual void draw() = 0;
};