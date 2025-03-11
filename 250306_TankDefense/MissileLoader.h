#pragma once
#include "GameObject.h"

class Missile2;

class MissileLoader
{
private:
	Missile2* _missiles;
	int _missileCount;
	int _missileIdx;
	
	void SetMissiles(int count);

public:
	void Init();	// ��� ������ ���ʱ�ȭ, �޸� �Ҵ�
	void Release(); // �޸� ����
	void Update();	// ������ ������ ���� ���� ����(������ ���)
	void Render(HDC hdc); // ������ ������ ���(�̹���, �ؽ�Ʈ ��)
	void Boom(POINT& pos);
	void DefaultFire(POINT& pos, float& angle, int speed);
	void ThreeFire(POINT& pos, float& angle, int speed);
	void BoomFire(POINT& pos, float& angle, int speed);
	void SplitFire(POINT& pos, float& angle, int speed);
	void ChaseFire(POINT& pos, float& angle, int speed, const POINT& target);
	Missile2& GetMissile();
	bool CheckMissileHit(const RECT& target);

	MissileLoader();
	~MissileLoader();
};

