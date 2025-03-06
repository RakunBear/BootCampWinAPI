// config.h

#pragma once

#include <Windows.h>
#include <string>
#include <iostream>

using namespace std;

#define WINSIZE_X 1080
#define WINSIZE_Y 720

/*
	extern 키워드 : 변수나 함수가 다른 파일에 정의되어 있다 라는 사실을 알리는 키워드
*/
extern HWND g_hWnd;