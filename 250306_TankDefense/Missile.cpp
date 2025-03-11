#include "Missile.h"
#include "CommonFunction.h"
#include "MissileLoader.h"

void Missile2::Init()
{
	pos.x = 0;
	pos.y = 0;
	size = 50;
	damage = 10;
	rcCollision = GetRectAtCenter(pos.x, pos.y, size, size);
	missileLoader = nullptr;
	
	angle = 0;
	speed = 10.0f;
	isDead = true;
	curTime = 0;
	liveTime = 0;
	this->target = nullptr;
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

	if (HasTarget())
	{
		Chase();

	}
	else
	{
		Move();
	}

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
	this->target = nullptr;
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

void Missile2::TargetSet(const POINT& pos)
{
	this->target = &pos;
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

bool Missile2::HasTarget()
{
	if (target != nullptr)
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
	case 1:
		if (missileLoader != nullptr)
		{
			missileLoader->Boom(pos);
			Dead();
		}
		break;
	default:
		break;
	}
}

void Missile2::SetMissileLoader(MissileLoader* loader)
{
	missileLoader = loader;
	OutputDebugString(L")))");
}

void Missile2::Chase()
{
	int dx = target->x - pos.x;
	int dy = target->y - pos.y;
	float ag = atan2f(dy, dx);

	pos.x += (int)(speed * cosf(ag));
	pos.y += (int)(speed * sinf(ag));

	rcCollision = GetRectAtCenter(pos.x, pos.y, size, size);
}

Missile2::Missile2()
{
}

Missile2::~Missile2()
{
}
