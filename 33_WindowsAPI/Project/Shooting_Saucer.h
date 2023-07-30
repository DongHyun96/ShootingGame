#pragma once
class Shooting_Saucer : public Shooting_Enemy
{
public:
	Shooting_Saucer(Texture* texture, Texture* explodeTexture, Shooting_EBulletManager* bulletManager, Shooting_ItemManager* itemManager);
	~Shooting_Saucer();

private:

	virtual void FireWeapon() override;
	virtual void HandleTextureFrame() override;

};
