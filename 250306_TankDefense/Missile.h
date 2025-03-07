#pragma once
#include "GameObject.h"

class Missile2 : public GameObject
{
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

	void CheckOrder();
	void Shot();

public:
	void Init();	
	void Release(); 
	void Update();
	void Render(HDC hdc); 
	void Move();
	void Dead();
	void Set(POINT pos, float angle, int delayTime);
	POINT GetPos();
	float GetAngle();

	Missile2();
	~Missile2();
};

