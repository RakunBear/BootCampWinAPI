#pragma once
#include "GameObject.h"

class Missile2;
class MissileLoader;
class EnumyGroup;

class Tank : public GameObject
{
private :
	POINT pos;
	int size;
	float damage;
	string name;
	RECT rcCollision;
	int hp;

	//����
	POINT barrelEnd;
	int barrelSize;
	float barrelAngle;    // ���� : ��(degree) 0  ~ 180   ~ 360
						 // ���� : (radian)  0f ~ 3.14f ~ 6.28

	// �̻���
	MissileLoader* missileLoader;
	bool canFire;
	int fireTimer;
	std::queue<pair<int, int>>orderQueue;
	int curTime;

	EnumyGroup* enumyGroup;

	bool CheckFire();
	void Reload();

public:

	void Init();	// ��� ������ ���ʱ�ȭ, �޸� �Ҵ�
	void Release(); // �޸� ����
	void Update();	// ������ ������ ���� ���� ����(������ ���)
	void Render(HDC hdc); // ������ ������ ���(�̹���, �ؽ�Ʈ ��)

	void Move();
	void Fire(int skill);
	void RotateBarrel(float angle);
	void Dead();
	void Hit(int damage);
	
	bool CheckMissileHit(const RECT& target);

	const float& GetBarrelAngle();
	const POINT& GetPos();
	const RECT& GetRect();
	const int& GetHp();

	int GetRemainTime();
	void SetEnumyGroup(EnumyGroup* eg);

	Tank();
	~Tank();
};

