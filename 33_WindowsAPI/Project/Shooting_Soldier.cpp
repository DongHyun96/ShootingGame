#include "Framework.h"
#include "Shooting_Soldier.h"



Shooting_Soldier::Shooting_Soldier(Texture* texture, Texture* explodeTexture, Shooting_EBulletManager* bulletManager, Shooting_ItemManager* itemManager)
	:Shooting_Enemy(texture, explodeTexture, bulletManager, itemManager)
{
	body = new Rect(WIN_CENTER, { 45 * 1.5f, 44 * 1.5f }); // Todo - body 크기는 나중에 정할 것
	explodeBody = new Rect(WIN_CENTER, { 50, 100 });

	curFrame = { 0, 0 };

}

Shooting_Soldier::~Shooting_Soldier()
{
}

void Shooting_Soldier::FireWeapon()
{
	fireTime += Time::Delta();

	if (fireTime >= 3.f)
	{
		fireTime -= 3.f;

		float randomSpeed = GetRandom(150.f, 300.f);

		bulletManager->FireMissile({ body->Pos().x, body->Bottom() }, randomSpeed);
	}
}

void Shooting_Soldier::HandleTextureFrame()
{
	textureTime += Time::Delta();

	if (textureTime >= 0.05f)
	{
		textureTime -= 0.05f;

		++curFrame.x %= 16;
	}
}
