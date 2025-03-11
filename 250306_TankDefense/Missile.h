#pragma once
#include "GameObject.h"

class MissileLoader;

class Missile2 : public GameObject
{
public:
	POINT pos;
	int size;
	float damage;
	RECT rcCollision;
	float angle;
	float speed;
	bool isDead;
	int curTime;
	int liveTime;
	std::queue<pair<int, int>> orderQueue;

	MissileLoader* missileLoader;
	const POINT* target;

	void CheckOrder();
	void Shot();

public:
	void Init();	
	void Release(); 
	void Update();
	void Render(HDC hdc); 
	void Move();
	void Dead();
	bool GetDead();
	void Set(const POINT& pos, float angle, float speed = 10);
	void TargetSet(const POINT& pos);
	const POINT& GetPos();
	float GetAngle();
	const RECT& GetRect();
	void AddOrder(int delayTime, int order);
	void ExcuteOrder(int order);
	void SetMissileLoader(MissileLoader* loader);
	void Chase();

	bool HitCheck(const RECT& target);
	bool HasTarget();

	Missile2();
	~Missile2();
};

