//#pragma once
//
//class Target {
//public:
//	Target();
//	~Target();
//
//	void update(float delta_time);
//	void draw(Shared<dxe::Camera> camera);
//	Shared<dxe::Mesh> mesh_ = nullptr;
//
//	//判定用の的の大きさ
//	tnl::Vector3 target_size_v;
//private:
//	//的の位置
//	tnl::Vector3 target_pos_ = { 1300,0,500 };
//	//的の形
//	const tnl::Vector3 TARGET_FORM = { 1.0f, 1.0f, 0.2f };
//	//const tnl::Vector3 TARGET_FORM = { 1.0f, 1.0f, 1.0f };
//	const int TARGET_SIZE = 100;
//
//	//経過時間
//	float timeleft_ = 0;
//
//
//};