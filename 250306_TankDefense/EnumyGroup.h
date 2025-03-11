#pragma once
#include "GameObject.h"
class Enumy;
class Tank;

class EnumyGroup : protected GameObject
{
private:
	Enumy* enumys;
	Tank& tank;
	int enumyCount;
	int nearIdx;
	float nearDistance;
	
public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);
	bool HitCheck(const RECT& target);

	const POINT& GetNearEnumyPos();

	EnumyGroup(Tank& tank);
	~EnumyGroup() = default;
};

