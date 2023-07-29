#include "Framework.h"
#include "CannonBallManager.h"


CannonBallManager::CannonBallManager(UINT poolCount)
{
	for (UINT i = 0; i < poolCount; i++)
		objects.push_back(new CannonBall());
}

CannonBallManager::~CannonBallManager()
{
	for (CannonBall* ball : objects)
		delete ball;

	objects.clear();
}

void CannonBallManager::Update()
{
	for (CannonBall* ball : objects)
		ball->Update();				// ActiveÇÑ ballµé¸¸ updateµÊ
}

void CannonBallManager::Render(HDC hdc)
{
	for (CannonBall* ball : objects)
		ball->Render(hdc);		  // ActiveÇÑ ballµé¸¸ renderµÊ
}

void CannonBallManager::Fire(Point startPos, float angle, float power)
{
	for (CannonBall* ball : objects)
	{
		if (ball->IsActive())
			continue;

		ball->Fire(startPos, angle, power);

		break;
	}
}

void CannonBallManager::Fire(Point startPos, Vector2 dir, float power)
{
	for (CannonBall* ball : objects)
	{
		if (ball->IsActive())
			continue;

		ball->Fire(startPos, dir, power);

		break;
	}
}
