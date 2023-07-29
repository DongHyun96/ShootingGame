#include "Framework.h"
#include "Line.h"


Line::Line()
{
}

Line::Line(Point start, Point end)
	:start(start), end(end)
{
}

Line::~Line()
{
}

void Line::Render(HDC hdc)
{
	MoveToEx(hdc, start.x, start.y, nullptr);
	LineTo(hdc, end.x, end.y);
}
