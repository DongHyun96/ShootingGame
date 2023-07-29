#include "Framework.h"
#include "CollisionScene.h"


CollisionScene::CollisionScene()
{
	circle1 = new Circle(Point(200, 200), 50);
	circle2 = new Circle(Point(200, 400), 50);
	rect1	= new Rect(Point(400, 200), Point(100, 200));
	rect2	= new Rect(Point(100, 100), Point(50, 50));

	line1	= new Line(Point(0, 0), Point(500, 500));
	line2	= new Line(Point(300, 100), Point(100, 300));

	redBrush	= CreateSolidBrush(RGB(255, 0, 0));
	blueBrush	= CreateSolidBrush(RGB(0, 0, 255));
}

CollisionScene::~CollisionScene()
{
	delete circle1;
	delete circle2;
	delete rect1;
	delete rect2;

	delete line1;
	delete line2;


	DeleteObject(redBrush);
	DeleteObject(blueBrush);
}

void CollisionScene::Update()
{
	//circle1->Pos().x++;

	if (GetAsyncKeyState('A'))
		rect2->Pos().x -= 20.f;
	if (GetAsyncKeyState('D'))
		rect2->Pos().x += 20.f;
	if (GetAsyncKeyState('W'))
		rect2->Pos().y -= 20.f;
	if (GetAsyncKeyState('S'))
		rect2->Pos().y += 20.f;

	line1->end = mousePos;

	//rect2->Pos() = mousePos;
}

void CollisionScene::Render(HDC hdc)
{
	circle2->Render(hdc);
	rect1->Render(hdc);

	if (Collision::Collision(line1, line2))
		SelectObject(hdc, redBrush);
	else
		SelectObject(hdc, blueBrush);

	circle1->Render(hdc);
	rect2->Render(hdc);

	line1->Render(hdc);
	line2->Render(hdc);


	wstring str;

	str = L"MousePos : " + to_wstring((int)mousePos.x) + L", " + to_wstring((int)mousePos.y);

	TextOut(hdc, 0, 0, str.c_str(), str.size());
}
