#include "MainGame.h"
#include "Tank.h"
#include "EnumyGroup.h"

/*
	�ǽ�1. �̻��� �ѹ� ���
	�ǽ�2. �̻��� ������ ���
	�ǽ�3. ��ų1(360 �̻��� ���)
	�ǽ�4. ��ų��2 (��ü ��ȹ)
*/

/* 
	�ǽ�1. �� Ŭ���� ���� (ȭ�� ��, ������ ��ġ)
	�ǽ�2. ���� ��ũ�� ���� �ٰ��´�.
	�ǽ�3. �̻��� - ��, �� - ��ũ �浹 ó��
	�ǽ�4. 5��° �̻��� ���� �����̻��� �߻�
			(���� ����� ���� ���� ���� �����)
*/

void MainGame::Init()
{
	tank = new Tank();
	tank->Init();
	enumyGroup = new EnumyGroup(*tank);
	enumyGroup->Init();
}

void MainGame::Release()
{
	if (tank)
	{
		tank->Release();
		delete tank;
	}

	if (enumyGroup)
	{
		enumyGroup->Release();
		delete enumyGroup;
	}
}

void MainGame::Update()
{
	if (tank)
	{
		tank->Update();
	}

	if (enumyGroup)
	{
		enumyGroup->Update();
	}
}

void MainGame::Render(HDC hdc)
{
	if (tank)
		tank->Render(hdc);

	if (enumyGroup)
	{
		enumyGroup->Render(hdc);
	}

	wsprintf(szText, L"HP : %d", tank->GetHp());
	TextOut(hdc, 20, 20, szText, wcslen(szText));
	wsprintf(szText, L"Attack Delay : %d", tank->GetRemainTime());
	TextOut(hdc, 20, 40, szText, wcslen(szText));
}

LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMessage)
	{
	case WM_CREATE:
		SetTimer(hWnd, 0, 100, NULL);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case 'a': case 'A':
			tank->RotateBarrel(DEGTORAD(10));
			break;
		case 'd': case 'D':
			tank->RotateBarrel(-DEGTORAD(10));
			break;
		case 'j': case 'J':
			tank->Fire(0);
			break;
		case 'k': case 'K':
			tank->Fire(1);
			break;
		case 'l': case 'L':
			tank->Fire(2);
			break;
		case 'i': case 'I':
			tank->Fire(3);
			break;
		}
		break;
	case WM_LBUTTONDOWN:
		mousePosX = LOWORD(lParam);
		mousePosY = HIWORD(lParam);
		break;
	case WM_LBUTTONUP:
		break;
	case WM_MOUSEMOVE:
		mousePosX = LOWORD(lParam);
		mousePosY = HIWORD(lParam);
	case WM_TIMER:
		this->Update();
		InvalidateRect(g_hWnd, nullptr, true);
		break;
	case WM_PAINT:
		hdc = BeginPaint(g_hWnd, &ps);

		this->Render(hdc);

		EndPaint(g_hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

MainGame::MainGame()
{
}

MainGame::~MainGame()
{
}
