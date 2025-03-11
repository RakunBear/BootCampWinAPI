#include "MissileLoader.h"
#include "Missile.h"

void MissileLoader::CreateMissile(POINT pos, float dx, float dy, int speed)
{

}

void MissileLoader::Init()
{
	// πÃªÁ¿œ
	_missileCount = 100;
	_missiles = new Missile2 * [_missileCount];
	for (int i = 0; i < _missileCount; ++i)
	{
		_missiles[i] = new Missile2;
		_missiles[i]->Init();
	}
	_missileIdx = 0;
}

void MissileLoader::Release()
{
	if (_missiles)
	{
		for (int i = 0; i < _missileCount; ++i)
		{
			if (!_missiles[i]) continue;

			delete _missiles[i];
		}
		delete[] _missiles;
	}
}

void MissileLoader::Update()
{
	for (int i = 0; i < _missileCount; ++i)
	{
		if (_missiles[i]->GetDead()) continue;

		_missiles[i]->Update();
	}
}
