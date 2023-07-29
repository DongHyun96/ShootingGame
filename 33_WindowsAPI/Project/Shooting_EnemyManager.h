#pragma once
class Shooting_EnemyManager
{
public:
	Shooting_EnemyManager();
	~Shooting_EnemyManager();

	void Update();
	void Render(HDC hdc);

	vector<Shooting_Enemy*>& GetEnemies() { return enemies; }
	vector<Shooting_EnemyBullet*>& GetBullets() { return bulletManager->GetBullets(); }

private:
	void SpawnEnemy();

	UINT GetActiveEnemiesCnt();

private:
	Shooting_EBulletManager* bulletManager = nullptr;

	vector<Shooting_Enemy*> enemies = {};

	Texture* enemyTexture = nullptr;
};
