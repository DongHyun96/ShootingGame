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

	// �÷��̾� �Ѿ˵� vs ���ʹ̵�
	void HandleCollision(vector<Shooting_PlayerBullet*>& pBullets, vector<Shooting_Enemy*>& enemies);

	// ���ʹ� �Ѿ˵� vs �÷��̾�
	void HandleCollision(vector<Shooting_EnemyBullet*>& eBullets, Shooting_Player* player);

	// �����۵� vs �÷��̾�
	void HandleCollision(map<ItemType, vector<Shooting_Item*>>& itemMap, Shooting_Player* player);

private:

	Shooting_Player* player = nullptr;
	Shooting_EnemyManager* enemyManager = nullptr;

	Shooting_ItemManager* itemManager = nullptr;


private:
	Shooting_Background* backGround = nullptr;
};
