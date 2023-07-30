#include "Framework.h"
#include "Shooting_EBulletManager.h"



Shooting_EBulletManager::Shooting_EBulletManager()
{
	bulletTexture = new Texture(L"_Texture/ball.bmp", { 16, 16 }, { 1, 1 });

	missileTexture = new Texture(L"_Texture/missilePF.bmp", { 576, 44 }, { 16, 1 });

	for (UINT i = 0; i < 200; i++)
		bullets.push_back(new Shooting_EnemyBullet(bulletTexture));

	for (UINT i = 0; i < 100; i++)
		missiles.push_back(new Shooting_Missile(missileTexture));


}

Shooting_EBulletManager::~Shooting_EBulletManager()
{
	for (Shooting_EnemyBullet* bullet : bullets)
		delete bullet;

	for (Shooting_Missile* missile : missiles)
		delete missile;

	bullets.clear();
	missiles.clear();

	delete bulletTexture;
	delete missileTexture;
}

void Shooting_EBulletManager::Update()
{
	for (Shooting_EnemyBullet* bullet : bullets)
		bullet->Update();

	for (Shooting_Missile* missile : missiles)
		missile->Update();
}

void Shooting_EBulletManager::Render(HDC hdc)
{
	for (Shooting_EnemyBullet* bullet : bullets)
		bullet->Render(hdc);

	for (Shooting_Missile* missile : missiles)
		missile->Render(hdc);
}

void Shooting_EBulletManager::FireDefaultRound(Point startPos, float speed, Vector2 direction)
{
	for (Shooting_EnemyBullet* bullet : bullets)
	{
		if (!bullet->IsActive())
		{
			bullet->Fire(startPos, speed, direction);
			return;
		}
	}
}

void Shooting_EBulletManager::FireMissile(Point startPos, float speed, Vector2 direction)
{
	for (Shooting_Missile* missile : missiles)
	{
		if (!missile->IsActive())
		{
			missile->Fire(startPos, speed, direction);
			return;
		}
	}
}

