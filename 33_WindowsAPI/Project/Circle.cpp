#include "Framework.h"
#include "Circle.h"


Circle::Circle()
{
}

Circle::Circle(Point pos, float radius)
	:pos(pos), radius(radius)
{
}

Circle::~Circle()
{
}

void Circle::Render(HDC hdc)
{
	Ellipse(hdc, Left(), Top(), Right(), Bottom());
}
