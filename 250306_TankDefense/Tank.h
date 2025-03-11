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

	//포신
	POINT barrelEnd;
	int barrelSize;
	float barrelAngle;    // 단위 : 도(degree) 0  ~ 180   ~ 360
						 // 라디안 : (radian)  0f ~ 3.14f ~ 6.28

	// 미사일
	MissileLoader* missileLoader;
	bool canFire;
	int fireTimer;
	std::queue<pair<int, int>>orderQueue;
	int curTime;

	EnumyGroup* enumyGroup;

	bool CheckFire();
	void Reload();

public:

	void Init();	// 멤버 변수으 ㅣ초기화, 메모리 할당
	void Release(); // 메모리 해제
	void Update();	// 프레임 단위로 게임 로직 실행(데이터 계산)
	void Render(HDC hdc); // 프레임 단위로 출력(이미지, 텍스트 등)

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

