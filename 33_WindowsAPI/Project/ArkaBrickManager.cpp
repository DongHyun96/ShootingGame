#include "Framework.h"
#include "ArkaBrickManager.h"


ArkaBrickManager::ArkaBrickManager()
{
	Stage1();
}

ArkaBrickManager::~ArkaBrickManager()
{
	Clear();
}

void ArkaBrickManager::Render(HDC hdc)
{
	for (auto& brick : objects)
		brick->Render(hdc);
}

void ArkaBrickManager::Stage1()
{
	objects.push_back(new ArkaBrick(WIN_CENTER, Point(200, 200), 5));
}

void ArkaBrickManager::Stage2()
{
	UINT nX = 8;
	UINT nY = 5;

	Point startPos = Point(50, 50);
	Point size = Point(50, 20);

	Point interval = Point(10, 10);

	for (UINT i = 0; i < nX * nY; i++)
	{
		UINT x = i % nX;
		UINT y = i / nX;

		Point pos =
		{
			startPos.x + size.x * x + interval.x * x,
			startPos.y + size.y * y + interval.y * y
		};

		objects.push_back(new ArkaBrick(pos, size, y + 1));
	}
}

bool ArkaBrickManager::IsClear()
{
	for (ArkaBrick* brick : objects)
	{
		if (brick->GetHP() > 0)
			return false;
	}

	return true;
}

void ArkaBrickManager::Clear()
{
	for (ArkaBrick* brick : objects)
		delete brick;

	objects.clear();
}
