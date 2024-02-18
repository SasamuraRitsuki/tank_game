#pragma once
#include "../gm_mgr/Scene_base.h"
#include "../gm_obj/Tank.h"
#include "../gm_obj/Enemy.h"
#include "../gm_obj/Floor.h"
#include "../gm_obj/Wall.h"
#include "gm_scene_result.h"


class ScenePlay : public SceneBase {
public:
	ScenePlay();
	~ScenePlay();

	void update(float delta_time) override;
	void draw() override;

	//当たり判定をまとめたもの
	void CollisionSet();
	//当たり判定をまとめたもの(敵用)
	void CollisionSetEnemy(std::shared_ptr<Enemy> enemy);
	//床との当たり判定
	void FloorCollision(int move_floor, tnl::Vector3 floorpos, tnl::Vector3 floorsize);
	//壁との当たり判定(自機)
	void TankWallCollision(tnl::Vector3 wall_pos, tnl::Vector3 wall_size);
	//壁との当たり判定(敵)
	void EnemyWallCollision(std::shared_ptr<Enemy> enemy,tnl::Vector3 wall_pos, tnl::Vector3 wall_size);

	//ゲームクリアの判定
	bool cleared_ = false;
	//ゲーム終了の判定
	bool finished_ = false;
	//自機がダメージを受けた時に敵の弾を消す用の判定
	//リスキル防止
	bool tank_damged_ = false;

	//敵のイテレーター
	std::list<std::shared_ptr<Enemy>>::iterator enemy_it_;

	Shared<Tank> tank_ = nullptr;
	Shared<Wall> wall_ = nullptr;
	Shared<Floor> floor_ = nullptr;
	std::list<std::shared_ptr<Enemy>> enemy_;

	//床の種類
	const enum FLOOR_SORT {
		STOP_FLOOR,
		MOVE_FLOOR1,
		MOVE_FLOOR2
	};
private:
	//リザルトシーンの処理
	void ResultSceneProcess(float delta_time);
	
	//カメラの初期値
	tnl::Vector3 FIRST_CAMERA_POS = { 0, 650, -500 };
	//tnl::Vector3 FIRST_CAMERA_POS = { -200, 300, -300 };
	//1体目の敵の座標
	const tnl::Vector3 FIRST_ENEMY1_POS = { 1200,0.1f,500 };
	//2体目の敵の座標
	const tnl::Vector3 FIRST_ENEMY2_POS = { 200,0.1f,2000 };
	//3体目の敵の座標
	const tnl::Vector3 FIRST_ENEMY3_POS = { 1000,0.1f,2000 };
	//敵1の初期向き
	const int ENEMY1_ANGLE = 270;
	//敵2と3の初期向き
	const int ENEMY2_3_ANGLE = 180;
	//黒い背景の画像の透明度
	const int BACK_GFX_ALPHA = 125;
	//リザルトシーンに入るまでの時間
	const float RESULT_SCENE_CHANGE_COUNT = 0.4f;

	//ゲームスタートのフラグ
	bool start_ = false;
	//リザルトを呼び出すフラグ
	bool result_start_ = false;

	//後ろの黒い背景の画像パス
	int back_gfx_;
	//bgmの音楽パス
	int bgm_snd_;
	//ダメージの音楽パス
	int damage_snd_;

	//リザルトの経過時間
	float elapsed_ = 0;


	Shared<dxe::Camera> camera_ = nullptr;
	Shared<dxe::Mesh> skybox_ = nullptr;

	Shared<SceneResult>result_ = nullptr;

};