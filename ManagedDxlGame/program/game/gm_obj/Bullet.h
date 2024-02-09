#pragma once


class Bullet {
public:
	//���W�A�����A����(�x���@�̊p�x)�A�G��������
	Bullet(const tnl::Vector3& spawn_pos, const tnl::Vector3& move_dir,const int& dir_value,const bool& enemy);

	void update(float delta_time);
	void draw(Shared<dxe::Camera> camera);

	Shared<dxe::Mesh> mesh_ = nullptr;

	//�����̊m�F
	void DirCheck(bool bullet_reflection);

	//�e�̔���p�̑傫��
	tnl::Vector3 bullet_size_v;
	//�e�����˂��ꂽ���ǂ���
	bool bullet_reflection_ = false;
private:
	//�e�̌`
	const tnl::Vector3 BULLET_FORM = { 1.0f, 1.0f, 2.0f };
	//�e�̑傫��
	const float BULLET_SIZE = 15;
	//�e��
	const int BULLET_SPEED = 10;
	//���ˌ�̒e��
	const int BULLET_REFLECT_SPEED = -2;

	//�e�̌���
	int bullet_dir_ = 1;
	//�e�̌���(Vector3)
	tnl::Vector3 move_dir_ = { 0,0,0 };

	Shared<dxe::Texture> texture = nullptr;
};