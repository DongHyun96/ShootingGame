#include "Framework.h"
#include "Shooting_PBulletManager.h"


Shooting_PBulletManager::Shooting_PBulletManager()
{
	bulletTexture = new Texture(L"_Texture/PBullet.bmp", { 28, 28 }, { 1, 1 });

	for (UINT i = 0; i < 50; i++)
		bullets.push_back(new Shooting_PlayerBullet(bulletTexture));

}

Shooting_PBulletManager::~Shooting_PBulletManager()
{
	for (Shooting_PlayerBullet* bullet : bullets)
		delete bullet;

	bullets.clear();

	delete bulletTexture;
}

void Shooting_PBulletManager::Update()
{
	for (Shooting_PlayerBullet* bullet : bullets)
		bullet->Update();
}

void Shooting_PBulletManager::Render(HDC hdc)
{
	for (Shooting_PlayerBullet* bullet : bullets)
		bullet->Render(hdc);
}

void Shooting_PBulletManager::Fire(Point startPos, float speed, Vector2 direction)
{
	for (Shooting_PlayerBullet* bullet : bullets)
	{
		if (!bullet->IsActive())
		{
			bullet->Fire(startPos, speed, direction);
			return;
		}
	}
}

