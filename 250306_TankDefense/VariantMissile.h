#pragma once
#include "Missile.h"

class VariantMissile : protected Missile2
{
protected:
	Missile2* missiles;
	int missileCount;
	POINT* targetPos;

public:
	void Init() override;
	void Update() override;
	void Render(HDC hdc) override;
	void Release() override;
	void SetTarget(POINT& pos);
	void AddSet(Missile2& missile, const POINT& pos, float angle, float speed = 10);
	void ExcuteOrder(int order) override;
};

class BoomMissile : public VariantMissile
{
public:
	void Init() override;
	void Update() override;
};

