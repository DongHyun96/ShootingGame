#include "Framework.h"
#include "Shooting_Item.h"


Shooting_Item::Shooting_Item(ItemType type, Texture* texture)
	:type(type), texture(texture)
{
	body = new Rect(WIN_CENTER, Point(50, 50));
}

Shooting_Item::~Shooting_Item()
{
	delete body;
}

void Shooting_Item::Update()
{
	if (!isActive)
		return;

	CheckTimeElapsed();

	Move();
	HandleCollisionWall();
	
}

void Shooting_Item::Render(HDC hdc)
{
	if (!isActive)
		return;

	texture->Render(body);
}

void Shooting_Item::Spawn(const Point& spawnPos)
{
	isActive = true;

	body->Pos() = spawnPos;

	direction = {};

	while (direction.Length() == 0.f)
		direction = Vector2(GetRandom(-1.f, 1.f), GetRandom(-1.f, 1.f));

	direction.Normalize();

	timeElapsed = 0.f;
}

void Shooting_Item::Move()
{
	body->Pos() += direction * speed * Time::Delta();
}

void Shooting_Item::HandleCollisionWall()
{
	if (body->Left() < 0)
	{
		direction.x *= -1;
		body->Pos().x = body->Size().x * 0.5;
	}

	if (body->Right() > WIN_WIDTH)
	{
		direction.x *= -1;
		body->Pos().x = WIN_WIDTH - body->Size().x * 0.5;
	}

	if (body->Top() < 0)
	{
		direction.y *= -1;
		body->Pos().y = body->Size().x * 0.5;
	}

	if (body->Bottom() > WIN_HEIGHT)
	{
		direction.y *= -1;
		body->Pos().y = WIN_HEIGHT - body->Size().x * 0.5;
	}
}

void Shooting_Item::CheckTimeElapsed()
{
	timeElapsed += Time::Delta();

	if (timeElapsed >= 10.f)
	{
		timeElapsed = 0.f;
		isActive = false;
	}
}
