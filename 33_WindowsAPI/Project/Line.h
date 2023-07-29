#pragma once
class Line
{
public:
	Line();
	Line(Point start, Point end);
	~Line();

	void Render(HDC hdc);

	Point start;
	Point end;

private:
};
