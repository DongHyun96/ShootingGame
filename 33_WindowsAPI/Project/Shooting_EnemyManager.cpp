#include "Framework.h"
#include "Shooting_EnemyManager.h"


Shooting_EnemyManager::Shooting_EnemyManager(Shooting_ItemManager* itemManager)
{
	enemyTexture = new Texture(L"_Texture/ufo.bmp", { 530, 32 }, { 10, 1 });
	enemyTexture2 = new Texture(L"_Texture/enemy1.bmp", { 720, 44 }, { 16, 1 }, RGB(153, 217, 234));

	explosionTexture = new Texture(L"_Texture/Explode.bmp", { 538, 168 }, { 8, 1 }, RGB(0, 248, 0));

	bulletManager = new Shooting_EBulletManager;

	for (UINT i = 0; i < 60; i++)
	{
		Shooting_Enemy* enemy = nullptr;

		if (i <= 30)
		{
			enemy = new Shooting_Soldier(enemyTexture2, explosionTexture, bulletManager, itemManager);
			soldiers.push_back(enemy);
		}
		else 
		{
			enemy = new Shooting_Saucer(enemyTexture, explosionTexture, bulletManager, itemManager);
			saucers.push_back(enemy);
		}

		enemies.push_back(enemy);
	}
}

Shooting_EnemyManager::~Shooting_EnemyManager()
{
	delete bulletManager;

	for (Shooting_Enemy* enemy : enemies)
		delete enemy;

	enemies.clear();
	saucers.clear();
	soldiers.clear();

	delete enemyTexture;
	delete enemyTexture2;
	delete explosionTexture;
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
	static float spawnFactor = 200.f;

	static float spawnTime = 0.f;

	spawnTime += Time::Delta();

	if (GetActiveEnemiesCnt() >= 15) // 적이 15마리 이상이면 스폰 시키지 않음
	{
		spawnTime = 0.f;
		return;
	}

	spawnFactor = (spawnFactor <= 30.f) ? spawnFactor : spawnFactor - Time::Delta() * 1.5f;

	if (spawnTime >= spawnFactor / 100.f)
	{
		spawnTime -= spawnFactor / 100.f;
		
		// 30%의 확률로 soldier 스폰
		if (rand() % 10 < 3)
			SpawnRoutine(SOLDIER);
		else // spawn saucer
			SpawnRoutine(SAUCER);
	}
	
}

void Shooting_EnemyManager::SpawnRoutine(EnemyType type)
{
	switch (type)
	{
	case SAUCER:
	{
		for (Shooting_Enemy* enemy : saucers)
		{
			if (!enemy->IsActive())
			{
				Point endPos;

				do
				{
					endPos =
					{
						GetRandom(enemy->GetBody()->Size().x * 0.5f, WIN_WIDTH - enemy->GetBody()->Size().x * 0.5f),
						GetRandom(enemy->GetBody()->Size().y * 0.5f, WIN_HEIGHT * 0.4f)
					};
				} while (!CheckSpawnEndPosValid(endPos));


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
		break;
	case SOLDIER:
	{
		for (Shooting_Enemy* enemy : soldiers)
		{
			if (!enemy->IsActive())
			{
				Point endPos;

				do
				{
					endPos =
					{
						GetRandom(enemy->GetBody()->Size().x * 0.5f, WIN_WIDTH - enemy->GetBody()->Size().x * 0.5f),
						GetRandom(enemy->GetBody()->Size().y * 0.5f, WIN_HEIGHT * 0.4f)
					};
				} while (!CheckSpawnEndPosValid(endPos));


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
		break;
	default:
		break;
	}
}

UINT Shooting_EnemyManager::GetActiveEnemiesCnt()
{
	return count_if(enemies.begin(), enemies.end(), [this](Shooting_Enemy* enemy)
		{
			return enemy->IsActive();
		});
}

bool Shooting_EnemyManager::CheckSpawnEndPosValid(Point endPos)
{
	Rect tempBody(endPos, enemies[0]->GetBody()->Size());
	Rect targetBody;

	for (Shooting_Enemy* enemy : enemies)
	{
		if (!enemy->IsActive())
			continue;

		targetBody = Rect(enemy->GetEndPos(), enemy->GetBody()->Size());

		if (Collision::Collision(&targetBody, &tempBody))
			return false;
	}

	return true;
}

