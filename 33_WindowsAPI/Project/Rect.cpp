#include "Framework.h"
#include "Rect.h"


Rect::Rect()
{
}

Rect::Rect(Point pos, Point size)
	:pos(pos), size(size)
{
}

Rect::Rect(float left, float top, float right, float bottom)
{
	pos.x = (left + right) * 0.5f;
	pos.y = (bottom + top) * 0.5f;

	size.x = right - left;
	size.y = bottom - top;
}

Rect::~Rect()
{
}

void Rect::SetRect(float left, float top, float right, float bottom)
{
	pos.x = (left + right) * 0.5f;
	pos.y = (bottom + top) * 0.5f;

	size.x = right - left;
	size.y = bottom - top;
}

void Rect::Render(HDC hdc)
{
	Rectangle(hdc, Left(), Top(), Right(), Bottom());
}
