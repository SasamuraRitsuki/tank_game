#pragma once

class Wall {
public:
	Wall();
	~Wall();

	void update(float delta_time);
	void draw(Shared<dxe::Camera> camera);

	//�ǂ�3D�p�̃��b�V��
	Shared<dxe::Mesh> wall1_mesh_ = nullptr;
	Shared<dxe::Mesh> wall2_mesh_ = nullptr;
	Shared<dxe::Mesh> wall3_mesh_ = nullptr;
	Shared<dxe::Mesh> wall4_mesh_ = nullptr;
	Shared<dxe::Mesh> wall5_mesh_ = nullptr;
	//Shared<dxe::Mesh> wall_virtual_mesh_ = nullptr;

	//����p�̏��̑傫��
	tnl::Vector3 wall1_size_v;
	tnl::Vector3 wall2_size_v;
	tnl::Vector3 wall3_size_v;
	tnl::Vector3 wall4_size_v;
	tnl::Vector3 wall5_size_v;
	tnl::Vector3 wall_virtual_size_v;

	//���z�ǂ̍��W
	tnl::Vector3 wall_virtual_pos_ = { 650,-45,1264 };

private:
	//�[�̕ǂ̑傫��
	const float WALL_SIZE = 100;

	//--------------------------------��1��-----------------------------------------
	//�ǂ̌`
	const tnl::Vector3 WALL1_FORM = { 1, 5, 27 };
	//�ǂ̍��W
	tnl::Vector3 wall1_pos_ = { -250,-45,1050 };

	//--------------------------------��2�E-----------------------------------------
	//�ǂ̌`
	const tnl::Vector3 WALL2_FORM = { 1, 5, 27 };
	//�ǂ̍��W
	tnl::Vector3 wall2_pos_ = { 1550,-45,1050 };
	//tnl::Vector3 wall2_pos_ = { 1580,-45,1050 };

	//--------------------------------��3��O-----------------------------------------
	//�ǂ̌`
	const tnl::Vector3 WALL3_FORM = { 17, 5, 1 };
	//�ǂ̍��W
	tnl::Vector3 wall3_pos_ = { 650,-45,-250 };

	//--------------------------------��4��-----------------------------------------
	//�ǂ̌`
	const tnl::Vector3 WALL4_FORM = { 17, 5, 1 };
	//�ǂ̍��W
	tnl::Vector3 wall4_pos_ = { 650,-45,2350 };
	//tnl::Vector3 wall4_pos_ = { 650,-45,2550 };

	//--------------------------------��5���������̉���-----------------------------------------
	//�ǂ̌`
	const tnl::Vector3 WALL5_FORM = { 10, 1.4f, 1 };
	//�ǂ̍��W
	tnl::Vector3 wall5_pos_ = { 302,50,300 };

	//--------------------------------���z��-----------------------------------------
	//�ǂ̌`
	const tnl::Vector3 WALL_VIRTUAL_FORM = { 19, 5, 8.4f };

};