#include "Framework.h"
#include "ArkaBall.h"


ArkaBall::ArkaBall(Point pos, float radius)
{
	body = new Circle(pos, radius);
	hBrush = CreateSolidBrush(COLOR_GRAY);

	dir = Vector2(+1, -1).GetNormal();
}

ArkaBall::~ArkaBall()
{
	delete body;

	DeleteObject(hBrush);
}

void ArkaBall::Update()
{
	if (GetAsyncKeyState(VK_SPACE))
		isPlay = true;

	if (isPlay)
	{
		Move();
		CollisionWall();
		CollisionPlayer();
		CollisionBricks();
	}
	else
	{
		Point pos =
		{
			playerInfo->GetBody()->Pos().x,
			playerInfo->GetBody()->Top() - body->Radius()
		};

		body->Pos() = pos;
	}

	if (bricksInfo->IsClear())
	{
		bricksInfo->Clear();
		bricksInfo->Stage2();

		Initialize();
	}
}

void ArkaBall::Render(HDC hdc)
{
	SelectObject(hdc, hBrush);
	body->Render(hdc);
}

void ArkaBall::Move()
{
	body->Pos() += dir * speed * Time::Delta();
}

void ArkaBall::Initialize()
{
	isPlay = false;

	Point pos =
	{
		playerInfo->GetBody()->Pos().x,
		playerInfo->GetBody()->Top() - body->Radius()
	};

	body->Pos() = pos;

	dir = Vector2(+1, -1).GetNormal();

	playerInfo->GetBody()->Pos().x = WIN_CENTER.x;

}

void ArkaBall::CollisionWall()
{
	if (body->Left() < 0) // 왼쪽 벽에 충돌했을 때
	{
		dir.x *= -1;
		body->Pos().x = body->Radius();
	}

	if (body->Right() > WIN_WIDTH)
	{
		dir.x *= -1;
		body->Pos().x = WIN_WIDTH - body->Radius();
	}

	if (body->Top() < 0)
	{
		dir.y *= -1;
		body->Pos().y = body->Radius();
	}

	if (body->Bottom() > WIN_HEIGHT)
		Initialize();
}

void ArkaBall::CollisionPlayer()
{
	if (Collision::Collision(playerInfo->GetBody(), this->GetBody()))
	{
		Point pos =
		{
			playerInfo->GetBody()->Pos().x,
			playerInfo->GetBody()->Bottom()
		};

		dir = this->GetBody()->Pos() - pos;
		dir.Normalize();
	}
}

void ArkaBall::CollisionBricks()
{
	vector<ArkaBrick*> vector = bricksInfo->GetObjects();

	for (ArkaBrick* brick : vector)
	{
		if (brick->GetHP() <= 0)
			continue;

		Point point;

		if (Collision::Collision(brick->GetBody(), this->GetBody(), &point))
		{

			Vector2 dir = this->GetBody()->Pos() - brick->GetBody()->Pos();

			Point size = brick->GetBody()->Size();

			Vector2 LU = Vector2(-size.x, -size.y); // Left UP
			Vector2 RU = Vector2(+size.x, -size.y); // Right Up
			Vector2 LD = Vector2(-size.x, +size.y);
			Vector2 RD = Vector2(+size.x, +size.y);
			// Normalize 할 필요 없음, 어차피 사이인지만 판단하기 위함

			if (Vector2::IsBetween(dir, LU, LD) && this->GetBody()->Pos().x < brick->GetBody()->Pos().x)
			{
				// Left
				this->dir.x *= -1;
				this->GetBody()->Pos().x = brick->GetBody()->Left() - this->GetBody()->Radius();
				brick->GetHP()--;
			}
			else if (Vector2::IsBetween(dir, RU, RD) && this->GetBody()->Pos().x > brick->GetBody()->Pos().x)
			{
				// Right
				this->dir.x *= -1;
				this->GetBody()->Pos().x = brick->GetBody()->Right() + this->GetBody()->Radius();
				brick->GetHP()--;

			}
			else if (Vector2::IsBetween(dir, LU, RU) && this->GetBody()->Pos().y < brick->GetBody()->Pos().y)
			{
				// Up
				this->dir.y *= -1;
				this->GetBody()->Pos().y = brick->GetBody()->Top() - this->GetBody()->Radius();
				brick->GetHP()--;

			}
			else if (Vector2::IsBetween(dir, LD, RD) && this->GetBody()->Pos().y > brick->GetBody()->Pos().y)
			{
				// Down
				this->dir.y *= -1;
				this->GetBody()->Pos().y = brick->GetBody()->Bottom() + this->GetBody()->Radius();
				brick->GetHP()--;

			}

		}
	}
}
