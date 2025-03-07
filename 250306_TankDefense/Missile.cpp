#include "Missile.h"
#include "CommonFunction.h"

void Missile2::Init()
{
	pos.x = 0;
	pos.y = 0;
	size = 50;
	damage = 10;
	rcCollision = GetRectAtCenter(pos.x, pos.y, size, size);
	
	angle = 0;
	speed = 10.0f;
	isDead = true;
	curTime = 0;
	liveTime = 0;
}

void Missile2::Release()
{
}

void Missile2::Update()
{
	CheckOrder();
	Move();

	if (liveTime-- > 0)
		return;
	Dead();
}

void Missile2::Render(HDC hdc)
{
	if (isDead) return;

	RenderEllipseAtCenter(hdc, pos.x, pos.y, size, size);
}

void Missile2::Move()
{
	if (isDead) return;

	if (pos.x < 0 || pos.x > WINSIZE_X || pos.y < 0 || pos.y > WINSIZE_Y)
		return;

	pos.x += (int)(speed * cosf(angle));
	pos.y += -(int)(speed * sinf(angle));

}

void Missile2::Dead()
{
	isDead = true;
}

void Missile2::Set(POINT pos, float angle, int delayTime)
{
	this->curTime = 0;
	this->liveTime = 300;
	this->angle = angle;
	this->pos = pos;
	orderQueue.push(pair<int, int>{delayTime, 0});
}

POINT Missile2::GetPos()
{
	return pos;
}

float Missile2::GetAngle()
{
	return angle;
}

void Missile2::CheckOrder()
{
	if (orderQueue.size() < 1)
		return;
	wstring s = L"SF : " + std::to_wstring(curTime);
	OutputDebugString(s.c_str());
	if (curTime > orderQueue.front().first)
	{
		
		int order = orderQueue.front().second;
		switch (order)
		{
		case 0:
			Shot();
			break;
		default:
			break;
		}

		curTime = 0;
		orderQueue.pop();
	}

	++curTime;
}

void Missile2::Shot()
{
	isDead = false;
}

Missile2::Missile2()
{
}

Missile2::~Missile2()
{
}
