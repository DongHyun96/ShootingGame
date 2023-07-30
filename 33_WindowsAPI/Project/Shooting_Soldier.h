#pragma once
class Shooting_Soldier : public Shooting_Enemy
{
public:
	Shooting_Soldier(Texture* texture, Texture* explodeTexture, Shooting_EBulletManager* bulletManager, Shooting_ItemManager* itemManager);

	~Shooting_Soldier();

	// Shooting_Enemy��(��) ���� ��ӵ�
	virtual void FireWeapon() override;

	virtual void HandleTextureFrame() override;

private:



};
