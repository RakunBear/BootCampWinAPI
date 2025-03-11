#pragma once
#include "GameObject.h"

class Missile2;

class MissileLoader
{
	enum class MissileOrder
	{
		Default,

	};

private:
	Missile2** _missiles;
	int _missileCount;
	int _missileIdx;
	
	void CreateMissile(POINT pos, float dx, float dy, int speed);

public:
	void Init();	// 멤버 변수으 ㅣ초기화, 메모리 할당
	void Release(); // 메모리 해제
	void Update();	// 프레임 단위로 게임 로직 실행(데이터 계산)
	void Render(HDC hdc); // 프레임 단위로 출력(이미지, 텍스트 등)

	void OrderMissile(MissileOrder order);
};

