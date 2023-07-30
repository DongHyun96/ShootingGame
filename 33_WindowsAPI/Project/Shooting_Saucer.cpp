#include "Framework.h"
#include "Shooting_Saucer.h"



Shooting_Saucer::Shooting_Saucer(Texture* texture, Texture* explodeTexture, Shooting_EBulletManager* bulletManager, Shooting_ItemManager* itemManager)
	:Shooting_Enemy(texture, explodeTexture, bulletManager, itemManager)
{
	body = new Rect(WIN_CENTER, { 53 * 1.2f, 32 * 1.2f });
	explodeBody = new Rect(WIN_CENTER, { 50, 100 });

	curFrame = { 0, 0 };
}

Shooting_Saucer::~Shooting_Saucer()
{
}

void Shooting_Saucer::FireWeapon()
{
	fireTime += Time::Delta();

	if (fireTime >= 1.5f)
	{
		fireTime -= 1.5f;

		if (rand() % 2 == 0)
			bulletManager->FireDefaultRound({ body->Pos().x, body->Bottom() });
		else
		{
			bulletManager->FireDefaultRound({ body->Pos().x, body->Bottom() }, 300.f, { 0.5f, 1 });
			bulletManager->FireDefaultRound({ body->Pos().x, body->Bottom() }, 300.f, { 0, 1 });
			bulletManager->FireDefaultRound({ body->Pos().x, body->Bottom() }, 300.f, { -0.5f, 1 });
		}
	}
}

void Shooting_Saucer::HandleTextureFrame()
{
	textureTime += Time::Delta();

	if (textureTime >= 0.02f)
	{
		textureTime -= 0.02f;

		++curFrame.x %= 10;
	}
	
}
