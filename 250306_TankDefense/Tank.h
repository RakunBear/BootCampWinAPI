#pragma once
#include "GameObject.h"

class Tank : public GameObject
{
private :
	POINT pos;
	int size;
	float damage;
	string name;
	RECT rcCollision;

	//포신
	POINT barrelEnd;
	int barrelSize;
	float barrelAngle;

	// 미사일

public:
	void Init();	// 멤버 변수으 ㅣ초기화, 메모리 할당
	void Release(); // 메모리 해제
	void Update();	// 프레임 단위로 게임 로직 실행(데이터 계산)
	void Render(HDC hdc); // 프레임 단위로 출력(이미지, 텍스트 등)

	void Move();
	void Fire();
	void RotateBarrel(float angle);
	void Dead();

	Tank();
	~Tank();
};

