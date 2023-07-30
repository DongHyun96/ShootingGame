#pragma once
class Shooting_Soldier : public Shooting_Enemy
{
public:
	Shooting_Soldier(Texture* texture, Texture* explodeTexture, Shooting_EBulletManager* bulletManager, Shooting_ItemManager* itemManager);

	~Shooting_Soldier();

	// Shooting_Enemy을(를) 통해 상속됨
	virtual void FireWeapon() override;

	virtual void HandleTextureFrame() override;

private:



};
