#pragma once


class Bullet {
public:
	//À•WAŒü‚«AŒü‚«(“x”–@‚ÌŠp“x)A“G‚©–¡•û‚©
	Bullet(const tnl::Vector3& spawn_pos, const tnl::Vector3& move_dir,const int& dir_value,const bool& enemy);

	void update(float delta_time);
	void draw(Shared<dxe::Camera> camera);

	Shared<dxe::Mesh> mesh_ = nullptr;

	//Œü‚«‚ÌŠm”F
	void DirCheck(bool bullet_reflection);

	//’e‚Ì”»’è—p‚Ì‘å‚«‚³
	tnl::Vector3 bullet_size_v;
	//’e‚ª”½Ë‚³‚ê‚½‚©‚Ç‚¤‚©
	bool bullet_reflection_ = false;
private:
	//’e‚ÌŒ`
	const tnl::Vector3 BULLET_FORM = { 1.0f, 1.0f, 2.0f };
	//’e‚Ì‘å‚«‚³
	const float BULLET_SIZE = 15;
	//’e‘¬
	const int BULLET_SPEED = 10;
	//”½ËŒã‚Ì’e‘¬
	const int BULLET_REFLECT_SPEED = -2;

	//’e‚ÌŒü‚«
	int bullet_dir_ = 1;
	//’e‚ÌŒü‚«(Vector3)
	tnl::Vector3 move_dir_ = { 0,0,0 };

	Shared<dxe::Texture> texture = nullptr;
};