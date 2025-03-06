#pragma once
#include "GameObject.h"

class Tank : public GameObject
{
private :
	POINT pos;
	int size;
	float damage;
	string name;
	RECT rcCollision;

	//����
	POINT barrelEnd;
	int barrelSize;
	float barrelAngle;

	// �̻���

public:
	void Init();	// ��� ������ ���ʱ�ȭ, �޸� �Ҵ�
	void Release(); // �޸� ����
	void Update();	// ������ ������ ���� ���� ����(������ ���)
	void Render(HDC hdc); // ������ ������ ���(�̹���, �ؽ�Ʈ ��)

	void Move();
	void Fire();
	void RotateBarrel(float angle);
	void Dead();

	Tank();
	~Tank();
};

