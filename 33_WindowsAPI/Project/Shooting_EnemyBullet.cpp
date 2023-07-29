#include "Framework.h"
#include "Shooting_EnemyBullet.h"



Shooting_EnemyBullet::Shooting_EnemyBullet(Texture* texture)
	:texture(texture)
{
	body = new Rect(WIN_CENTER, { 15, 15 });
}

Shooting_EnemyBullet::~Shooting_EnemyBullet()
{
	delete body;
}

void Shooting_EnemyBullet::Update()
{
	if (!isActive)
		return;

	Move();
	HandleBoundary();
}

void Shooting_EnemyBullet::Render(HDC hdc)
{
	if (!isActive)
		return;

	texture->Render(body);
}

void Shooting_EnemyBullet::Fire(Point startPos, float speed, Vector2 direction)
{
	isActive = true;

	body->Pos() = startPos;

	this->speed = speed;
	this->direction = direction.GetNormal();
}

void Shooting_EnemyBullet::Move()
{
	body->Pos() += direction * speed * Time::Delta();
}

void Shooting_EnemyBullet::HandleBoundary()
{
	if (body->Bottom() < 0 || body->Top() > WIN_HEIGHT || body->Right() < 0 || body->Left() > WIN_WIDTH)
		isActive = false;
}

