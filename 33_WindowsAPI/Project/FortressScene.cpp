#include "Framework.h"
#include "FortressScene.h"

FortressScene::FortressScene()
{
	tank = new Tank();
	brick = new Rect(WIN_CENTER, Point(100, 100));
}

FortressScene::~FortressScene()
{
	delete tank;
	delete brick;
}

void FortressScene::Update()
{
	tank->Update();

	vector<CannonBall*> balls = tank->GetBalls()->GetObjects();

	for (CannonBall* ball : balls)
	{
		Point point;

		if (Collision::Collision(brick, ball->GetBody(), &point))
		{
			// Left
			/*if (point.x == rect->Left())
			{
				ball->GetBody()->Pos().x = rect->Left() - ball->GetBody()->Radius();
				ball->GetDir().x *= -1;
			}
			else if (point.x == rect->Right())
			{
				ball->GetBody()->Pos().x = rect->Right() + ball->GetBody()->Radius();
				ball->GetDir().x *= -1;
			}
			else if (point.y == rect->Top())
			{
				ball->GetBody()->Pos().y = rect->Top() - ball->GetBody()->Radius();
				ball->GetDir().y *= -1;
			}
			else if (point.y == rect->Bottom())
			{
				ball->GetBody()->Pos().y = rect->Bottom() + ball->GetBody()->Radius();
				ball->GetDir().y *= -1;
			}*/

			Vector2 dir = ball->GetBody()->Pos() - brick->Pos();

			Point size = brick->Size();

			Vector2 LU = Vector2(-size.x, -size.y); // Left UP
			Vector2 RU = Vector2(+size.x, -size.y); // Right Up
			Vector2 LD = Vector2(-size.x, +size.y); 
			Vector2 RD = Vector2(+size.x, +size.y); 
			// Normalize 할 필요 없음, 어차피 사이인지만 판단하기 위함

			if (Vector2::IsBetween(dir, LU, LD) && ball->GetBody()->Pos().x < brick->Pos().x)
			{
				// Left
				ball->GetDir().x *= -1;
				ball->GetBody()->Pos().x = brick->Left() - ball->GetBody()->Radius();
			}
			else if (Vector2::IsBetween(dir, RU, RD) && ball->GetBody()->Pos().x > brick->Pos().x)
			{
				// Right
				ball->GetDir().x *= -1;
				ball->GetBody()->Pos().x = brick->Right() + ball->GetBody()->Radius();
			}
			else if (Vector2::IsBetween(dir, LU, RU) && ball->GetBody()->Pos().y < brick->Pos().y)
			{
				// Up
				ball->GetDir().y *= -1;
				ball->GetBody()->Pos().y = brick->Top() - ball->GetBody()->Radius();
			}
			else if (Vector2::IsBetween(dir, LD, RD) && ball->GetBody()->Pos().y > brick->Pos().y)
			{
				// Down
				ball->GetDir().y *= -1;
				ball->GetBody()->Pos().y = brick->Bottom() + ball->GetBody()->Radius();
			}
			// Right
			// Top
			// Bottom
		}
	}
}

void FortressScene::Render(HDC hdc)
{
	brick->Render(hdc);
	tank->Render(hdc);
}
