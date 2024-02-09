#pragma once

class Floor {
public:
	Floor();
	~Floor();

	void update(float delta_time);
	void draw(Shared<dxe::Camera> camera);

	//����3D�p�̃��b�V��
	Shared<dxe::Mesh> floor1_mesh_ = nullptr;
	Shared<dxe::Mesh> floor2_mesh_ = nullptr;
	Shared<dxe::Mesh> move_floor1_mesh_ = nullptr;
	Shared<dxe::Mesh> move_floor2_mesh_ = nullptr;

	//����p�̏��̑傫��
	tnl::Vector3 floor1_size_v;
	tnl::Vector3 floor2_size_v;
	tnl::Vector3 move_floor_size_v;

	//�����ʒu���瓮�����������̈ړ�����
	float delta_move_floor1_pos_ = 0;
	float delta_move_floor2_pos_ = 0;
private:
	//���̑傫��
	const float FLOOR_SIZE = 1000;
	//�������̑傫��
	const float MOVE_FLOOR_SIZE = 250;

	//--------------------------------��1(��O)-----------------------------------------
	//���̌`
	const tnl::Vector3 FLOOR1_FORM = { 1.7f, 0.25f, 1 };
	//���̍��W
	tnl::Vector3 floor1_pos_ = { 650,-155,300 };
	//--------------------------------��2(��)-----------------------------------------
	//���̌`
	const tnl::Vector3 FLOOR2_FORM = { 1.7f, 0.25f, 0.575f };
	//���̍��W
	tnl::Vector3 floor2_pos_ = { 650,-155,2012.4f };
	//--------------------------------������-----------------------------------------
	//���̌`
	const tnl::Vector3 MOVE_FLOOR_FORM = { 1, 0.25f, 1 };
	//�����ǂ̂��炢������
	const int MOVE_FLOOR_DISTANCE = 600;
	//�����ǂꂭ�炢�̑����œ�����
	const float MOVE_FLOOR_SPEED = 0.5f;
	//--------------------------------������1(��O)-----------------------------------------
	//���̏������W
	tnl::Vector3 MOVE_FLOOR1_POS = { 650,-61,1050 };
	//���̍��W
	tnl::Vector3 move_floor1_pos_ = MOVE_FLOOR1_POS;
	//--------------------------------������2(��)-----------------------------------------
	//���̏������W
	tnl::Vector3 MOVE_FLOOR2_POS = { 650,-61,1400 };
	//���̍��W
	tnl::Vector3 move_floor2_pos_ = MOVE_FLOOR2_POS;



	//�o�ߎ���
	float elapsed_ = 0;
};