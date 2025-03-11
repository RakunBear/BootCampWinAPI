#include "Enumy.h"
#include "CommonFunction.h"

void Enumy::Init(POINT targetPos)
{
	pos.x = 0;
	pos.y = 0;
	size = 50;
	damage = 10;
	rcCollision = GetRectAtCenter(pos.x, pos.y, size, size);
	atk = 10;

	angle = 0;
	speed = 5.0f;
	isDead = true;
	colorBrush = CreateSolidBrush(RGB(255, 0, 0));

	this->targetPos = targetPos;
}

void Enumy::Release()
{
}

void Enumy::Update()
{
	if (OutOfScreen())
	{
		Dead();
	}

	Move();
}

void Enumy::Render(HDC hdc)
{
	if (isDead) return;

	oldBrush = (HBRUSH)SelectObject(hdc, colorBrush);
	RenderEllipseAtCenter(hdc, pos.x, pos.y, size, size);
	SelectObject(hdc, oldBrush);
}

void Enumy::Move()
{
	pos.x += (int)(speed * cosf(angle));
	pos.y += (int)(speed * sinf(angle));

	rcCollision = GetRectAtCenter(pos.x, pos.y, size, size);
}

void Enumy::Dead()
{
	isDead = true;
	SetRandom();
}

bool Enumy::GetDead()
{
    return isDead;
}

bool Enumy::OutOfScreen()
{
	if (pos.x < 0 || pos.x > WINSIZE_X || pos.y < 0 || pos.y > WINSIZE_Y)
	{
		return true;
	}
	return false;
}

void Enumy::SetRandom()
{
	int x = rand() % WINSIZE_X;
	int y = 0;

	Set(POINT{ x, y }, targetPos);
}

void Enumy::Set(POINT pos, POINT targetPos, float speed, int delayTime)
{
	this->pos = pos;
	int dx = targetPos.x - pos.x;
	int dy = targetPos.y - pos.y;
	float angle = atan2f(dy , dx);
	this->angle = angle;
	this->speed = speed;

	rcCollision = GetRectAtCenter(pos.x, pos.y, size, size);
	
	isDead = false;
}

bool Enumy::HitCheck(const RECT& target)
{
	if (isDead) return false;

	if (RectInRect(target, rcCollision))
	{
		return true;
	}
	return false;
}

const POINT& Enumy::GetPos()
{
    return pos;
}

float Enumy::GetAngle()
{
	return angle;
}

float Enumy::GetDistance()
{
	return (targetPos.x - pos.x) * (targetPos.x - pos.x) 
		+ (targetPos.y - pos.y) * (targetPos.y - pos.y);
}

const RECT& Enumy::GetRect()
{
	return rcCollision;
}

const int& Enumy::GetAtk()
{
	return atk;
}
