#include "config.h"
#include "MainGame.h"

HINSTANCE g_hInstance;	// 프로그램 인스턴스 핸들
HWND g_hWnd;			// 윈도우 핸들
LPCWSTR g_lpszClassName = (LPCWSTR)TEXT("윈도우 API 사용하기");

MainGame g_mainGame;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpszCmdParam, int nCmdShow)
{
	g_hInstance = hInstance;
	
	// 윈도우를 생성하기 위한 데이터 셋팅
	WNDCLASSEX wndClassEx;
	wndClassEx.cbSize = sizeof(WNDCLASSEX); // 구조체 크기 설정
	wndClassEx.cbClsExtra = 0;
	wndClassEx.cbWndExtra = 0;
	wndClassEx.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClassEx.hCursor = LoadCursor(g_hInstance, IDC_ARROW);
	wndClassEx.hIcon = LoadIcon(g_hInstance, IDI_APPLICATION);
	wndClassEx.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SHIELD));
	wndClassEx.hInstance = g_hInstance;
	wndClassEx.lpfnWndProc = WndProc;		// 함수의 이름은 메모리주소이다.
	wndClassEx.lpszClassName = g_lpszClassName;
	wndClassEx.lpszMenuName = NULL;
	wndClassEx.style = CS_HREDRAW | CS_VREDRAW;	// | : 비트연산자

	RegisterClassEx(&wndClassEx);

	RECT rcWindowSize = { 0 , 0, WINSIZE_X, WINSIZE_Y };
	AdjustWindowRect(&rcWindowSize, WS_OVERLAPPEDWINDOW, FALSE);
	int width = rcWindowSize.right - rcWindowSize.left;
	int height = rcWindowSize.bottom - rcWindowSize.top;

	g_hWnd = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, g_lpszClassName, g_lpszClassName,
		WS_OVERLAPPEDWINDOW, 50, 50, width, height,
		NULL, NULL, g_hInstance, NULL);
	 
	//WNDCLASS wndClass;
	//wndClass.cbClsExtra = 0;
	//wndClass.cbWndExtra = 0;
	//wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	//wndClass.hCursor = LoadCursor(g_hInstance, IDC_ARROW);
	//wndClass.hIcon = LoadIcon(g_hInstance, IDI_APPLICATION);
	//wndClass.hInstance = g_hInstance;
	//wndClass.lpfnWndProc = WndProc;		// 함수의 이름은 메모리주소이다.
	//wndClass.lpszClassName = g_lpszClassName;
	//wndClass.lpszMenuName = NULL;
	//wndClass.style = CS_HREDRAW | CS_VREDRAW;	// | : 비트연산자

	//RegisterClass(&wndClass);

	//  g_hWnd = CreateWindow(g_lpszClassName, g_lpszClassName,
	//	WS_OVERLAPPEDWINDOW, 50, 50, WINSIZE_X, WINSIZE_Y,
	//	NULL, NULL, g_hInstance, NULL);

	if (ShowWindow(g_hWnd, nCmdShow))
	{
		int a = 0;
	}
	else
	{
		int b = 0;

	}

	g_mainGame.Init();

	MSG message;
	while (GetMessage(&message, 0, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	return message.wParam;
}

LRESULT WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	return g_mainGame.MainProc(hWnd, iMessage, wParam, lParam);
}
