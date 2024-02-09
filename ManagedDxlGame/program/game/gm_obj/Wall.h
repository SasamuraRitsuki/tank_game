#pragma once

class Wall {
public:
	Wall();
	~Wall();

	void update(float delta_time);
	void draw(Shared<dxe::Camera> camera);

	//壁の3D用のメッシュ
	Shared<dxe::Mesh> wall1_mesh_ = nullptr;
	Shared<dxe::Mesh> wall2_mesh_ = nullptr;
	Shared<dxe::Mesh> wall3_mesh_ = nullptr;
	Shared<dxe::Mesh> wall4_mesh_ = nullptr;
	Shared<dxe::Mesh> wall5_mesh_ = nullptr;
	//Shared<dxe::Mesh> wall_virtual_mesh_ = nullptr;

	//判定用の床の大きさ
	tnl::Vector3 wall1_size_v;
	tnl::Vector3 wall2_size_v;
	tnl::Vector3 wall3_size_v;
	tnl::Vector3 wall4_size_v;
	tnl::Vector3 wall5_size_v;
	tnl::Vector3 wall_virtual_size_v;

	//仮想壁の座標
	tnl::Vector3 wall_virtual_pos_ = { 650,-45,1264 };

private:
	//端の壁の大きさ
	const float WALL_SIZE = 100;

	//--------------------------------壁1左-----------------------------------------
	//壁の形
	const tnl::Vector3 WALL1_FORM = { 1, 5, 27 };
	//壁の座標
	tnl::Vector3 wall1_pos_ = { -250,-45,1050 };

	//--------------------------------壁2右-----------------------------------------
	//壁の形
	const tnl::Vector3 WALL2_FORM = { 1, 5, 27 };
	//壁の座標
	tnl::Vector3 wall2_pos_ = { 1550,-45,1050 };
	//tnl::Vector3 wall2_pos_ = { 1580,-45,1050 };

	//--------------------------------壁3手前-----------------------------------------
	//壁の形
	const tnl::Vector3 WALL3_FORM = { 17, 5, 1 };
	//壁の座標
	tnl::Vector3 wall3_pos_ = { 650,-45,-250 };

	//--------------------------------壁4奥-----------------------------------------
	//壁の形
	const tnl::Vector3 WALL4_FORM = { 17, 5, 1 };
	//壁の座標
	tnl::Vector3 wall4_pos_ = { 650,-45,2350 };
	//tnl::Vector3 wall4_pos_ = { 650,-45,2550 };

	//--------------------------------壁5すぐそこの横壁-----------------------------------------
	//壁の形
	const tnl::Vector3 WALL5_FORM = { 10, 1.4f, 1 };
	//壁の座標
	tnl::Vector3 wall5_pos_ = { 302,50,300 };

	//--------------------------------仮想壁-----------------------------------------
	//壁の形
	const tnl::Vector3 WALL_VIRTUAL_FORM = { 19, 5, 8.4f };

};