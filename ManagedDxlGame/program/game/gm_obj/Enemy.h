#pragma once
#include "Bullet.h"

class Enemy {
public:
	Enemy(const tnl::Vector3& spawn_pos,const int& dir_angle);
	~Enemy();

	void update(float delta_time);
	void draw(Shared<dxe::Camera> camera);
	Shared<dxe::Mesh> mesh_ = nullptr;

	//壁との当たり判定
	bool TryWallCollision(std::shared_ptr<Bullet> blt);

	//現在のtankの位置
	tnl::Vector3 tank_pos_;
	//tankの判定用の大きさ
	tnl::Vector3 tank_size_v;
	//ジャンプの値
	float jump_value_ = 0;
	//ジャンプ中か
	bool jumped_ = false;
	//残りHP
	int tank_hp_;
	//弾の生存
	bool is_alive_bullet_ = false;
	//hp計算中
	bool hp_calc_ = false;
	//死亡判定
	bool dead_ = false;

	//弾のイテレーター
	std::list<std::shared_ptr<Bullet>>::iterator bullet_it_;
	//弾のリスト
	std::list<std::shared_ptr<Bullet>> bullet;

private:
	//ランダムで向きを変える
	void RandomDirChange();
	//弾の発射の処理
	void BulletShot(float delta_time);
	//戦車への角度計算
	void AngleCalcToTank();
	//弾との当たり判定
	bool TryBulletCollision(std::shared_ptr<Bullet> blt);

	//tankの形
	const tnl::Vector3 TANK_FORM = { 1.0f, 0.75f, 1.0f };
	//初期HP
	const int TANK_HP = 3;
	//移動量
	const int MOVE_SPEED = 3;
	//tankの大きさ
	const float TANK_SIZE = 80;
	//ジャンプ力
	const int JUMP_VALUE = 10;
	//重力の初期値
	const float GRAVITY_VALUE = 0.49f;
	//落下死亡ライン
	const int DEAD_Y = -500;
	//弾の発射可能数
	const int BULLET_MAX = 10;
	//ランダムで向きを変える秒数
	const int DIR_CHANGE_COUNT = 1;
	//弾を撃ってから動き出すまでの秒数
	const int SHOT_INTERVAL = 1;
	//向きの倍率
	const float RANDOM_DIR_POWER = 0.5f;
	//HPバーの長さ
	const int HP_BAR_MAX = 60;
	//hpが減りきる時間
	const int HP_ELAPSED_LIMIT = 1;


	//戦車への距離
	tnl::Vector2i distance_to_tank_;
	//画面上のhpバーの座標
	tnl::Vector3 screen_hp_bar_pos_;
	//弾発射用の秒数のカウント
	float shot_elapsed_ = 0;
	//弾発射のインターバル
	float shot_interval_ = 0;
	//ランダム用の秒数のカウント
	float random_elapsed_ = 0;
	//向く角度の値
	int dir_value_ = 0;
	//向いている角度
	int dir_angle_ = 0;
	//進むか止まるか
	bool go_judge_ = false;
	//弾を発射しているかどうか
	bool shoted_ = false;
	//戦車への角度
	int angle_to_tank_ = 0;
	//HPバーの右端
	float hp_bar_right_ = screen_hp_bar_pos_.x + HP_BAR_MAX;
	//hpバーの経過時間
	float hp_elapsed_ = 0;
	//hpが0になった時に動きを止める
	bool move_stop_ = false;
	//hpバーの長さ
	float hp_bar_length_ = HP_BAR_MAX;
	//弾を撃つまでの秒数
	float shot_count_;

	//HPの画像パス
	int hp_gfx_;
	//バーの背景画像パス
	int hp_back_gfx_;
	//弾の発射の音楽パス
	int shot_snd_;
	//やられた時の音楽パス
	int dead_snd_;
	//反射の音楽パス
	int reflection_snd_;

	//--------摩擦もろもろ--------
	float centroid_radius_ = 20;
	float mass_ = 98;
	//摩擦
	float friction_ = 1;
	//動きの量
	tnl::Vector3 move_vel_;
	//1つ前の動きの量
	tnl::Vector3 past_move_vel_;
	//重心
	tnl::Vector3 center_of_gravity_;
	//----------------------------

};