#include "Tank.h"
#include "CommonFunction.h"
#include "Missile.h"

void Tank::Init()
{
	pos.x = WINSIZE_X / 2;
	pos.y = WINSIZE_Y ;
	size = 100;
	damage = 10;
	name = "Tank";
	rcCollision = GetRectAtCenter(pos.x, pos.y, size, size);

	// 포신
	barrelSize = 120;
	barrelEnd.x = pos.x;
	barrelEnd.y = pos.y - barrelSize;
	barrelAngle = DEGTORAD(135);

	// 미사일
	missileCount = 100;
	missiles = new Missile2*[missileCount];
	for (int i = 0; i < missileCount; ++i)
	{
		missiles[i] = new Missile2;
		missiles[i]->Init();
	}
	curMissileIdx = 0;

	canFire = true;
	fireTimer = 0;

	// skill
	s1 = pair<int, int>{ 0, 10 };
	s2 = pair<int, int>{ 0, 3 };
}

void Tank::Release()
{
	if (missiles)
	{
		for (int i = 0; i < missileCount; ++i)
		{
			if (!missiles[i]) continue;

			delete missiles[i];
		}
		delete[] missiles;
	}
}

void Tank::CheckOrder()
{
	if (orderQueue.size() < 1)
		return;

	if (curTime > orderQueue.front().first)
	{
		int order = orderQueue.front().second;
		switch (order)
		{
		case 0:
			DefaultFire();
			break;
		case 1:
			ThreeFire();
			break;
		case 2:
			BoomFire();
			break;
		case 3:
			SplitFire();
			break;
		default:
			break;
		}

		curTime = 0;
		orderQueue.pop();
	}

	++curTime;
}

void Tank::Update()
{
	Reload();
	CheckOrder();

	barrelEnd.x = pos.x + barrelSize * cosf(barrelAngle);
	barrelEnd.y = pos.y - barrelSize * sinf(barrelAngle);

	for (int i = 0; i < missileCount; ++i)
	{
		if (!missiles[i]) continue;

		missiles[i]->Update();
	}
}

void Tank::Render(HDC hdc)
{
	// Body
	RenderEllipseAtCenter(hdc, pos.x, pos.y, size, size);
	// Barrel
	MoveToEx(hdc, pos.x, pos.y, NULL);
	LineTo(hdc, barrelEnd.x, barrelEnd.y);

	for (int i = 0; i < missileCount; ++i)
	{
		if (!missiles[i]) continue;

		missiles[i]->Render(hdc);
	}
}

void Tank::Move()
{
}

bool Tank::CheckFire()
{
	if (fireTimer > 5)
	{
		canFire = true;
		fireTimer = 0;
	}
	else
	{
		canFire = false;
	}

	return canFire;
}

void Tank::Reload()
{
	if (canFire) return;

	fireTimer += 1;
}

void Tank::DefaultFire()
{
	missiles[curMissileIdx]->Set(pos, barrelAngle, 0);
	curMissileIdx = ++curMissileIdx % missileCount;
}

void Tank::ThreeFire()
{
	missiles[curMissileIdx]->Set(pos, barrelAngle, 0);
	curMissileIdx = ++curMissileIdx % missileCount;
	missiles[curMissileIdx]->Set(pos, barrelAngle, 3);
	curMissileIdx = ++curMissileIdx % missileCount;
	missiles[curMissileIdx]->Set(pos, barrelAngle, 6);
	curMissileIdx = ++curMissileIdx % missileCount;

	OutputDebugString(L"ADADA");
}

void Tank::BoomFire()
{
	int idx = (curMissileIdx - 1) % missileCount;
	POINT sp = missiles[idx]->GetPos();
	missiles[idx]->Dead();
	for (int i = 0; i < 36; ++i)
	{
		missiles[curMissileIdx]->Set(sp, DEGTORAD(10 * i), 0);
		curMissileIdx = ++curMissileIdx % missileCount;
	}
}

void Tank::SplitFire()
{
	int idx = (curMissileIdx - 1) % missileCount;
	POINT sp = missiles[idx]->GetPos();
	float ang = missiles[idx]->GetAngle();
	float halfAng = DEGTORAD(45);
	missiles[idx]->Dead();
	missiles[curMissileIdx]->Set(sp, ang - halfAng, 0);
	curMissileIdx = ++curMissileIdx % missileCount;
	missiles[curMissileIdx]->Set(sp, ang + halfAng, 0);
	curMissileIdx = ++curMissileIdx % missileCount;
}

void Tank::Fire(int skill)
{
	if (!CheckFire()) return;

	switch (skill)
	{
	case 0:
		orderQueue.push(pair<int, int>{0, 0});
		break;
	case 1:
		orderQueue.push(pair<int, int>{0, 1});
		break;
	case 2:
		orderQueue.push(pair<int, int>{0, 0});
		orderQueue.push(pair<int, int>{60, 2});
		break;
	case 3:
		orderQueue.push(pair<int, int>{0, 0});
		orderQueue.push(pair<int, int>{30, 3});
		break;
	default:
		break;
	}


}



void Tank::RotateBarrel(float angle)
{
	barrelAngle += angle;
}

void Tank::Dead()
{
}

Tank::Tank()
{
}

Tank::~Tank()
{
}
