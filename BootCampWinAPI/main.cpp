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
BigSquare bigSquare[2];
SmallSquare smallSquare;
GameManager gameManager;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpszCmdParam, _In_ int nCmdShow)
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
		gameManager.objects.push_back(&car);
		/* Set Box */
		for (int i = 0; i < (sizeof(starBoxs) / sizeof(starBoxs[0])); ++i)
		{
			gameManager.objects.push_back(&starBoxs[i]);
			starBoxs[i].SetSize(50,50);
			starBoxs[i].SetPos(100 + (i * 50), 600);
		}
		gameManager.objects.push_back(&destroyer);
		destroyer.SetPos(500, 100);
		destroyer.SetSize(100,100);

		for (int i = 0; i < 2; ++i)
		{
			gameManager.objects.push_back(&bigSquare[i]);
			bigSquare->SetPos(200 + 150 * i, 200);
			bigSquare->SetSize(150, 150);
		}
		gameManager.objects.push_back(&smallSquare);
		smallSquare.SetPos(250, 200);
		smallSquare.SetSize(50, 50);
		bigSquare[0]._childs.push_back(&smallSquare);
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
	HDC hdc;
	PAINTSTRUCT ps;
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
			car.Move(-10, 0);
			InvalidateRect(g_hWnd, NULL, true);
			break;
		case 'd': case 'D':
			hdc = BeginPaint(g_hWnd, &ps);
			car.Move(10, 0);
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
		if (car.GetCollider()->PointInRect(mouse.point))
		{
			car.isDrag = true;
			break;
		}
		for (int i = 0; i < (sizeof(starBoxs) / sizeof(starBoxs[0])); ++i)
		{
			if (starBoxs[i].GetCollider()->PointInRect(mouse.point))
			{
				starBoxs[i].isDrag = true;
				selectedIdx = i;
				break;
			}
		}
		if (destroyer.GetCollider()->PointInRect(mouse.point))
		{
			destroyer.isDrag = true;
			break;
		}

		InvalidateRect(g_hWnd, NULL, true);
		break;
	case WM_LBUTTONUP:
		car.isDrag = false;
		starBoxs[selectedIdx].isDrag = false;
		destroyer.isDrag = false;

		if (starBoxs[selectedIdx].GetCollider()->
			CheckCollidState(*(destroyer.GetCollider()))
			== CollidState::Stay)
		{
			starBoxs[selectedIdx].Destroy();
		}
		InvalidateRect(g_hWnd, NULL, true);
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
			car.Move(mouse.movedPoint);
		}

		for (int i = 0; i < (sizeof(starBoxs) / sizeof(starBoxs[0])); ++i)
		{
			if (starBoxs[i].isDrag)
				starBoxs[i].Move(mouse.movedPoint);
		}

		if (destroyer.isDrag)
		{
			destroyer.Move(mouse.movedPoint);
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

		gameManager.SetHDC(hdc);
		gameManager.UpdateCollid();


		wsprintf(szText, L"Car State : %s", car.isDrag ? L"Drag" : L"No Drag");
		TextOut(hdc, 20, 20, szText, wcslen(szText));
		wsprintf(szText, L"MousePos : %d %d", mouse.curX, mouse.point.y);
		TextOut(hdc, 20, 40, szText, wcslen(szText));
		//car.Render();

		//for (int i = 0; i < (sizeof(starBoxs) / sizeof(starBoxs[0])); ++i)
		//{
		//	starBoxs[i].Render();
		//}

		//destroyer.Render();
		gameManager.Render();

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

#pragma region ���Ǻ�
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

Car::Car()
{
	Initialize();
	_pos = POINT{ 300, 300 };
	_width = { 140 };
	_height = { 50 };
	_collid->SetRect(_pos.x, _pos.y, _width, _height);
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

void Car::Render()
{
	if (_isDestroyed) return;

	const RECT& rt = _collid->GetRect();
	// ��(�׵θ�)�� �귯��(ä��� ����) ����
	HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0)); 
	// ������ ��� �귯�ø� ����
	HPEN hOldPen = (HPEN)SelectObject(_hdc, hPen);
	// �׸���
	RenderRect(_hdc, rt.left, rt.top, rt.right - rt.left, rt.bottom - rt.top); // collider
	// ���� ��� �귯�÷� ����
	SelectObject(_hdc, hOldPen);
	// ������ ��� �귯�� ����
	DeleteObject(hPen);

	RenderRect(_hdc, _pos.x + 20, _pos.y, 100, 20); // �Ѳ�
	RenderRect(_hdc, _pos.x, _pos.y + 20, 140, 30); // MainFrame
	RenderEllipse(_hdc, _pos.x + 20, _pos.y + 40, 20, 20); // L Tier
	RenderEllipse(_hdc, _pos.x + 100, _pos.y + 40, 20, 20); // R Tier

}

StarBox::StarBox()
{
	Initialize();
	type = ObjectType::StartBox;
	_spaceHeight = 200;
	_isStar = false;
	shapeType = ShapeType::Square;
}

bool StarBox::CanBeStar()
{
	if (_pos.y <= _spaceHeight)
	{
		shapeType = ShapeType::Star;
		return true;
	}

	shapeType = ShapeType::Square;
	return false;
}

void StarBox::Render()
{
	if (_isDestroyed) return;

	if (CanBeStar())
		RenderStar();
	else
		RenderRect();
}



void StarBox::RenderStar()
{
	/* collider */
	HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	HPEN hOldPen = (HPEN)SelectObject(_hdc, hPen);
	RenderRect();
	SelectObject(_hdc, hOldPen);
	DeleteObject(hPen);
	
	const RECT& rt = _collid->GetRect();
	MoveToEx(_hdc, rt.left, rt.top, NULL);
	LineTo(_hdc, rt.right, rt.bottom);
	LineTo(_hdc, rt.left, (rt.bottom + rt.top) / 2);
	LineTo(_hdc, rt.right, rt.top);
	LineTo(_hdc, (rt.right + rt.left) / 2, rt.bottom);
	LineTo(_hdc, rt.left, rt.top);
}

Destroyer::Destroyer()
{
	Initialize();
}

void Destroyer::Render()
{
	/* collider */
	HPEN hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	HPEN hOldPen = (HPEN)SelectObject(_hdc, hPen);
	Rectangle(_hdc, _collid->GetRect().left, _collid->GetRect().top, _collid->GetRect().right, _collid->GetRect().bottom);
	SelectObject(_hdc, hOldPen);
	DeleteObject(hPen);
}

void Object::RenderRect()
{
	Rectangle(_hdc, _collid->GetRect().left, _collid->GetRect().top, _collid->GetRect().right, _collid->GetRect().bottom);
}

void Object::Render()
{
	if (_isDestroyed) return;
}

void Object::Update(Object obj)
{
	if (_isDestroyed) return;
}

Collid* Object::GetCollider()
{
	return _collid;
}

void Object::Destroy()
{
	_isDestroyed = true;
}

Object::Object()
{
	Initialize();
}

Object::~Object()
{
	if (_collid)
		delete _collid;
	if (_parent)
		delete _parent;
}

void Object::Initialize()
{
	_pos = POINT{ 0, 0 };
	_width = 0; _height = 0;
	_collid = new Collid(*this);
	_selectState = SelectState::None;
	_hdc = nullptr;
	_parent = nullptr;
	_childs;
	_isDestroyed = false;
	isDrag = false;
}

void Object::SetHDC(HDC hdc)
{
	_hdc = hdc;
}

void Object::SetPos(int x, int y)
{
	_pos.x = x; _pos.y = y;
	_collid->SetRect(x, y, _width, _height);
}

void Object::SetSize(int width, int height)
{
	_width = width; _height = height;
	_collid->SetRect(_pos.x, _pos.y, width, height);
}

void Object::Move(POINT movePoint)
{
	SetPos(_pos.x + movePoint.x, _pos.y + movePoint.y);
}

void Object::Move(int x, int y)
{
	SetPos(_pos.x + x, _pos.y + y);
}

bool Collid::PointInRect(POINT ptMouse)
{
	if ((ptMouse.x < _collider.left) || (ptMouse.x > _collider.right) || (ptMouse.y < _collider.top) || (ptMouse.y > _collider.bottom))
		return false;

	return true;
}

void Collid::SetRect(int x, int y, int width, int height)
{
	_collider.left = x; _collider.top = y;
	_collider.right = x + width; _collider.bottom = y + height;
}

const RECT& Collid::GetRect()
{
	return _collider;
}

uint8_t Collid::IsColliding(const RECT& otherCollid)
{
	uint8_t contactDir = (uint8_t)ContactDir::None;
	if (otherCollid.left <= _collider.left && _collider.left <= otherCollid.right)
		contactDir = contactDir | (uint8_t)ContactDir::Left;
	else
		contactDir = contactDir ^ (uint8_t)ContactDir::Left;
	if (otherCollid.left <= _collider.right && _collider.right <= otherCollid.right)
		contactDir = contactDir | (uint8_t)ContactDir::Right;
	else
		contactDir = contactDir ^ (uint8_t)ContactDir::Right;
	if (otherCollid.top <= _collider.top && _collider.top <= otherCollid.bottom)
		contactDir = contactDir | (uint8_t)ContactDir::Top;
	else
		contactDir = contactDir ^ (uint8_t)ContactDir::Top;
	if (otherCollid.top <= _collider.bottom && _collider.bottom <= otherCollid.bottom)
		contactDir = contactDir | (uint8_t)ContactDir::Bottom;
	else
		contactDir = contactDir ^ (uint8_t)ContactDir::Bottom;

	return contactDir;
}

void Collid::OnTriggerEnter(Collid& otherCollid)
{
	if (object.type == ObjectType::BigSquare 
		&& otherCollid.object.type == ObjectType::BigSquare)
	{
		otherCollid.object._childs = object._childs;
		object._childs.clear();
	}
}

void Collid::OnTriggerStay(Collid& otherCollid)
{
	if (object._parent != nullptr)
	{
		const RECT& pCollider = otherCollid.GetRect();
		_collider.left = _collider.left < pCollider.left ? pCollider.left : _collider.left;
		_collider.top = _collider.top < pCollider.top ? pCollider.top : _collider.top;
		_collider.right = _collider.right > pCollider.right ? pCollider.right : _collider.right;
		_collider.bottom = _collider.bottom > pCollider.bottom ? pCollider.bottom : _collider.bottom;
	}
}

void Collid::OnTriggerExit(Collid& otherCollid)
{
}

CollidState Collid::CheckCollidState(Collid& otherCollid)
{
	uint8_t b = IsColliding(otherCollid.GetRect());
	if (b == 0)
	{
		if ((int)_collidState > 0)
		{
			OnTriggerExit(otherCollid);
		}
	}
	else if (b > 0)
	{
		if (_collidState == CollidState::None)
		{
			OnTriggerEnter(otherCollid);
			_collidState = CollidState::Stay;
		}
		else
		{
			OnTriggerStay(otherCollid);
		}
	}

	if (object._parent != nullptr)
	{
		for (Object* childObj : object._childs)
		{
			CheckCollidState(*(childObj->GetCollider()));
		}
	}

	return _collidState;
}
#pragma endregion

void GameManager::SetHDC(HDC hdc)
{
	for (Object* pObj : gameManager.objects)
	{
		if (!pObj) continue;

		pObj->SetHDC(hdc);
	}
}

void GameManager::UpdateCollid()
{
	for (Object* pObj : gameManager.objects)
	{
		if (!pObj) continue;

		for (Object* pOtherObj : gameManager.objects)
		{
			if (!pOtherObj || pOtherObj == pObj)
				continue;

			pObj->GetCollider()->CheckCollidState(
				*(pOtherObj->GetCollider()));
		}
	}
}

void GameManager::Render()
{
	for (Object* obj : objects)
	{
		obj->Render();
	}
}

BigSquare::BigSquare()
{
	Initialize();
	type = ObjectType::BigSquare;
}

void BigSquare::Render()
{
	RenderRect();
}

SmallSquare::SmallSquare()
{
	Initialize();
	type = ObjectType::SmallSquare;
}

void SmallSquare::Render()
{
	RenderRect();
}
