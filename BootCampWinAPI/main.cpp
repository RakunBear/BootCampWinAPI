/*
	WinAPI (Windows Application Programming Interface)
	- �ü���� �������α׷� ������ ���� �����ϴ� �Լ��� ����

	�ڵ�(Handle) : ������ �� ��ü�� �����ϴ� �ε��� ��ȣ(����)
	�޽���(Message) : �����쿡�� �߻��ϴ� �̺�Ʈ�� �ü���� �����쿡 �����ϴ� ������ ����
*/

/*
	1. �ڵ��� �׸��� (�Լ�ȭ)
	2. a, dŰ�� �����̱�
		-> [����] mouse ��ġ��
	3. ���콺 �巡��&������� �����̱�
	4. ���� �Ǿ��!
		�ٴڿ� �׸� 10��, ���콺 �巡�׸� ���ؼ� ���� �̵�
		Ư�� ���� �̻� ��ġ�� ����� �ϸ� �׸� -> �� ������� �ٲ��
	5. ������� �ִ� ����
		5_1. ū ���� 2��, ���� ���� 1��
		5_2. ū ���� �ȿ��� ���� ���ڰ� ������� (����� �ִ� ����)
		5_3. ���� ���ڴ� ū ���ڸ� ��� �� ����.
		5_4. ū ���ڳ��� �ε����� ���� ���ڰ� �ε��� ���ڷ� �Ѿ (������� �Ѿ)
*/

#include "main.h"

HINSTANCE g_hinstance;	// ���α׷� �ν��Ͻ� �ڵ�
HWND g_hWnd;			// ������ �ڵ�
LPWSTR g_lpszClassName{ (LPWSTR)TEXT("������ API ����ϱ�") };
Mouse mouse;
Car car;
StarBox starBoxs[10];
Destroyer destroyer;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpszCmdParam, _In_ int nCmdShow)
{
	g_hinstance = hInstance;

	// ������ �������� ������ ����
	WNDCLASS wndClass;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = LoadCursor(g_hinstance, IDC_ARROW);
	wndClass.hIcon = LoadIcon(g_hinstance, IDI_APPLICATION);
	wndClass.hInstance = g_hinstance;
	wndClass.lpfnWndProc = WndProc; // �Լ��� �̸��� �޸��ּ�
	wndClass.lpszClassName = g_lpszClassName;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;  // | ; ��Ʈ ������

	RegisterClass(&wndClass);

	g_hWnd = CreateWindow(g_lpszClassName, g_lpszClassName, WS_OVERLAPPEDWINDOW, 50, 50, 1080, 720, NULL, NULL, g_hinstance, NULL);

	if (ShowWindow(g_hWnd, nCmdShow))
	{

	}
	else
	{
		/* Set Box */
		for (int i = 0; i < (sizeof(starBoxs) / sizeof(starBoxs[0])); ++i)
		{
			starBoxs[i].SetSize(50);
			starBoxs[i].SetPos(100 + (i * starBoxs[i].GetWidth()), 600);
		}
		destroyer.SetSize(100);
		OutputDebugString(L"Test\n");
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
	// static ���� : �Լ� ������ ����
	// ������ ������ �޸𸮰� �Ҵ� (���������� ����)
	// ���α׷� ���� �ÿ� �޸� ����
	// �ش� �Լ������� ������ ����
	static int dan = 2;
	wchar_t szText[128];

	/*���ڽ�*/
	static int selectedIdx = 0;

	// Logic
	switch (iMessage)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case 'a': case 'A':
			hdc = BeginPaint(g_hWnd, &ps);
			car.posX -= 10;
			InvalidateRect(g_hWnd, NULL, true);
			break;
		case 'd': case 'D':
			hdc = BeginPaint(g_hWnd, &ps);
			car.posX += 10;
			InvalidateRect(g_hWnd, NULL, true);
			break;
		default:
			break;
		}

		break;
	case WM_LBUTTONDOWN:
		/* GUGUDan */
		if (dan > 2)
			--dan;

		/* Mouse Mode Car */
		if (car.PointInRect(mouse.point, car.collider))
		{
			car.isDrag = true;
			break;
		}
		for (int i = 0; i < (sizeof(starBoxs) / sizeof(starBoxs[0])); ++i)
		{
			if (starBoxs[i].PointInRect(mouse.point))
			{
				starBoxs[i].isDrag = true;
				selectedIdx = i;
				break;
			}
		}
		if (destroyer.PointInRect(mouse.point))
		{
			destroyer.isDrag = true;
			break;
		}

		InvalidateRect(g_hWnd, NULL, true);
		break;
	case WM_LBUTTONUP:
		car.isDrag = false;
		
		starBoxs[selectedIdx].isDrag = false;
		if (destroyer.RectInRect(starBoxs[selectedIdx].GetCollider()))
		{
			starBoxs[selectedIdx].Destroy();
		}

		destroyer.isDrag = false;
		break;
	case WM_RBUTTONDOWN:
		/* GUGUDan */
		if (dan < 9)
			++dan;

		InvalidateRect(g_hWnd, NULL, true);
		break;
	case WM_MOUSEMOVE:
		// {Y 16bit}{X 16bit} <- 32bit
		//mousePosX = LOWORD(lParam);
		//mousePosY = HIWORD(lParam);
		mouse.Set(LOWORD(lParam), HIWORD(lParam));

		if (car.isDrag)
		{
			car.posX += mouse.movedPoint.x; car.posY += mouse.movedPoint.y;
		}

		for (int i = 0; i < (sizeof(starBoxs) / sizeof(starBoxs[0])); ++i)
		{
			if (starBoxs[i].isDrag)
				starBoxs[i].Move(mouse.movedPoint.x, mouse.movedPoint.y);
		}

		if (destroyer.isDrag)
		{
			destroyer.Move(mouse.movedPoint.x, mouse.movedPoint.y);
		}

		InvalidateRect(g_hWnd, NULL, true);
		break;
	case WM_PAINT:
		hdc = BeginPaint(g_hWnd, &ps);  // â ������ �� ��, ������ window ���ÿ� �������� �������� ���

		//// �׸��� ����
		//TextOut(hdc, 20, 20, TEXT("Hello, World"), strlen("Hello, World"));
		//wsprintf(szText/*���ڿ�����*/, L"Mouse X : %d, Y : %d"/*����*/, mousePosX, mousePosY/*��1,��2...*/);
		//TextOut(hdc, 20, 160, szText, wcslen(szText));

		 //������
		//for (int i = 2; i <= dan; ++i)
		//	for (int j = 1; j < 10; ++j)
		//	{
		//		wsprintf(szText, L"%d * %d = %d", i, j, i*j);
		//		TextOut(hdc, 20 + (100 * i), 80 + (20 * j), szText, wcslen(szText));
		//	}

		//Ellipse(hdc, 300, 300, 500, 500);
		//Rectangle(hdc, 500, 300, 700, 400);

		car.RenderCar(hdc, car.posX, car.posY);
		wsprintf(szText, L"Car State : %s", car.isDrag ? L"Drag" : L"No Drag");
		TextOut(hdc, 20, 20, szText, wcslen(szText));
		wsprintf(szText, L"MousePos : %d %d", mouse.curX, mouse.point.y);
		TextOut(hdc, 20, 40, szText, wcslen(szText));

		for (int i = 0; i < (sizeof(starBoxs) / sizeof(starBoxs[0])); ++i)
		{
			starBoxs[i].Render(hdc);
		}

		destroyer.Render(hdc);

		EndPaint(g_hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		break;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

Car::Car() : posX(250), posY(250), isDrag(false), _width(140), _height(60)
{
	this->collider = RECT{ this->posX, this->posY, this->posX + _width, this->posY + _height };
}

void Car::RenderRect(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x+width, y+height);
}

void Car::RenderRectAtCenter(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x - (x+width)/2, y - (y+height)/2, x + (x + width) / 2, y + (y + height) / 2);
}

void Car::RenderEllipse(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x+width, y+height);
}

void Car::RenderEllipseAtCenter(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x - (x + width) / 2, y - (y + height) / 2, x + (x + width) / 2, y + (y + height) / 2);
}

void Car::RenderCar(HDC hdc, int posX, int posY)
{
	// ��(�׵θ�)�� �귯��(ä��� ����) ����
	HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0)); 
	// ������ ��� �귯�ø� ����
	HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
	// �׸���
	collider.left = posX; collider.right = posX + _width; collider.top = posY; collider.bottom = posY + _height;
	RenderRect(hdc, collider.left, collider.top, collider.right - collider.left, collider.bottom - collider.top); // collider
	// ���� ��� �귯�÷� ����
	SelectObject(hdc, hOldPen);
	// ������ ��� �귯�� ����
	DeleteObject(hPen);

	RenderRect(hdc, posX + 20, posY, 100, 20); // �Ѳ�
	RenderRect(hdc, posX, posY + 20, 140, 30); // MainFrame
	RenderEllipse(hdc, posX + 20, posY + 40, 20, 20); // L Tier
	RenderEllipse(hdc, posX + 100, posY + 40, 20, 20); // R Tier

}

bool Car::PointInRect(POINT ptMouse, RECT rc)
{
	if ((ptMouse.x < rc.left) || (ptMouse.x > rc.right) || (ptMouse.y < rc.top) || (ptMouse.y > rc.bottom) )
		return false;

	return true;
}

Mouse::Mouse() :preX(0), preY(0), curX(0), curY(0)
{
	point = POINT{ curX, curY };
	movedPoint = POINT{ 0,0 };
}

void Mouse::Set(int x, int y)
{
	preX = curX; preY = curY;
	curX = x; curY = y;
	point.x = curX;
	point.y = curY;
	movedPoint.x = curX - preX;
	movedPoint.y = curY - preY;
}

StarBox::StarBox() : _x(0), _y(0), _width(50), _height(50), _spaceHeight(200), _isStar(false), isDrag(false), _isDestroyed(false)
{
	_collider = RECT{ _x, _y, _width, _height };
	type = ShapeType::Square;
}

void StarBox::SetPos(int x, int y)
{
	_x = x; _y = y;
	_collider = { _x, _y, _x + _width, _y + _height };
	_isStar = CanBeStar(_y);
}

void StarBox::Move(int x, int y)
{
	if (_isDestroyed) return;

	SetPos(_x + x, _y + y);
}

bool StarBox::CanBeStar(int y)
{
	if (y <= _spaceHeight)
	{
		type = ShapeType::Star;
		return true;
	}

	type = ShapeType::Square;
	return false;
}

bool StarBox::PointInRect(POINT ptMouse)
{
	if ((ptMouse.x < _collider.left) || (ptMouse.x > _collider.right) || (ptMouse.y < _collider.top) || (ptMouse.y > _collider.bottom))
		return false;

	return true;
}

void StarBox::Render(HDC hdc)
{
	if (_isDestroyed) return;

	if (_isStar)
		RenderStar(hdc);
	else
		RenderRect(hdc);
}

void StarBox::RenderRect(HDC hdc)
{
	Rectangle(hdc, _collider.left, _collider.top, _collider.right, _collider.bottom);
}

void StarBox::RenderStar(HDC hdc)
{
	/* collider */
	HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
	RenderRect(hdc);
	SelectObject(hdc, hOldPen);
	DeleteObject(hPen);

	MoveToEx(hdc, _collider.left, _collider.top, NULL);
	LineTo(hdc, _collider.right, _collider.bottom);
	LineTo(hdc, _collider.left, (_collider.bottom + _collider.top) / 2);
	LineTo(hdc, _collider.right, _collider.top);
	LineTo(hdc, (_collider.right + _collider.left) / 2, _collider.bottom);
	LineTo(hdc, _collider.left, _collider.top);
}

int StarBox::GetWidth()
{
	return _width;
}

void StarBox::SetSize(int width)
{
	_width = width;
	_height = width;
}

void StarBox::Destroy()
{
	_isDestroyed = true;
}

RECT StarBox::GetCollider()
{
	return _collider;
}

Destroyer::Destroyer() : _width(100)
{
	_point = POINT{ 100, 100 };
	_collider = { _point.x, _point.y, _point.x + _width, _point.y + _width };
}

void Destroyer::SetSize(int width)
{
	_width = width;
	_collider = { _point.x, _point.y, _point.x + _width, _point.y + _width };
}

void Destroyer::SetPos(int x, int y)
{
	_point.x = x; _point.y = y;
	_collider = { _point.x, _point.y, _point.x + _width, _point.y + _width };
}

void Destroyer::Move(int x, int y)
{
	SetPos(_point.x + x, _point.y + y);
}

bool Destroyer::PointInRect(POINT ptMouse)
{
	if ((ptMouse.x < _collider.left) || (ptMouse.x > _collider.right) || (ptMouse.y < _collider.top) || (ptMouse.y > _collider.bottom))
		return false;

	return true;
}

bool Destroyer::RectInRect(RECT rc2)
{
	if (_collider.right < rc2.left || _collider.left > rc2.right ||
		_collider.top > rc2.bottom || _collider.bottom < rc2.top)
	{
		return false;
	}

	return true;
}

void Destroyer::Render(HDC hdc)
{
	/* collider */
	HPEN hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
	Rectangle(hdc, _collider.left, _collider.top, _collider.right, _collider.bottom);
	SelectObject(hdc, hOldPen);
	DeleteObject(hPen);
}

RECT Destroyer::GetCollider()
{
	return _collider;
}
