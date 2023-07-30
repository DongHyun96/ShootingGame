#include "Framework.h"
#include "Shooting_Enemy.h"



Shooting_Enemy::Shooting_Enemy()
{
}

Shooting_Enemy::Shooting_Enemy(Texture* texture, Texture* explodeTexture, Shooting_EBulletManager* bulletManager, Shooting_ItemManager* itemManager)
	: texture(texture), explodeTexture(explodeTexture), bulletManager(bulletManager), itemManager(itemManager)
{
}


Shooting_Enemy::~Shooting_Enemy()
{
	delete body;
	delete explodeBody;
}

void Shooting_Enemy::Update()
{
	if (!isActive)
		return;

	if (hasDestroyed)
	{
		HandleExplosionFrame();
		return;
	}

	Move();
	HandleTextureFrame();
	FireWeapon();
}

void Shooting_Enemy::Render(HDC hdc)
{
	if (!isActive)
		return;

	if (hasDestroyed)
	{
		explodeTexture->Render(explodeBody, curFrame);
		return;
	}

	texture->Render(body, curFrame);
}

void Shooting_Enemy::Spawn(Point startPos, Point endPos)
{
	isActive = true;
	hasDestroyed = false;

	body->Pos() = startPos;
	direction = (endPos - startPos).GetNormal();
	this->endPos = endPos;
	destination = endPos;

	curFrame = { 0, 0 };

	hp = GetRandom(1, 10);
	speed = GetRandom(100.f, 300.f);
}


void Shooting_Enemy::ApplyDamage()
{
	if (!isActive)
		return;

	hp--;

	if (hp <= 0) // Dead
	{
		curFrame = { 0, 0 };
		hasDestroyed = true;

		explodeBody->Pos() = body->Pos();

		if (rand() % 5 == 0) // 20%의 확률로 아이템 스폰
			itemManager->SpawnRandomItem(body->Pos());

		Shooting_GameManager::GetInst()->AddScore(50);
	}
}

void Shooting_Enemy::Move()
{
	Vector2 temp = destination - body->Pos();
	
	if (Vector2::Dot(temp, direction) < 0) // destination reached
		return;

	body->Pos() += direction * speed * Time::Delta();
}


void Shooting_Enemy::HandleExplosionFrame()
{
	textureTime += Time::Delta();

	if (textureTime >= 0.07f)
	{
		textureTime -= 0.07f;

		curFrame.x++;

		if (curFrame.x == 8)
		{
			isActive = false;
			hasDestroyed = false;
		}
	}
}
