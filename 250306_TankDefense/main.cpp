#include "config.h"
#include "MainGame.h"

HINSTANCE g_hInstance;	// 프로그램 인스턴스 핸들
HWND g_hWnd;			// 윈도우 핸들
LPCWSTR g_lpszClassName = (LPCWSTR)TEXT("윈도우 API 사용하기");

MainGame g_mainGame;

enum Box { First, Second, End };
RECT rcBox[Box::End], rcIn;
Box currentBox = Box::First;
int boxMoveSpeed = 5;

enum class ShapeType : uint8_t
{
	None,
	Nemo,
	Star
};

struct BeingStar
{
	POINT pt;
	ShapeType type;
	int size;
};

/*
	1. 자동차 그리기 (함수화)
	2. a, d키로 움직이기
	3. 네모 or 동그라미를 그리고 마우스로 드래그 & 드랍 구현
	4. 별이 되어라!
		바닥에 네모 10개를 그린다.
		마우스 드래그를 통해서 위로 이동
		특정 높이 이상 위치에 드랍을 하면
		네모 -> 별 모양으로 바뀐다.
	5. 제어권이 있는 상자 구현
		5_1. 큰 상자 두개, 작은 상자 한개가 존재
		5_2. 큰 상자 안에는 작은 상자가 들어 있다.(제어권이 있는 상자)
		5_3. 작은 상자는 큰 상자를 벗어날 수 없다.
		5_4. 큰 상자끼리 부딪히면 작은 상자가 상대 큰 상자에게 넘어간다. (제어권이 이동)
*/
// Init
void SetBox();

RECT GetRect(int left, int top, int width, int height);
RECT GetRectAtCenter(int x, int y, int width, int height);

// Render
void RenderStar(HDC hdc, int posX, int posY);
void RenderRect(HDC hdc, int x, int y, int width, int height);
void RenderRectAtCenter(HDC hdc, int centerX, int centerY, int width, int height);
void RenderEllipse(HDC hdc, int x, int y, int width, int height);
void RenderEllipseAtCenter(HDC hdc, int centerX, int centerY, int width, int height);
void RenderCar(HDC hdc, int posX, int posY);
void RenderBoxs(HDC hdc);
// Collision
bool PointInRect(POINT ptMouse, RECT rc);	// ptInRect
bool RectInRect(RECT rc1, RECT rc2);
// Update
void UpdateRect(RECT& rc, POINT pt);


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpszCmdParam, int nCmdShow)
{
	g_hInstance = hInstance;

	// 윈도우를 생성하기 위한 데이터 셋팅
	WNDCLASS wndClass;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = LoadCursor(g_hInstance, IDC_ARROW);
	wndClass.hIcon = LoadIcon(g_hInstance, IDI_APPLICATION);
	wndClass.hInstance = g_hInstance;
	wndClass.lpfnWndProc = WndProc;		// 함수의 이름은 메모리주소이다.
	wndClass.lpszClassName = g_lpszClassName;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;	// | : 비트연산자

	RegisterClass(&wndClass);

	g_hWnd = CreateWindow(g_lpszClassName, g_lpszClassName,
		WS_OVERLAPPEDWINDOW, 50, 50, 1080, 720,
		NULL, NULL, g_hInstance, NULL);

	if (ShowWindow(g_hWnd, nCmdShow))
	{
		int a = 0;
	}
	else
	{
		int b = 0;

	}

	MSG message;
	while (GetMessage(&message, 0, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	return message.wParam;
}

void SetBox()
{
	rcBox[Box::First] = GetRectAtCenter(200, 200, 200, 200);
	rcBox[Box::Second] = GetRectAtCenter(500, 200, 200, 200);
	rcIn = GetRectAtCenter(200, 200, 80, 80);
}

RECT GetRect(int left, int top, int width, int height)
{
	RECT rc{ left, top, left + width, top + height };
	return rc;
}

RECT GetRectAtCenter(int x, int y, int width, int height)
{
	RECT rc{ x - (width / 2), y - (height / 2),
		x + (width / 2), y + (height / 2) };
	return rc;
}

void RenderStar(HDC hdc, int posX, int posY)
{
	MoveToEx(hdc, posX + 60, posY + 20, NULL);
	LineTo(hdc, posX - 60, posY + 20);
	LineTo(hdc, posX + 40, posY - 60);
	LineTo(hdc, posX, posY + 60);
	LineTo(hdc, posX - 40, posY - 60);
	LineTo(hdc, posX + 60, posY + 20);
}

// 좌상단 기준
void RenderRect(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x + width, y + height);
}

// 가운데 기준
void RenderRectAtCenter(HDC hdc, int centerX, int centerY, int width, int height)
{
	Rectangle(hdc, centerX - (width / 2), centerY - (height / 2),
		centerX + (width / 2), centerY + (height / 2));
}

// 좌상단 기준
void RenderEllipse(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}

// 가운데 기준
void RenderEllipseAtCenter(HDC hdc, int centerX, int centerY, int width, int height)
{
	Ellipse(hdc, centerX - (width / 2), centerY - (height / 2),
		centerX + (width / 2), centerY + (height / 2));
}

void RenderCar(HDC hdc, int posX, int posY)
{
	// 자동차 상단
	RenderRectAtCenter(hdc, posX, posY - (60 + 50), 220, 100);

	// 자동차 하단
	RenderRectAtCenter(hdc, posX, posY, 350, 120);

	// 바퀴 왼쪽
	RenderEllipseAtCenter(hdc, posX - 80, posY + (60), 80, 80);

	// 바퀴 오른쪽
	RenderEllipseAtCenter(hdc, posX + 80, posY + (60), 80, 80);
}

void RenderBoxs(HDC hdc)
{
	for (int i = 0; i < Box::End; i++)
	{
		Rectangle(hdc, rcBox[i].left, rcBox[i].top,
			rcBox[i].right, rcBox[i].bottom);
	}
	Rectangle(hdc, rcIn.left, rcIn.top, rcIn.right, rcIn.bottom);
}

bool PointInRect(POINT ptMouse, RECT rc)
{
	if (ptMouse.x < rc.left || ptMouse.x > rc.right
		|| ptMouse.y < rc.top || ptMouse.y > rc.bottom)
	{
		return false;
	}
	return true;
}

bool RectInRect(RECT rc1, RECT rc2)
{
	if (rc1.right < rc2.left || rc1.left > rc2.right
		|| rc1.top > rc2.bottom || rc1.bottom < rc2.top)
	{
		return false;
	}
	return true;
}

void UpdateRect(RECT& rc, POINT pt)
{
	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;

	rc.left = pt.x - (width / 2);
	rc.right = rc.left + width;
	rc.top = pt.y - (height / 2);
	rc.bottom = rc.top + height;
}

LRESULT WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	return g_mainGame.MainProc(hWnd, iMessage, wParam, lParam);
}
