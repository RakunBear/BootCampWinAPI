#pragma once
#include "GameObject.h"

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

	virtual void CheckOrder();
	void Shot();

public:
	virtual void Init();	
	virtual void Release(); 
	virtual void Update();
	virtual void Render(HDC hdc); 
	void Move();
	void Dead();
	bool GetDead();
	virtual void Set(const POINT& pos, float angle, float speed = 10);
	const POINT& GetPos();
	float GetAngle();
	const RECT& GetRect();
	void AddOrder(int delayTime, int order);
	virtual void ExcuteOrder(int order);
	virtual void Fire();

	bool HitCheck(const RECT& target);

	Missile2();
	~Missile2();
};

