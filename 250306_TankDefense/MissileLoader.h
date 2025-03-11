#pragma once
#include "GameObject.h"

class Missile2;

class MissileLoader
{
private:
	Missile2* _missiles;
	int _missileCount;
	int _missileIdx;
	
	void SetMissiles(int count);

public:
	void Init();	// 멤버 변수으 ㅣ초기화, 메모리 할당
	void Release(); // 메모리 해제
	void Update();	// 프레임 단위로 게임 로직 실행(데이터 계산)
	void Render(HDC hdc); // 프레임 단위로 출력(이미지, 텍스트 등)
	void Boom(POINT& pos);
	void DefaultFire(POINT& pos, float& angle, int speed);
	void ThreeFire(POINT& pos, float& angle, int speed);
	void BoomFire(POINT& pos, float& angle, int speed);
	void SplitFire(POINT& pos, float& angle, int speed);
	void ChaseFire(POINT& pos, float& angle, int speed, const POINT& target);
	Missile2& GetMissile();
	bool CheckMissileHit(const RECT& target);

	MissileLoader();
	~MissileLoader();
};

