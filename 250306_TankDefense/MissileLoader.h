#pragma once
#include "GameObject.h"

class Missile2;

class MissileLoader
{
	enum class MissileOrder
	{
		Default,

	};

private:
	Missile2** _missiles;
	int _missileCount;
	int _missileIdx;
	
	void CreateMissile(POINT pos, float dx, float dy, int speed);

public:
	void Init();	// ��� ������ ���ʱ�ȭ, �޸� �Ҵ�
	void Release(); // �޸� ����
	void Update();	// ������ ������ ���� ���� ����(������ ���)
	void Render(HDC hdc); // ������ ������ ���(�̹���, �ؽ�Ʈ ��)

	void OrderMissile(MissileOrder order);
};

