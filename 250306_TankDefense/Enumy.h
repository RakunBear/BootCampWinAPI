#pragma once
#include "GameObject.h"

class Enumy
{
	POINT pos;
	POINT targetPos;
	int size;
	float damage;
	RECT rcCollision;
	float angle;
	float speed;
	bool isDead;
	int atk;

	HBRUSH colorBrush;
	HBRUSH oldBrush;

public:
	virtual void Init(POINT targetPos);
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
	void Move();
	void Dead();
	bool GetDead();
	bool OutOfScreen();
	void SetRandom();
	virtual void Set(POINT pos, POINT targetPos, float speed = 5, int delayTime = 0);
	virtual bool HitCheck(const RECT& target);

	const POINT& GetPos();
	float GetAngle();
	float GetDistance();
	const RECT& GetRect();
	const int& GetAtk();
};

