// config.h

#pragma once

#include <Windows.h>
#include <string>
#include <iostream>
#include <queue>

using namespace std;

// Collision
bool PointInRect(POINT ptMouse, RECT rc);	// ptInRect
bool RectInRect(RECT rc1, RECT rc2);
// Update
void UpdateRect(RECT& rc, POINT pt);
// Render
void RenderStar(HDC hdc, int posX, int posY);
void RenderRect(HDC hdc, int x, int y, int width, int height);
void RenderRectAtCenter(HDC hdc, int centerX, int centerY, int width, int height);
void RenderEllipse(HDC hdc, int x, int y, int width, int height);
void RenderEllipseAtCenter(HDC hdc, int centerX, int centerY, int width, int height);

#define WINSIZE_X 1080
#define WINSIZE_Y 720
#define DEGTORAD(x) x * (6.28f/360.0f)

/*
	extern Ű���� : ������ �Լ��� �ٸ� ���Ͽ� ���ǵǾ� �ִ� ��� ����� �˸��� Ű����
*/
extern HWND g_hWnd;