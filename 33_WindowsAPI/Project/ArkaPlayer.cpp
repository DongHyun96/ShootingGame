#include "Framework.h"
#include "ArkaPlayer.h"


ArkaPlayer::ArkaPlayer()
{
	body = new Rect(Point(WIN_CENTER.x, WIN_HEIGHT * 0.9f), Point(100, 30));

	hBrush = CreateSolidBrush(COLOR_GRAY);
}

ArkaPlayer::~ArkaPlayer()
{
	delete body;
	DeleteObject(hBrush);
}

void ArkaPlayer::Update()
{
	Move();
}

void ArkaPlayer::Render(HDC hdc)
{
	SelectObject(hdc, hBrush);
	body->Render(hdc);
}

void ArkaPlayer::Move()
{
	if (GetAsyncKeyState('A'))
		body->Pos() += Vector2(-1, 0) * speed * Time::Delta();

	if (GetAsyncKeyState('D'))
		body->Pos() += Vector2(1, 0) * speed * Time::Delta();

	if (body->Left() < 0)
		body->Pos().x = body->Size().x * 0.5f;

	if (body->Right() > WIN_WIDTH)
		body->Pos().x = WIN_WIDTH - body->Size().x * 0.5f;
}

