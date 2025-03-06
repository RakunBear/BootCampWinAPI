
/*
	실습 1. 플레이어(좌측), 적(우측)을 하나씩 만듦
	플레이어는 w, s 키로 상하로 이동 가능
	적은 자동으로 상하로 이동

	실습 2. 마우스 왼쪽 버튼 누르면 미사일 발사
	적도 랜덤 타이밍에 미사일 발사

	실습 3. 각자 미사일에 맞으면 사라진다.
	(적에게 맞거나 화면 밖으로 사라지면 재장전)
*/

#include <Windows.h>
#include <vector>
#include <string>

enum class eDir
{
	LEFT,
	TOP,
	RIGHT,
	BOTTOM,
};

class Object
{
protected:
	POINT halfSize;

	void Move(int dx, int dy, const int& sw, const int& sh);
public:
	POINT pos;
	POINT size;
	RECT collider;
	int hp;
	unsigned int speed;

	Object();
	void SetPos(int x, int y);
	void SetSize(int x, int y);
	void SetCollider();
	void Move(eDir dir, const int& sw, const int& sh);
	virtual void Render(HDC hdc);
	virtual void Initialize();
	virtual void Update(HDC hdc, const int& sw, const int& sh);
};

class Missile : public Object
{
public:
	int atk;
	bool isShot;
	bool isErase;
	eDir dir;
	Missile();
	void Reset();
	void EraseMove(const int& sw, const int& sh);
	void Render(HDC hdc) override;
	void Update(HDC hdc, const int& sw, const int& sh) override;
	void Shot(eDir dir, int x, int y);
};


class Player : public Object
{
public:
	int curMissileIdx;
	Missile missile[10];
	bool isDestory;

	Player();
	void Render(HDC hdc) override;
	void Shot();
	void Update(HDC hdc, const int& sw, const int& sh) override;
};

class Enumy : public Object
{
public:
	int dirY;
	int curMissileIdx;
	Missile missile[10];
	bool isDestory;
	int randomCount;

	Enumy();
	void Render(HDC hdc) override;
	void RepeatMove(const int& sw, const int& sh);
	void Update(HDC hdc, const int& sw, const int& sh) override;
	void Shot();
};

class Manager
{
public:
	int width;
	int height;
public:
	const int MISSILECOUNT{ 5 };

	std::vector<Object*> objs;
	Player player;
	Enumy enumy;

	int curMissileIdx;
	Missile missiles[5];

	Manager();
	void SetScreenSize(int w, int h);
	void InitGame();
	void Render(HDC hdc);
	void Update(HDC hdc);
	void Shot(eDir dir, int x, int y);
	bool RectInRect(RECT rc1, RECT rc2);
};

HINSTANCE g_hinstance;	// 프로그램 인스턴스 핸들
HWND g_hWnd;			// 윈도우 핸들
LPWSTR g_lpszClassName{ (LPWSTR)TEXT("윈도우 API 사용하기") };

Manager gameManger;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpszCmdParam, _In_ int nCmdShow)
{
	g_hinstance = hInstance;

	/* Save Screen Size*/
	gameManger.SetScreenSize(1080, 720);

	// 윈도우 생성위한 데이터 셋팅
	WNDCLASS wndClass;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = LoadCursor(g_hinstance, IDC_ARROW);
	wndClass.hIcon = LoadIcon(g_hinstance, IDI_APPLICATION);
	wndClass.hInstance = g_hinstance;
	wndClass.lpfnWndProc = WndProc; // 함수의 이름은 메모리주소
	wndClass.lpszClassName = g_lpszClassName;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;  // | ; 비트 연산자

	RegisterClass(&wndClass);

	g_hWnd = CreateWindow(g_lpszClassName, g_lpszClassName, WS_OVERLAPPEDWINDOW, 50, 50, 1080, 720, NULL, NULL, g_hinstance, NULL);

	if (ShowWindow(g_hWnd, nCmdShow))
	{

	}
	else
	{

	}

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
	PAINTSTRUCT ps;
	HDC hdc;

	// 타이머
	// : 일정 시간마다 호출되는 이벤트
	static HANDLE timer;

	// Logic
	switch (iMessage)
	{
	case WM_CREATE:
		SetTimer(hWnd, 0, 100, NULL);
		gameManger.InitGame();
	case WM_KEYDOWN:
		switch (wParam)
		{
		case 'a': case 'A':
			//gameManger.player.Move(eDir::LEFT, gameManger.width, gameManger.height);
			break;
		case 'w': case 'W':
			gameManger.player.Move(eDir::TOP, gameManger.width, gameManger.height);
			break;
		case 'd': case 'D':
			//gameManger.player.Move(eDir::RIGHT, gameManger.width, gameManger.height);
			break;
		case 's': case 'S':
			gameManger.player.Move(eDir::BOTTOM, gameManger.width, gameManger.height);
			break;
		default:
			break;
		}

		break;
	case WM_LBUTTONDOWN:
		//gameManger.player.Shot();
		if (!gameManger.player.isDestory)
			gameManger.Shot(eDir::RIGHT, gameManger.player.pos.x, gameManger.player.pos.y);
		break;
	case WM_PAINT:
		hdc = BeginPaint(g_hWnd, &ps);  // 창 여러개 쓸 때, 동일한 window 셋팅에 쓰기위해 전역변수 사용
		gameManger.Render(hdc);
		EndPaint(g_hWnd, &ps);
		break;
	case WM_TIMER:
		hdc = BeginPaint(g_hWnd, &ps);
		gameManger.Update(hdc);
		EndPaint(g_hWnd, &ps);
		InvalidateRect(hWnd, NULL, true);
		break;
	case WM_DESTROY:
		KillTimer(hWnd, 0);
		PostQuitMessage(0);
		break;
	default:
		break;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

Object::Object()
{
	Initialize();
}

void Object::SetPos(int x, int y)
{
	pos.x = x; pos.y = y;
	SetCollider();
}

void Object::SetSize(int x, int y)
{
	size.x = x; size.y = y;
	halfSize.x = x / 2; halfSize.y = y / 2;
	SetCollider();
}

void Object::SetCollider()
{
	collider.left = pos.x - halfSize.x; 
	collider.top = pos.y - halfSize.y;
	collider.right = pos.x + halfSize.x;
	collider.bottom = pos.y + halfSize.y;
}

void Object::Move(int dx, int dy, const int& sw, const int& sh)
{
	int x = pos.x + dx;
	int y = pos.y + dy;
	
	if (x < 0 || x > sw - 40)
		x = pos.x;
	if (y < 0 || y > sh - 40)
		y = pos.y;


	SetPos(x, y);
}

void Object::Move(eDir dir, const int& sw, const int& sh)
{
	switch (dir)
	{
	case eDir::LEFT:
		Move(speed * -1, 0, sw, sh);
		break;
	case eDir::TOP:
		Move(0, speed * -1, sw, sh);
		break;
	case eDir::RIGHT:
		Move(speed, 0, sw, sh);
		break;
	case eDir::BOTTOM:
		Move(0, speed, sw, sh);
		break;
	default:
		break;
	}
}

void Object::Render(HDC hdc)
{
	Rectangle(hdc, collider.left, collider.top, collider.right, collider.bottom);
}

void Object::Initialize()
{
	pos = POINT{ 0,0 };
	size = POINT{ 0, 0 };
	halfSize = POINT{ 0, 0 };
	collider = RECT{ 0, 0,0,0 };
	hp = 0;
	speed = 0;
}

void Object::Update(HDC hdc, const int& sw, const int& sh)
{
}

Enumy::Enumy()
{
	isDestory = false;
	speed = 5;
	dirY = 1;
	curMissileIdx = 0;
	randomCount = 0;
	for (int i = 0; i < 10; ++i)
	{
		missile[i].SetSize(50, 50);
		missile[i].SetPos(pos.x, pos.y);
	}
}

void Enumy::Render(HDC hdc)
{
	if (isDestory) return;
	HBRUSH hBrush = CreateHatchBrush(HS_CROSS, RGB(0, 0, 255));
	HBRUSH hOldPen = (HBRUSH)SelectObject(hdc, hBrush);
	Rectangle(hdc, collider.left, collider.top, collider.right, collider.bottom);
	SelectObject(hdc, hOldPen);
	DeleteObject(hBrush);
}

void Enumy::RepeatMove(const int& sw, const int& sh)
{
	
	if (pos.y < 20 || pos.y > sh - 50)
		dirY *= -1;

	Move(0, dirY * speed, sw, sh);


}

void Enumy::Update(HDC hdc, const int& sw, const int& sh)
{
	if (isDestory) return;
	RepeatMove(sw, sh);

	for (int i = 0; i < 10; ++i)
	{
		missile[i].Update(hdc, sw, sh);
		missile[i].Render(hdc);
	}

	randomCount = std::rand() % 11 + 1;
}

void Enumy::Shot()
{
	missile[curMissileIdx].Shot(eDir::RIGHT, pos.x, pos.y);
	curMissileIdx = ++curMissileIdx % 10;
}

Player::Player()
{
	isDestory = false;
	speed = 10;
	curMissileIdx = 0;

	for (int i = 0; i < 10; ++i)
	{
		missile[i].SetSize(50, 50);
		missile[i].SetPos(pos.x, pos.y);
	}
}

void Player::Render(HDC hdc)
{
	if (isDestory) return;

	HBRUSH hBrush = CreateHatchBrush(HS_CROSS, RGB(255, 0, 0));
	HBRUSH hOldPen = (HBRUSH)SelectObject(hdc, hBrush);
	Rectangle(hdc, collider.left, collider.top, collider.right, collider.bottom);
	SelectObject(hdc, hOldPen);
	DeleteObject(hBrush);
}

void Player::Shot()
{
	missile[curMissileIdx].Shot(eDir::RIGHT, pos.x, pos.y);
	curMissileIdx = ++curMissileIdx % 10;
}

void Player::Update(HDC hdc, const int& sw, const int& sh)
{
	if (isDestory) return;
	for (int i = 0; i < 10; ++i)
	{
		missile[i].Update(hdc, sw, sh);
		missile[i].Render(hdc);
	}
}

Manager::Manager()
{
	width = 0;
	height = 0;
	curMissileIdx = 0;
}

void Manager::SetScreenSize(int w, int h)
{
	width = w;
	height = h;
}

void Manager::InitGame()
{
	// Set Objects
	objs.push_back(&player);
	player.SetSize(width / 40, height / 10);
	player.SetPos(width / 10, height / 2);

	objs.push_back(&enumy);
	enumy.SetSize(width / 40, height / 10);
	enumy.SetPos(width / 10 * 9, height / 10);

	for (Missile& m : missiles)
	{
		objs.push_back(&m);
		m.SetSize(width / 20, height / 20);
	}
}

void Manager::Render(HDC hdc)
{
	for (int i = 0; i < objs.size(); ++i)
	{
		if (!objs[i]) continue;

		objs[i]->Render(hdc);
	}
}

void Manager::Update(HDC hdc)
{
	player.Update(hdc, width, height);
	enumy.Update(hdc, width, height);

	for (int i = 0; i < MISSILECOUNT; ++i)
	{
		missiles[i].Update(hdc, width, height);
		if (missiles[i].dir == eDir::RIGHT)
		{
			if (RectInRect(missiles[i].collider, enumy.collider))
			{
				enumy.isDestory = true;
				missiles[i].Reset();
			}
		}
		else
		{
			if (RectInRect(missiles[i].collider, player.collider))
			{
				player.isDestory = true;
				missiles[i].Reset();
			}
		}
	}

	if (enumy.randomCount > 9)
		Shot(eDir::LEFT, enumy.pos.x, enumy.pos.y);
}

void Manager::Shot(eDir dir, int x, int y)
{
	if (!missiles[curMissileIdx].isShot)
		missiles[curMissileIdx].Shot(dir, x, y);
	curMissileIdx = ++curMissileIdx % MISSILECOUNT;
}

bool Manager::RectInRect(RECT rc1, RECT rc2)
{
	if (rc1.right < rc2.left || rc1.left > rc2.right ||
		rc1.top > rc2.bottom || rc1.bottom < rc2.top)
	{
		return false;
	}

	return true;
}

Missile::Missile()
{
	SetSize(50, 50);
	atk = 10;
	speed = 20;
	isShot = false;
	isErase = true;
	dir = eDir::LEFT;
}

void Missile::Reset()
{
	isShot = false;
	isErase = true;
}

void Missile::EraseMove(const int& sw, const int& sh)
{
	if (isErase) return;

	if (pos.x < 0 || pos.x > sw || pos.y < 0 || pos.y > sh)
	{
		Reset();
		return;
	}
	int direction = dir == eDir::RIGHT ? 1 : -1;
	pos.x += speed * direction;
	SetPos(pos.x, pos.y);
	std::wstring ws = L"값은 " + std::to_wstring(pos.x) + L"입니다\n";
	OutputDebugString(ws.c_str());
}

void Missile::Render(HDC hdc)
{
	if (isErase) return;

	Ellipse(hdc, collider.left, collider.top, collider.right, collider.bottom);
	//std::wstring ws = L"aaaaa입니다\n";
	//OutputDebugString(ws.c_str());
}

void Missile::Update(HDC hdc, const int& sw, const int& sh)
{
	if (isShot)
	{
		EraseMove(sw, sh);
	}
}

void Missile::Shot(eDir dir, int x, int y)
{
	this->dir = dir;
	isShot = true;
	isErase = false;

	SetPos(x, y);
}
