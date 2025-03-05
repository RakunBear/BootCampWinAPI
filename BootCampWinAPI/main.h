#pragma once
#include <Windows.h>
#include <iostream>
#include <vector>


enum class SelectState
{
	None,
	Drag,
};
enum class ContactDir : uint8_t
{
	None   = 0b00000000,
	Left   = 0b00000001,
	Top	   = 0b00000010,
	Right  = 0b00000100,
	Bottom = 0b00001000,
};
enum class CollidState
{
	None,
	Stay,
};

enum class ShapeType : uint8_t
{
	Square,
	Star
};

enum class ObjectType : uint8_t
{
	Car,
	StartBox,
	Destroyer,
	BigSquare,
	SmallSquare,
};

class Object;

class GameManager
{
public:
	std::vector<Object*> objects;
	void SetHDC(HDC hdc);
	void UpdateCollid();
	void Render();
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

class Collid
{
protected:
	RECT _collider;
	CollidState _collidState;
public:
	Object& object;
public:
	Collid(Object& obj) : _collider(RECT{0,0,0,0}), 
		_collidState(CollidState::None), object{obj} {};
	uint8_t IsColliding(const RECT& otherCollid);
	virtual void OnTriggerEnter(Collid& otherCollid);
	virtual void OnTriggerStay(Collid& otherCollid);
	virtual void OnTriggerExit(Collid& otherCollid);
	CollidState CheckCollidState(Collid& otherCollid);
	bool PointInRect(POINT ptMouse);
	void SetRect(int x, int y, int width, int height);
	const RECT& GetRect();
};

class Object
{
protected:
	POINT _pos;
	int _width, _height;
	bool _isDestroyed;
	Collid* _collid;
	SelectState _selectState;
	HDC _hdc;
public:
	ObjectType type;
	bool isDrag;
	Object* _parent;
	std::vector<Object*> _childs;

public:
	Object();
	~Object();
	virtual void Initialize();
	void SetHDC(HDC hdc);
	void SetPos(int x, int y);
	void SetSize(int width, int height);
	void Move(POINT movePoint);
	void Move(int x, int y);
	void RenderRect();
	virtual void Render();
	virtual void Update(Object obj);
	Collid* GetCollider();
	void Destroy();
};

class Car : public Object
{
public:
	Car();
	void RenderRect(HDC hdc, int x, int y, int width, int height);
	void RenderRectAtCenter(HDC hdc, int x, int y, int width, int height);
	void RenderEllipse(HDC hdc, int x, int y, int width, int height);
	void RenderEllipseAtCenter(HDC hdc, int x, int y, int width, int height);
	void Render() override;
};

class StarBox : public Object
{
private:
	int _spaceHeight;
	bool _isStar;
public:
	ShapeType shapeType;
public:
	StarBox();
	bool CanBeStar();
	void Render() override;
	void RenderStar();
};

class Destroyer : public Object
{
public:
	Destroyer();
	void Render() override;
};

class BigSquare : public Object
{
public:
	BigSquare();
	void Render() override;
};

class SmallSquare : public Object
{
public:
	SmallSquare();
	void Render() override;
};