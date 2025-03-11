#include "MissileLoader.h"
#include "Missile.h"

void MissileLoader::SetMissiles(int count)
{
	_missileCount = count;
	_missiles = new Missile2[_missileCount];
	for (int i = 0; i < _missileCount; ++i)
	{
		_missiles[i].Init();
		_missiles[i].SetMissileLoader(this);
	}
	_missileIdx = 0;
}

void MissileLoader::Init()
{
	// ¹Ì»çÀÏ
	SetMissiles(200);
}

void MissileLoader::Release()
{
	if (_missiles)
	{
		delete[] _missiles;
	}
}

void MissileLoader::Update()
{
	for (int i = 0; i < _missileCount; ++i)
	{
		//if (_missiles[i].GetDead()) continue;
		_missiles[i].Update();
	}
}

void MissileLoader::Render(HDC hdc)
{
	for (int i = 0; i < _missileCount; ++i)
	{
		if (_missiles[i].GetDead()) continue;

		_missiles[i].Render(hdc);
	}
}

void MissileLoader::Boom(POINT& pos)
{
	for (int i = 0; i < 36; ++i)
	{
		Missile2& m = GetMissile();
		m.Set(pos, DEGTORAD(10*i));
		m.AddOrder(0, 0);
	}
}

void MissileLoader::DefaultFire(POINT& pos, float& angle, int speed = 10)
{
	Missile2& m = GetMissile();
	m.Set(pos, angle, speed);
	m.AddOrder(0, 0);

}

void MissileLoader::ThreeFire(POINT& pos, float& angle, int speed = 10)
{
	Missile2& m = GetMissile();
	m.Set(pos, angle, speed);
	m.AddOrder(0, 0);
	Missile2& m1 = GetMissile();
	m1.Set(pos, angle, speed);
	m1.AddOrder(3, 0);
	Missile2& m2 = GetMissile();
	m2.Set(pos, angle, speed);
	m2.AddOrder(6, 0);
}

void MissileLoader::BoomFire(POINT& pos, float& angle, int speed = 10)
{

	Missile2& m = GetMissile();
	m.Set(pos, angle, speed);
	m.AddOrder(0, 0);
	m.AddOrder(60, 1);
}

void MissileLoader::SplitFire(POINT& pos, float& angle, int speed)
{
	Missile2& m = GetMissile();
	m.Set(pos, angle, speed);
	m.AddOrder(0, 0);
}

void MissileLoader::ChaseFire(POINT& pos, float& angle, int speed, const POINT& target)
{
	Missile2& m = GetMissile();
	m.Set(pos, angle, speed);
	m.TargetSet(target);
	m.AddOrder(0, 0);
}



Missile2& MissileLoader::GetMissile()
{
	for (int i = 0; i < _missileCount; ++i)
	{
		_missileIdx = ++_missileIdx % _missileCount;
		if (!_missiles[_missileIdx].GetDead()) continue;
		
		return _missiles[_missileIdx];
	}

	SetMissiles(_missileCount + 50);
	_missileIdx = _missileCount - 50;
	return _missiles[_missileIdx];
}

bool MissileLoader::CheckMissileHit(const RECT& target)
{
	for (int i = 0; i < _missileCount; ++i)
	{
		if (_missiles[i].GetDead()) continue;
		//OutputDebugString(L"ABCDE_\n");

		if (RectInRect(_missiles[i].GetRect(), target))
		{
			_missiles[i].Dead();
			return true;
		}
	}
	return false;
}

MissileLoader::MissileLoader()
{
	Init();
}

MissileLoader::~MissileLoader()
{
	Release();
}
