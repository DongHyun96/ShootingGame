#pragma once
class Circle
{
public:
	Circle();
	Circle(Point pos, float radius);
	~Circle();

	void Render(HDC hdc);

	float Left()	const { return pos.x - radius; }
	float Right()	const { return pos.x + radius; }
	float Top()		const { return pos.y - radius; }
	float Bottom()	const { return pos.y + radius; }

	Point& Pos()		{ return pos; }
	float& Radius()		{ return radius; }

private:
	Point pos		= {};
	float radius	= 0.f;
};
