#include "Framework.h"
#include "ShootingScene.h"


ShootingScene::ShootingScene()
{
	player = new Shooting_Player;

	itemManager = new Shooting_ItemManager;

	enemyManager = new Shooting_EnemyManager(itemManager);

	backGround = new Shooting_Background;

}

ShootingScene::~ShootingScene()
{
	delete player;
	delete enemyManager;
	delete itemManager;
	delete backGround;
}


void ShootingScene::Update()
{
	backGround->Update();
	Shooting_GameManager::GetInst()->Update();

	if (!player->IsActive())
		return;

	player->Update();
	enemyManager->Update();
	itemManager->Update();

	HandleCollision();
}

void ShootingScene::Render(HDC hdc)
{
	backGround->Render(hdc);

	Shooting_GameManager::GetInst()->Render(hdc);

	if (!player->IsActive())
		return;

	player->Render(hdc);
	enemyManager->Render(hdc);
	itemManager->Render(hdc);

}


void ShootingScene::HandleCollision()
{
	HandleCollision(player->GetBulletManager()->GetBullets(), enemyManager->GetEnemies());
	HandleCollision(enemyManager->GetBullets(), player);

	HandleCollision(itemManager->GetItemMap(), player);
}

void ShootingScene::HandleCollision(vector<Shooting_PlayerBullet*>& pBullets, vector<Shooting_Enemy*>& enemies)
{
	for (Shooting_PlayerBullet* bullet : pBullets)
	{
		if (!bullet->IsActive())
			continue;

		for (Shooting_Enemy* enemy : enemies)
		{
			if (!enemy->IsActive())
				continue;

			if (enemy->IsActive() && enemy->HasDestroyed())
				continue;

			if (Collision::Collision(bullet->GetBody(), enemy->GetBody()))
			{
				bullet->SetActive(false);

				enemy->ApplyDamage();
			}
		}
	}
}

void ShootingScene::HandleCollision(vector<Shooting_EnemyBullet*>& eBullets, Shooting_Player* player)
{
	for (Shooting_EnemyBullet* bullet : eBullets)
	{
		if (!bullet->IsActive())
			continue;

		if (Collision::Collision(player->GetBody(), bullet->GetBody()))
		{
			bullet->SetActive(false);
			player->ApplyDamage();
		}
	}
}

void ShootingScene::HandleCollision(map<ItemType, vector<Shooting_Item*>>& itemMap, Shooting_Player* player)
{
	for (auto& pair : itemMap)
	{
		for (Shooting_Item* item : pair.second)
		{
			if (!item->IsActive())
				continue;

			if (Collision::Collision(player->GetBody(), item->GetBody()))
			{
				item->SetActive(false);
				player->SetWeaponState((Weapon_State)(pair.first + 1));
			}
		}
	}
}

