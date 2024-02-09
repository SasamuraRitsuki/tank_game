#pragma once


class Bullet {
public:
	//座標、向き、向き(度数法の角度)、敵か味方か
	Bullet(const tnl::Vector3& spawn_pos, const tnl::Vector3& move_dir,const int& dir_value,const bool& enemy);

	void update(float delta_time);
	void draw(Shared<dxe::Camera> camera);

	Shared<dxe::Mesh> mesh_ = nullptr;

	//向きの確認
	void DirCheck(bool bullet_reflection);

	//弾の判定用の大きさ
	tnl::Vector3 bullet_size_v;
	//弾が反射されたかどうか
	bool bullet_reflection_ = false;
private:
	//弾の形
	const tnl::Vector3 BULLET_FORM = { 1.0f, 1.0f, 2.0f };
	//弾の大きさ
	const float BULLET_SIZE = 15;
	//弾速
	const int BULLET_SPEED = 10;
	//反射後の弾速
	const int BULLET_REFLECT_SPEED = -2;

	//弾の向き
	int bullet_dir_ = 1;
	//弾の向き(Vector3)
	tnl::Vector3 move_dir_ = { 0,0,0 };

	Shared<dxe::Texture> texture = nullptr;
};