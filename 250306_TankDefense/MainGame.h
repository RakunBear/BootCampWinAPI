#pragma once
#include "GameObject.h"

class Tank;
class EnumyGroup;

class MainGame : public GameObject
{
private:
	HDC hdc;
	PAINTSTRUCT ps;
	HANDLE hTimer;
	int mousePosX = 0, mousePosY = 0;
	wchar_t szText[128];

	Tank* tank;
	EnumyGroup* enumyGroup;

public:
	void Init();	// ��� ������ ���ʱ�ȭ, �޸� �Ҵ�
	void Release(); // �޸� ����
	void Update();	// ������ ������ ���� ���� ����(������ ���)
	void Render(HDC hdc); // ������ ������ ���(�̹���, �ؽ�Ʈ ��)

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	MainGame();
	~MainGame();
};

