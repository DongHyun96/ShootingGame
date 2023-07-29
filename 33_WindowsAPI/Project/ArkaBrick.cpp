#include "Framework.h"
#include "ArkaBrick.h"


ArkaBrick::ArkaBrick(Point pos, Point size, UINT hp)
	:curHP(hp)
{
	body = new Rect(pos, size);

	hBrush[0] = CreateSolidBrush(COLOR_RED);
	hBrush[1] = CreateSolidBrush(COLOR_ORANGE);
	hBrush[2] = CreateSolidBrush(COLOR_PINK);
	hBrush[3] = CreateSolidBrush(COLOR_MAGENTA);
	hBrush[4] = CreateSolidBrush(COLOR_YELLOW);

}

ArkaBrick::~ArkaBrick()
{
	delete body;

	for (UINT i = 0; i < 5; i++)
		DeleteObject(hBrush[i]);
	 
}

void ArkaBrick::Render(HDC hdc)
{
	if (curHP <= 0)
		return;

	SelectObject(hdc, hBrush[curHP - 1]);

	body->Render(hdc);
}
