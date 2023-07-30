#pragma once
class ShootingScene : public Scene
{
public:
	ShootingScene();
	~ShootingScene();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

private:
	
	void HandleCollision();

	// 플레이어 총알들 vs 에너미들
	void HandleCollision(vector<Shooting_PlayerBullet*>& pBullets, vector<Shooting_Enemy*>& enemies);

	// 에너미 총알들 vs 플레이어
	void HandleCollision(vector<Shooting_EnemyBullet*>& eBullets, Shooting_Player* player);

	// 아이템들 vs 플레이어
	void HandleCollision(map<ItemType, vector<Shooting_Item*>>& itemMap, Shooting_Player* player);

private:

	Shooting_Player* player = nullptr;
	Shooting_EnemyManager* enemyManager = nullptr;

	Shooting_ItemManager* itemManager = nullptr;


private:
	Shooting_Background* backGround = nullptr;
};
