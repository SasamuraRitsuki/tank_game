#pragma once
#include "Bullet.h"

class Tank {
public:
	Tank();
	~Tank();

	void update(float delta_time);
	void draw(Shared<dxe::Camera> camera);
	Shared<dxe::Mesh> mesh_ = nullptr;

	//壁との当たり判定
	bool TryWallCollision(std::shared_ptr<Bullet> blt);
	//敵と弾の当たり判定
	bool TryEnemyCollision(std::shared_ptr<Bullet> blt, tnl::Vector3 enemy_pos, tnl::Vector3 enemy_size);


	//現在のtankの位置
	tnl::Vector3 tank_pos_;
	//tankの判定用の大きさ
	tnl::Vector3 tank_size_v;
	//ジャンプの値
	float jump_value_ = 0;
	//ジャンプ中か
	bool jumped_ = false;
	//ダメージを受けた
	bool damaged_ = false;
	//残りHP
	int tank_hp_;
	//回転中
	bool rolling_ = false;
	//死亡判定
	bool dead_ = false;
	//動き床1に乗っているかどうか
	bool ride_move_floor1_ = false;
	//動き床2に乗っているかどうか
	bool ride_move_floor2_ = false;

private:
	//向きを変える
	void DirChange(int dir);
	//マウスへの角度計算
	void AngleCalcToMouse();
	//回転する
	void TankRolling(float delta_time);
	//加減速計算
	float EaseInOut(float t);
	//床の処理計算
	void MoveFloorCalc(int move_floor_sort,bool ride_move_floor,bool ride_calc,float delta_move_floor_pos);

	//スタート位置
	const tnl::Vector3 FIRST_POS = { 0,50,0 };
	//const tnl::Vector3 FIRST_POS = { 0,50,2000 };
	//tankの形
	const tnl::Vector3 TANK_FORM = { 1.0f, 0.75f, 1.0f };
	//弾の画像の位置と大きさ
	const tnl::Vector3 BULLET_POS = { 32, 50, 0.8f };
	//HPのゲージ位置
	const tnl::Vector2i hp_gauge_pos_ = { DXE_WINDOW_WIDTH / 3 ,DXE_WINDOW_HEIGHT * 4 / 5 };
	//スピンゲージ位置
	const tnl::Vector2i spin_gauge_pos_ = { hp_gauge_pos_.x ,hp_gauge_pos_.y + 60 };
	//テキストの位置
	const tnl::Vector2i HP_TEXT_POS = { hp_gauge_pos_.x - 90, hp_gauge_pos_.y };
	const tnl::Vector2i SPIN_TEXT_POS = { spin_gauge_pos_.x - 150, spin_gauge_pos_.y - 5 };
	const tnl::Vector2i SPIN_CLICK_TEXT_POS = { SPIN_TEXT_POS.x + 600, SPIN_TEXT_POS.y };
	//下の白い背景の位置の左上の位置
	const tnl::Vector2i DOWN_BACK_POS_FIRST = { 140,hp_gauge_pos_.y - 20 };
	//下の白い背景の位置の右下の位置
	const tnl::Vector2i DOWN_BACK_POS_LAST = { DXE_WINDOW_WIDTH - 140,spin_gauge_pos_.y + 60 };
	//上の白い背景の位置の左上の位置
	const tnl::Vector2i UP_BACK_POS_FIRST = { 0,0 };
	//上の白い背景の位置の右下の位置
	const tnl::Vector2i UP_BACK_POS_LAST = { 64 * 5,104 };
	//初期HP
	const int TANK_HP = 3;
	//移動量
	const int MOVE_SPEED = 5;
	//tankの大きさ
	const float TANK_SIZE = 80;
	//ジャンプ力
	const int JUMP_VALUE = 10;
	//重力の初期値
	const float GRAVITY_VALUE = 0.49f;
	//落下死亡ライン
	const int DEAD_Y = -500;
	//弾の発射可能数
	const int BULLET_MAX = 5;
	//回転時間
	const float ROLLING_TIME = 0.8f;
	//回転可能時間
	const float ROTATABLE_TIME = ROLLING_TIME * 2;
	//回転速度
	const int ROLLING_SPEED = 25;
	//hpが減りきる時間
	const int HP_ELAPSED_LIMIT = 1;
	//テキストのカラーコード
	const int TEXT_COLOR = 0;


	//マウスでクリックしたかどうか
	bool clicked_ = false;
	//1クリックで1発撃ったか
	bool shoted_ = false;
	//マウスの座標
	tnl::Vector3 mouse_pos_;
	//マウスへの角度
	int angle_to_mouse_;
	int blt_count_ = 0;
	//弾の生存
	bool is_alive_bullet_ = false;
	//回転の経過時間
	float rolling_elapsed_ = 0;
	//回転可能かどうか
	bool rotatable_;
	//HPバーの右端
	float hp_bar_right_ = hp_gauge_pos_.x + DXE_WINDOW_WIDTH / 3;
	//スピンバーの右端
	int spin_bar_right_ = spin_gauge_pos_.x + DXE_WINDOW_WIDTH / 3;
	//回転の速さ
	float rolling_speed_ = 0;
	//hpバーの経過時間
	float hp_elapsed_ = 0;
	//hp計算中
	bool hp_calc_ = false;
	//hpが0になった時に動きを止める
	bool move_stop_ = false;
	//死亡アニメを入れたか
	bool dead_anime_ = false;
	//動く床1の慣性計算中
	bool ride_calc1_ = false;
	//動く床2の慣性計算中
	bool ride_calc2_ = false;
	//動く床1に乗った瞬間の戦車の座標
	float prev_tank_pos1_;
	//動く床2に乗った瞬間の戦車の座標
	float prev_tank_pos2_;
	//「動く床1に乗った瞬間の初期位置」から動いた、動く床の移動距離
	float prev_delta_move_floor1_pos_;
	//動く床2に乗った瞬間の、初期位置から動いた動く床の移動距離
	float prev_delta_move_floor2_pos_;


	//HPの画像パス
	int hp_gfx_;
	//スピンゲージの画像パス
	int spin_gfx_;
	//バーの背景画像パス
	int hp_back_gfx_;
	//後ろの白い背景の画像パス
	int back_gfx_;
	//弾の画像パス
	int bullet_gfx_;
	//ダメージの音楽パス
	int damage_snd_;
	//回転の音楽パス
	int rolling_snd_;
	//ジャンプの音楽パス
	int jump_snd_;
	//弾の発射の音楽パス
	int shot_snd_;

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


	std::list<std::shared_ptr<Bullet>> bullet;

};