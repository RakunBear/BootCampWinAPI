#include "Tank.h"
#include "CommonFunction.h"
#include "Missile.h"
#include "VariantMissile.h"

void Tank::Init()
{
	pos.x = WINSIZE_X / 2;
	pos.y = WINSIZE_Y ;
	size = 100;
	damage = 10;
	name = "Tank";
	rcCollision = GetRectAtCenter(pos.x, pos.y, size, size);
	hp = 100;

	// 포신
	barrelSize = 120;
	barrelEnd.x = pos.x;
	barrelEnd.y = pos.y - barrelSize;
	barrelAngle = DEGTORAD(135);

	// 미사일
	missileCount = 200;
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
	if (!canFire && fireTimer > 5)
	{
		canFire = true;
		fireTimer = 0;
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
	missiles[curMissileIdx]->Set(pos, barrelAngle, 10);
	curMissileIdx = ++curMissileIdx % missileCount;
}

void Tank::ThreeFire()
{
	missiles[curMissileIdx]->Set(pos, barrelAngle, 10);
	missiles[curMissileIdx]->AddOrder(0, 0);
	curMissileIdx = ++curMissileIdx % missileCount;
	missiles[curMissileIdx]->Set(pos, barrelAngle, 10);
	missiles[curMissileIdx]->AddOrder(3, 0);
	curMissileIdx = ++curMissileIdx % missileCount;
	missiles[curMissileIdx]->Set(pos, barrelAngle, 10);
	missiles[curMissileIdx]->AddOrder(6, 0);
	curMissileIdx = ++curMissileIdx % missileCount;
}

void Tank::BoomFire()
{
	int idx = (curMissileIdx - 1) % missileCount;
	POINT sp = missiles[idx]->GetPos();
	missiles[idx]->Dead();
	for (int i = 0; i < 36; ++i)
	{
		missiles[curMissileIdx]->Set(sp, DEGTORAD(10 * i), 10);
		missiles[curMissileIdx]->AddOrder(60, 0);
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
	missiles[curMissileIdx]->Set(sp, ang - halfAng, 10);
	curMissileIdx = ++curMissileIdx % missileCount;
	missiles[curMissileIdx]->Set(sp, ang + halfAng, 10);
	curMissileIdx = ++curMissileIdx % missileCount;
}

void Tank::Fire(int skill)
{
	if (!CheckFire()) return;
	canFire = false;

	switch (skill)
	{
	case 0:
		orderQueue.push(pair<int, int>{0, 0});
		break;
	case 1:
		orderQueue.push(pair<int, int>{0, 1});
		break;
	case 2:
		//orderQueue.push(pair<int, int>{0, 0});
		//orderQueue.push(pair<int, int>{60, 2});
		orderQueue.push(pair<int, int>{0, 2});
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

void Tank::Hit(int damage)
{
	hp -= damage;
}

bool Tank::CheckMissileHit(const RECT& target)
{
	wstring w;
	for (int i = 0; i < missileCount; ++i)
	{
		if (!missiles[i] || missiles[i]->GetDead()) continue;
		//w = L"T : " + to_wstring(target.left) + L" _ M[" + to_wstring(i) + L"] : " + to_wstring(missiles[i]->GetRect().left) + L"\n";
		//if (i == 5)
		//	OutputDebugString(w.c_str());
		if (missiles[i]->HitCheck(target))
		{
			missiles[i]->Dead();
			return true;
		}
	}

	return false;
}

const float& Tank::GetBarrelAngle()
{
	return barrelAngle;
}

const POINT& Tank::GetPos()
{
	return pos;
}

const RECT& Tank::GetRect()
{
	return rcCollision;
}

const int& Tank::GetHp()
{
	return hp;
}

int Tank::GetRemainTime()
{
	return max(5 - fireTimer, 0);
}

Tank::Tank()
{
}

Tank::~Tank()
{
}
