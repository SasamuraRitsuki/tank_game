#pragma once

class Floor {
public:
	Floor();
	~Floor();

	void update(float delta_time);
	void draw(Shared<dxe::Camera> camera);

	//床の3D用のメッシュ
	Shared<dxe::Mesh> floor1_mesh_ = nullptr;
	Shared<dxe::Mesh> floor2_mesh_ = nullptr;
	Shared<dxe::Mesh> move_floor1_mesh_ = nullptr;
	Shared<dxe::Mesh> move_floor2_mesh_ = nullptr;

	//判定用の床の大きさ
	tnl::Vector3 floor1_size_v;
	tnl::Vector3 floor2_size_v;
	tnl::Vector3 move_floor_size_v;

	//初期位置から動いた動く床の移動距離
	float delta_move_floor1_pos_ = 0;
	float delta_move_floor2_pos_ = 0;
private:
	//床の大きさ
	const float FLOOR_SIZE = 1000;
	//動く床の大きさ
	const float MOVE_FLOOR_SIZE = 250;

	//--------------------------------床1(手前)-----------------------------------------
	//床の形
	const tnl::Vector3 FLOOR1_FORM = { 1.7f, 0.25f, 1 };
	//床の座標
	tnl::Vector3 floor1_pos_ = { 650,-155,300 };
	//--------------------------------床2(奥)-----------------------------------------
	//床の形
	const tnl::Vector3 FLOOR2_FORM = { 1.7f, 0.25f, 0.575f };
	//床の座標
	tnl::Vector3 floor2_pos_ = { 650,-155,2012.4f };
	//--------------------------------動く床-----------------------------------------
	//床の形
	const tnl::Vector3 MOVE_FLOOR_FORM = { 1, 0.25f, 1 };
	//床がどのくらい動くか
	const int MOVE_FLOOR_DISTANCE = 600;
	//床がどれくらいの速さで動くか
	const float MOVE_FLOOR_SPEED = 0.5f;
	//--------------------------------動く床1(手前)-----------------------------------------
	//床の初期座標
	tnl::Vector3 MOVE_FLOOR1_POS = { 650,-61,1050 };
	//床の座標
	tnl::Vector3 move_floor1_pos_ = MOVE_FLOOR1_POS;
	//--------------------------------動く床2(奥)-----------------------------------------
	//床の初期座標
	tnl::Vector3 MOVE_FLOOR2_POS = { 650,-61,1400 };
	//床の座標
	tnl::Vector3 move_floor2_pos_ = MOVE_FLOOR2_POS;



	//経過時間
	float elapsed_ = 0;
};