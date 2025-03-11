#include "VariantMissile.h"

void VariantMissile::Init()
{
	missileCount = 0;
	missiles = nullptr;
	targetPos = nullptr;
}

void VariantMissile::Update()
{
	Missile2::Update();
	for (int i = 0; i < missileCount; ++i)
	{
		if (missiles[i].GetDead()) continue;

		missiles[i].Update();
	}
}

void VariantMissile::Render(HDC hdc)
{
	Missile2::Render(hdc);
	for (int i = 0; i < missileCount; ++i)
	{
		if (missiles[i].GetDead()) continue;

		missiles[i].Render(hdc);
	}
}

void VariantMissile::Release()
{
	Missile2::Release();
	delete[] missiles;
}

void VariantMissile::SetTarget(POINT& pos)
{
	targetPos = &pos;
}

void VariantMissile::AddSet(Missile2& missile, const POINT& pos, float angle, float speed)
{
	missile.Set(pos, angle, speed);
}

void VariantMissile::ExcuteOrder(int order)
{
}

void BoomMissile::Init()
{
	missileCount = 36;
	missiles = new Missile2[missileCount];
}

void BoomMissile::Update()
{
	VariantMissile::Update();

	if (curTime == 60)
	{
		for (int i = 0; i < 36; ++i)
		{
			missiles[i].Set(*targetPos, DEGTORAD(10 * i), 10);
			missiles[i].AddOrder(0, 0);
		}
	}
}