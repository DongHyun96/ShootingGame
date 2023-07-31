#pragma once

enum EnemyType
{
	SAUCER,
	SOLDIER
};

class Shooting_EnemyManager
{
public:
	Shooting_EnemyManager(Shooting_ItemManager* itemManager);
	~Shooting_EnemyManager();

	void Update();
	void Render(HDC hdc);

	vector<Shooting_Enemy*>& GetEnemies() { return enemies; }
	vector<Shooting_EnemyBullet*>& GetBullets() { return bulletManager->GetBullets(); }
	vector<Shooting_Missile*>& GetMissiles() { return bulletManager->GetMissiles(); }

private:
	void SpawnEnemy();
	void SpawnRoutine(EnemyType type);

	UINT GetActiveEnemiesCnt();

	bool CheckSpawnEndPosValid(Point endPos);

private:
	Shooting_EBulletManager* bulletManager = nullptr;

	vector<Shooting_Enemy*> enemies = {};

	vector<Shooting_Enemy*> saucers = {};
	vector<Shooting_Enemy*> soldiers = {};

	Texture* enemyTexture = nullptr;
	Texture* enemyTexture2 = nullptr;

	Texture* explosionTexture = nullptr;
};
