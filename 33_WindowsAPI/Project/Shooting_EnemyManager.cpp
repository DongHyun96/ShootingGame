#include "Framework.h"
#include "Shooting_EnemyManager.h"


Shooting_EnemyManager::Shooting_EnemyManager()
{
	enemyTexture = new Texture(L"_Texture/ufo.bmp", { 530, 32 }, { 10, 1 });

	bulletManager = new Shooting_EBulletManager;

	for (UINT i = 0; i < 30; i++)
		enemies.push_back(new Shooting_Enemy(enemyTexture, bulletManager));
}

Shooting_EnemyManager::~Shooting_EnemyManager()
{
	delete bulletManager;

	for (Shooting_Enemy* enemy : enemies)
		delete enemy;

	enemies.clear();

	delete enemyTexture;
}

void Shooting_EnemyManager::Update()
{
	bulletManager->Update();

	for (Shooting_Enemy* enemy : enemies)
		enemy->Update();

	SpawnEnemy();
}

void Shooting_EnemyManager::Render(HDC hdc)
{
	bulletManager->Render(hdc);

	for (Shooting_Enemy* enemy : enemies)
		enemy->Render(hdc);
}

void Shooting_EnemyManager::SpawnEnemy()
{
	static float spawnTime = 0.f;

	spawnTime += Time::Delta();

	if (GetActiveEnemiesCnt() >= 15) // 적이 15마리 이상이면 스폰 시키지 않음
	{
		spawnTime = 0.f;
		return;
	}

	if (spawnTime >= 2.f)
	{
		spawnTime -= 2.f;

		for (Shooting_Enemy* enemy : enemies)
		{
			if (!enemy->IsActive())
			{
				Point endPos(
					GetRandom(enemy->GetBody()->Size().x * 0.5f, WIN_WIDTH - enemy->GetBody()->Size().x * 0.5f),
					GetRandom(enemy->GetBody()->Size().y * 0.5f, WIN_HEIGHT * 0.4f)
				);

				Point startPos;

				switch (rand() % 3)
				{
				case 0: // 왼쪽 구석에서 스폰 시작
					startPos =
					{
						-enemy->GetBody()->Size().x * 0.5f,
						GetRandom(0.f, WIN_HEIGHT * 0.4f)
					};
					break;
				case 1: // 상단에서 스폰 시작
					startPos =
					{
						GetRandom(0.f, WIN_WIDTH),
						-enemy->GetBody()->Size().y * 0.5f
					};
					break;
				case 2: // 오른쪽 구석에서 스폰 시작
					startPos =
					{
						WIN_WIDTH + enemy->GetBody()->Size().x * 0.5f,
						GetRandom(0.f, WIN_HEIGHT * 0.4f)
					};
					break;
				default:
					break;
				}

				enemy->Spawn(startPos, endPos);

				break;
			}
		}
	}


	
}

UINT Shooting_EnemyManager::GetActiveEnemiesCnt()
{
	return count_if(enemies.begin(), enemies.end(), [this](Shooting_Enemy* enemy)
		{
			return enemy->IsActive();
		});
}

