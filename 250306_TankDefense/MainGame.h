#pragma once
#include "GameObject.h"

class MainGame : public GameObject
{
private:
	HDC hdc;
	PAINTSTRUCT ps;
	HANDLE hTimer;
	int mousePosX = 0, mousePosY = 0;
	wchar_t szText[128];

	//Tank tank

public:
	void Init();	// 멤버 변수으 ㅣ초기화, 메모리 할당
	void Release(); // 메모리 해제
	void Update();	// 프레임 단위로 게임 로직 실행(데이터 계산)
	void Render(HDC hdc); // 프레임 단위로 출력(이미지, 텍스트 등)

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	MainGame();
	~MainGame();
};

