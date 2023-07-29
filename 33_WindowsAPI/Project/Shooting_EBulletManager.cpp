#include "Framework.h"
#include "Shooting_EBulletManager.h"



Shooting_EBulletManager::Shooting_EBulletManager()
{
	bulletTexture = new Texture(L"_Texture/ball.bmp", { 16, 16 }, { 1, 1 });

	for (UINT i = 0; i < 300; i++)
		bullets.push_back(new Shooting_EnemyBullet(bulletTexture));
}

Shooting_EBulletManager::~Shooting_EBulletManager()
{
	for (Shooting_EnemyBullet* bullet : bullets)
		delete bullet;

	bullets.clear();

	delete bulletTexture;
}

void Shooting_EBulletManager::Update()
{
	for (Shooting_EnemyBullet* bullet : bullets)
		bullet->Update();
}

void Shooting_EBulletManager::Render(HDC hdc)
{
	for (Shooting_EnemyBullet* bullet : bullets)
		bullet->Render(hdc);
}

void Shooting_EBulletManager::Fire(Point startPos, float speed, Vector2 direction)
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

