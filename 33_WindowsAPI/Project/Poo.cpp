#include "Framework.h"
#include "Poo.h"


Poo::Poo()
{
	COLORREF color = RGB(rand() % 256, rand() % 256, rand() % 256);

	brush	= CreateSolidBrush(color);
	pen		= CreatePen(PS_SOLID, 1, color);

	speed	= rand() % 10 + 1;


	float radius = rand() % 40 + 10;

	int start	= radius;
	int end		= WIN_WIDTH - radius;

	float x = rand() % (end - start) + start;

	Point pos(x, -radius); // y -> 화면 밖에서 시작

	body = new Circle(pos, radius);
}

Poo::~Poo()
{
	delete body;
}

void Poo::Update()
{
	Move();
}

void Poo::Render(HDC hdc)
{
	SelectObject(hdc, pen);
	SelectObject(hdc, brush);
	body->Render(hdc);
}

void Poo::Move()
{
	body->Pos().y += speed;
}
