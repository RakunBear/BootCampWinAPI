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

	if (pos.x < 0 || pos.x > WINSIZE_X || pos.y < 0 || pos.y > WINSIZE_Y)
	{
		Dead();
	}

	if (isDead) return;

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
	pos.x += (int)(speed * cosf(angle));
	pos.y += -(int)(speed * sinf(angle));

	rcCollision = GetRectAtCenter(pos.x, pos.y, size, size);
}

void Missile2::Dead()
{
	isDead = true;
}

bool Missile2::GetDead()
{
	return isDead;
}

void Missile2::Set(const POINT& pos, float angle, float speed)
{
	this->curTime = 0;
	this->liveTime = 300;
	this->angle = angle;
	this->speed = speed;
	this->pos = pos;

	rcCollision = GetRectAtCenter(pos.x, pos.y, size, size);
}

const POINT& Missile2::GetPos()
{
	return pos;
}

float Missile2::GetAngle()
{
	return angle;
}

const RECT& Missile2::GetRect()
{
	return rcCollision;
}

void Missile2::AddOrder(int delayTime, int order)
{
	orderQueue.push(pair<int, int>{delayTime, order});
}

bool Missile2::HitCheck(const RECT& target)
{
	if (isDead) return false;

	if (RectInRect(target, rcCollision))
	{
		return true;
	}
	return false;
}

void Missile2::CheckOrder()
{
	if (orderQueue.size() < 1)
		return;
	//wstring s = L"SF : " + std::to_wstring(curTime);
	//OutputDebugString(s.c_str());
	if (curTime > orderQueue.front().first)
	{
		ExcuteOrder(orderQueue.front().second);

		curTime = 0;
		orderQueue.pop();
	}

	++curTime;
}

void Missile2::Shot()
{
	isDead = false;
}

void Missile2::ExcuteOrder(int order)
{
	switch (order)
	{
	case 0:
		Shot();
		break;
	default:
		break;
	}
}

Missile2::Missile2()
{
}

Missile2::~Missile2()
{
}
