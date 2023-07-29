#include "Framework.h"
#include "Shooting_Enemy.h"



Shooting_Enemy::Shooting_Enemy(Texture* texture, Shooting_EBulletManager* bulletManager)
	: texture(texture), bulletManager(bulletManager)
{
	texture = new Texture(L"_Texture/ufo.bmp", { 530, 32 }, { 10, 1 });

	body = new Rect(WIN_CENTER, { 53 * 1.2f, 32 * 1.2f });

	curFrame = { 0, 0 };
}


Shooting_Enemy::~Shooting_Enemy()
{
	delete body;
}

void Shooting_Enemy::Update()
{
	if (!isActive)
		return;

	Move();
	HandleTextureFrame();
	FireWeapon();
}

void Shooting_Enemy::Render(HDC hdc)
{
	if (!isActive)
		return;

	texture->Render(body, curFrame);
}

void Shooting_Enemy::Spawn(Point startPos, Point endPos)
{
	isActive = true;
	body->Pos() = startPos;
	direction = (endPos - startPos).GetNormal();
	destination = endPos;

	hp = GetRandom(1, 20);
	speed = GetRandom(100.f, 300.f);
}


void Shooting_Enemy::ApplyDamage()
{
	if (!isActive)
		return;

	hp--;

	if (hp <= 0)
		isActive = false;
}

void Shooting_Enemy::Move()
{
	Vector2 temp = destination - body->Pos();
	
	if (Vector2::Dot(temp, direction) < 0) // destination reached
		return;

	body->Pos() += direction * speed * Time::Delta();
}


void Shooting_Enemy::FireWeapon()
{
	static float fireTime = 0.f;

	fireTime += Time::Delta();

	if (fireTime >= 1.5f)
	{
		fireTime -= 1.5f;

		if (rand() % 2 == 0)
			bulletManager->Fire({ body->Pos().x, body->Bottom() });
		else
		{
			bulletManager->Fire({ body->Pos().x, body->Bottom() }, 300.f, { 0.5f, 1 });
			bulletManager->Fire({ body->Pos().x, body->Bottom() }, 300.f, { 0, 1 });
			bulletManager->Fire({ body->Pos().x, body->Bottom() }, 300.f, { -0.5f, 1 });
		}
	}

}

void Shooting_Enemy::HandleTextureFrame()
{
	static float textureTime = 0.f;

	textureTime += Time::Delta();

	if (textureTime >= 0.02f)
	{
		textureTime -= 0.02f;

		++curFrame.x %= 10;
	}
}
