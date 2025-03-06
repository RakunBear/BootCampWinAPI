#include "MainGame.h"

void MainGame::Init()
{
}

void MainGame::Release()
{
}

void MainGame::Update()
{
}

void MainGame::Render(HDC hdc)
{
}

LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMessage)
	{
	case WM_CREATE:
		break;
	case WM_KEYDOWN:
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

		break;
	case WM_PAINT:
		hdc = BeginPaint(g_hWnd, &ps);

		// 그리기 위한 로직
		TextOut(hdc, 20, 20, TEXT("Hello, World!"), strlen("Hello, World!"));
		wsprintf(szText/* 문자열 공간 */,
			TEXT("Mouse X : %d, Y : %d")/* 형태 */,
			mousePosX, mousePosY);
		TextOut(hdc, 20, 60, szText, wcslen(szText));

		RenderBoxs(hdc);

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
