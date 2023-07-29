#pragma once

namespace Collision
{
	bool Collision(Point point, Circle* circle);
	bool Collision(Circle* circle, Point point);

	bool Collision(Circle* c1, Circle* c2);

	bool Collision(Point point, Rect* rect);
	bool Collision(Rect* rect, Point point);

	bool Collision(Rect* r1, Rect* r2);

	bool Collision(Rect* rect, Circle* circle, OUT Point* point = nullptr);
	bool Collision(Circle* circle, Rect* rect, OUT Point* point = nullptr);

	bool Collision(Line* l1, Line* l2);
}
