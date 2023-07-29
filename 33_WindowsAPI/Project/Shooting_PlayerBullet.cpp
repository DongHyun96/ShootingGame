#include "Framework.h"
#include "Shooting_PlayerBullet.h"



Shooting_PlayerBullet::Shooting_PlayerBullet(Texture* texture)
	:texture(texture)
{
	body = new Rect(WIN_CENTER, { 30, 30 });
}

Shooting_PlayerBullet::~Shooting_PlayerBullet()
{
	delete body;
}

void Shooting_PlayerBullet::Update()
{
	if (!isActive)
		return;

	Move();
	HandleBoundary();
}

void Shooting_PlayerBullet::Render(HDC hdc)
{
	if (!isActive)
		return;

	texture->Render(body);
}

void Shooting_PlayerBullet::Fire(Point startPos, float speed, Vector2 direction)
{
	isActive = true;

	body->Pos() = startPos;
	
	this->speed = speed;
	this->direction = direction.GetNormal();

}

void Shooting_PlayerBullet::Move()
{
	body->Pos() += direction * speed * Time::Delta();
}

void Shooting_PlayerBullet::HandleBoundary()
{
	if (body->Bottom() < 0 || body->Top() > WIN_HEIGHT || body->Right() < 0 || body->Left() > WIN_WIDTH)
		isActive = false;
}

