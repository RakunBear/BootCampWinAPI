#include "EnumyGroup.h"
#include "Enumy.h"
#include "Tank.h"

void EnumyGroup::Init()
{
	enumyCount = 10;
	enumys = new Enumy[enumyCount];
	for (int i = 0; i < enumyCount; ++i)
	{
		enumys[i].Init(this->tank.GetPos());
		enumys[i].SetRandom();
	}
}

void EnumyGroup::Release()
{
	delete[] enumys;
}

void EnumyGroup::Update()
{
	for (int i = 0; i < enumyCount; ++i)
	{
		if (enumys[i].GetDead()) continue;

		enumys[i].Update();
		
		float nd = enumys[i].GetDistance();
		if (nearDistance > nd)
		{
			nearDistance = nd;
			nearIdx = i;
		}

		if (tank.CheckMissileHit(enumys[i].GetRect()))
		{
			enumys[i].Dead();
		}
		if (enumys[i].HitCheck(tank.GetRect()))
		{
			enumys[i].Dead();
			tank.Hit(enumys[i].GetAtk());
		}
	}
}

void EnumyGroup::Render(HDC hdc)
{
	for (int i = 0; i < enumyCount; ++i)
	{
		enumys[i].Render(hdc);
	}
}

bool EnumyGroup::HitCheck(const RECT& target)
{
	for (int i = 0; i < enumyCount; ++i)
	{
		enumys[i].Update();
	}
	return false;
}

const POINT& EnumyGroup::GetNearEnumyPos()
{
	return enumys[nearIdx].GetPos();
}

EnumyGroup::EnumyGroup(Tank& tank) : tank(tank), enumys(nullptr), enumyCount(0), nearIdx(0), nearDistance(0)
{
}
