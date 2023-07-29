#include "Framework.h"
#include "Collision.h"

bool Collision::Collision(Point point, Circle* circle)
{
	float distance = Point::Distance(point, circle->Pos());

	return distance < circle->Radius(); // °°´Ù´Â »©¾ß ¾È ÀÌ»óÇØÁü
}

bool Collision::Collision(Circle* circle, Point point)
{
	return Collision(point, circle);
}

bool Collision::Collision(Circle* c1, Circle* c2)
{
	float distance = Point::Distance(c1->Pos(), c2->Pos());

	return distance < c1->Radius() + c2->Radius();
}

bool Collision::Collision(Point point, Rect* rect)
{
	float x = abs(point.x - rect->Pos().x);
	float y = abs(point.y - rect->Pos().y);

	if (x < rect->Size().x * 0.5f && y < rect->Size().y * 0.5f)
		return true;

	return false;
}

bool Collision::Collision(Rect* rect, Point point)
{
	return Collision(point, rect);
}

bool Collision::Collision(Rect* r1, Rect* r2)
{
	float x = abs(r1->Pos().x - r2->Pos().x);
	float y = abs(r1->Pos().y - r2->Pos().y);

	float sizeX = (r1->Size().x + r2->Size().x) * 0.5f;
	float sizeY = (r1->Size().y + r2->Size().y) * 0.5f;

	if (x < sizeX && y < sizeY)
		return true;

	return false;
}

bool Collision::Collision(Rect* rect, Circle* circle, OUT Point* point)
{
	Point temp;

	if (point == nullptr)
		point = &temp;

	point->x = min(max(rect->Left(), circle->Pos().x), rect->Right());
	point->y = min(max(rect->Top(), circle->Pos().y), rect->Bottom());

	return Collision(*point, circle);
}

bool Collision::Collision(Circle* circle, Rect* rect, OUT Point* point)
{
	return Collision(rect, circle, point);
}

bool Collision::Collision(Line* l1, Line* l2)
{
	Vector2 v1 = l2->start - l1->start;
	Vector2 v2 = l2->end - l1->start;
	Vector2 f1 = l1->end - l1->start;

	Vector2 v3 = l1->start - l2->start;
	Vector2 v4 = l1->end - l2->start;
	Vector2 f2 = l2->end - l2->start;

	if (Vector2::IsBetween(f1, v1, v2) && Vector2::IsBetween(f2, v3, v4))
		return true;

	return false;
}
