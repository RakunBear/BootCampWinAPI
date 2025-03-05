#pragma once
#include <Windows.h>
#include <iostream>

enum class CollidState
{
	Enter,
	Stay,
	Exit
};

enum class ShapeType : uint8_t
{
	Square,
	Star
};

class Mouse
{
public:
	POINT point, movedPoint;
	int preX, preY;
	int curX, curY;
	Mouse();
	void Set(int x, int y);
};

class GameManager
{

};

class Object
{
private:
	POINT _pos;
	int _width, _height;
	bool _isDestroyed;
	RECT _collider;
	CollidState _collidState;
	HDC _hdc;
public:
	Object();
	void SetHDC(HDC hdc);
	bool PointInRect(POINT ptMouse);
	bool IsColliding(RECT rc2);
	void Render();
	void Update(Object obj);
	CollidState GetCollidState();
};

class Car
{
private:
	int _width, _height;
public:
	int posX, posY;
	bool isDrag;
	RECT collider;
	Car();
	void RenderRect(HDC hdc, int x, int y, int width, int height);
	void RenderRectAtCenter(HDC hdc, int x, int y, int width, int height);
	void RenderEllipse(HDC hdc, int x, int y, int width, int height);
	void RenderEllipseAtCenter(HDC hdc, int x, int y, int width, int height);
	void RenderCar(HDC hdc, int posX, int posY);
	bool PointInRect(POINT ptMouse, RECT rc);
};

class StarBox
{
private:
	int _x, _y;
	int _width, _height;
	int _spaceHeight;
	bool _isStar;
	bool _isDestroyed;
	RECT _collider;
public:
	bool isDrag;
	ShapeType type;
public:
	StarBox();
	void SetPos(int x, int y);
	void Move(int x, int y);
	bool CanBeStar(int y);
	bool PointInRect(POINT ptMouse);
	void Render(HDC hdc);
	void RenderRect(HDC hdc);
	void RenderStar(HDC hdc);
	int GetWidth();
	void SetSize(int width);
	void Destroy();
	RECT GetCollider();
};
class Destroyer
{
private:
	int _width;
	POINT _point;
	RECT _collider;
public:
	bool isDrag;
public:
	Destroyer();
	void SetSize(int width);
	void SetPos(int x, int y);
	void Move(int x, int y);
	bool PointInRect(POINT ptMouse);
	bool RectInRect(RECT rc2);
	void Render(HDC hdc);
	RECT GetCollider();
};