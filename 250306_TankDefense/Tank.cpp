#include "Tank.h"
#include "CommonFunction.h"
#include "MissileLoader.h"
#include "EnumyGroup.h"

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
	missileLoader = new MissileLoader();
	missileLoader->Init();

	canFire = true;
	fireTimer = 0;
}

void Tank::Release()
{
}

void Tank::Update()
{
	Reload();

	barrelEnd.x = pos.x + barrelSize * cosf(barrelAngle);
	barrelEnd.y = pos.y - barrelSize * sinf(barrelAngle);

	missileLoader->Update();
}

void Tank::Render(HDC hdc)
{
	// Body
	RenderEllipseAtCenter(hdc, pos.x, pos.y, size, size);
	// Barrel
	MoveToEx(hdc, pos.x, pos.y, NULL);
	LineTo(hdc, barrelEnd.x, barrelEnd.y);

	missileLoader->Render(hdc);
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

void Tank::Fire(int skill)
{
	if (!CheckFire()) return;
	canFire = false;

	static int chaseCount = 0;

	switch (skill)
	{
	case 0:
		if (++chaseCount % 2 == 0)
		{
			const POINT& p = enumyGroup->GetNearEnumyPos();

			missileLoader->ChaseFire(pos, barrelAngle, 10, p);
		}
		else
		{
			missileLoader->DefaultFire(pos, barrelAngle, 10);
		}
		break;
	case 1:
		missileLoader->ThreeFire(pos, barrelAngle, 10);
		break;
	case 2:
		missileLoader->BoomFire(pos, barrelAngle, 10);
		break;
	case 3:
		missileLoader->SplitFire(pos, barrelAngle, 10);
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
	return missileLoader->CheckMissileHit(target);
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

void Tank::SetEnumyGroup(EnumyGroup* eg)
{
	enumyGroup = eg;
}

Tank::Tank()
{
}

Tank::~Tank()
{
}
