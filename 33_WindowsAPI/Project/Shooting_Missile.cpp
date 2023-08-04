#include "Framework.h"
#include "Shooting_Missile.h"


Shooting_Missile::Shooting_Missile(Texture* texture, Texture* explosionTexture)
	:Shooting_EnemyBullet(texture), explosionTexture(explosionTexture)
{
	body->Size() = { 50, 50 };

	for (float theta = 0.f; theta < 2.f * PI; theta += PI / 8.f)
		spriteDirections.push_back(Vector2(cosf(theta), -sinf(theta)));


}

Shooting_Missile::~Shooting_Missile()
{
	// 부모에서 body 삭제됨
}

void Shooting_Missile::Update()
{
	Shooting_EnemyBullet::Update();

	if (!isActive)
		return;

	if (hasDestroyed)
	{
		HandleExplosionFrame();
		return;
	}

	UpdateDirection();
	UpdateSprite();
}

void Shooting_Missile::Render(HDC hdc)
{
	if (!isActive)
		return;

	if (hasDestroyed)
		explosionTexture->Render(body, curFrame);
	else
		texture->Render(body, curFrame);
}

void Shooting_Missile::Move()
{
	Shooting_EnemyBullet::Move();
}

void Shooting_Missile::ApplyDamage()
{
	hp--;

	if (hp <= 0)
		HandleDestroyed();
}

void Shooting_Missile::HandleDestroyed()
{
	hp = MISSILE_HP;
	textureTime = 0.f;
	curFrame = { 0, 0 };
	//isActive = false;
	hasDestroyed = true;
}

void Shooting_Missile::UpdateDirection()
{
	direction = Shooting_GameManager::GetInst()->GetPlayerPos() - body->Pos();
	direction.Normalize();
}

void Shooting_Missile::UpdateSprite()
{

	for (UINT i = 0; i < spriteDirections.size() - 1; i++)
	{
		if (Vector2::IsBetween(direction, spriteDirections[i], spriteDirections[i + 1]))
		{
			if (Vector2::Dot(direction, spriteDirections[i]) > 0)
			{
				curFrame = { (int)(i), 0 };
				return;

			}
		}
	}

}

void Shooting_Missile::HandleExplosionFrame()
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


