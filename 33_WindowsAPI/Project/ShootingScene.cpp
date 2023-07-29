#include "Framework.h"
#include "ShootingScene.h"


ShootingScene::ShootingScene()
{
	player = new Shooting_Player;
	enemyManager = new Shooting_EnemyManager;
	backGround = new Shooting_Background;

	hFont = CreateFont(
		30,				  // Desired font size
		0,                // Font width
		0,                // Font escapement
		0,                // Orientation
		FW_NORMAL,        // Font weight
		FALSE,            // Italic
		FALSE,            // Underline
		FALSE,            // Strikeout
		DEFAULT_CHARSET,  // Character set
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE,
		TEXT("Impact")     // Font name
	);
}

ShootingScene::~ShootingScene()
{
	delete player;
	delete enemyManager;
	delete backGround;
	DeleteObject(hFont);
}


void ShootingScene::Update()
{
	backGround->Update();
	player->Update();
	enemyManager->Update();

	HandleCollision();
}

void ShootingScene::Render(HDC hdc)
{
	HFONT oldFont = (HFONT)SelectObject(hdc, hFont);
	UINT prevAlign = SetTextAlign(hdc, TA_CENTER);
	int prevMode = SetBkMode(hdc, TRANSPARENT);



	backGround->Render(hdc);

	player->Render(hdc);
	enemyManager->Render(hdc);


	SelectObject(hdc, oldFont);
	SetTextAlign(hdc, prevAlign);
	SetBkMode(hdc, prevMode);

	DeleteObject(oldFont);
}

void ShootingScene::HandleCollision()
{
	HandleCollision(player->GetBulletManager()->GetBullets(), enemyManager->GetEnemies());
	HandleCollision(enemyManager->GetBullets(), player);
}

void ShootingScene::HandleCollision(vector<Shooting_PlayerBullet*>& pBullets, vector<Shooting_Enemy*> enemies)
{
	for (Shooting_PlayerBullet* bullet : pBullets)
	{
		if (!bullet->IsActive())
			continue;

		for (Shooting_Enemy* enemy : enemies)
		{
			if (!enemy->IsActive())
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
