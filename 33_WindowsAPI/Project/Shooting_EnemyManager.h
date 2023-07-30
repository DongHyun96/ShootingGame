#pragma once
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

	UINT GetActiveEnemiesCnt();

	bool CheckSpawnEndPosValid(Point endPos);

private:
	Shooting_EBulletManager* bulletManager = nullptr;

	vector<Shooting_Enemy*> enemies = {};

	Texture* enemyTexture = nullptr;
	Texture* enemyTexture2 = nullptr;

	Texture* explosionTexture = nullptr;
};
