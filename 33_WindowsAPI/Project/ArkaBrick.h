#pragma once

#define MAX_HP 5

class ArkaBrick
{
public:
	ArkaBrick(Point pos, Point size, UINT hp = 1);
	~ArkaBrick();

	void Render(HDC hdc);

	UINT& GetHP() { return curHP; }
	Rect* GetBody() { return body; }

private:
	Rect* body = nullptr;

	UINT curHP = 1;

	HBRUSH hBrush[MAX_HP];
};
