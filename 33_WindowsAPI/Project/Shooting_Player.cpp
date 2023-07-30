#include "Framework.h"
#include "Shooting_Player.h"


Shooting_Player::Shooting_Player()
{
	texture = new Texture(L"_Texture/Player.bmp", { 448, 40 }, { 14, 1 });

	body = new Rect({WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.9}, { 64, 80 });

	curFrame = { 6, 0 };

	bulletManager = new Shooting_PBulletManager;

	explosionTexture = new Texture(L"_Texture/Explode.bmp", { 538, 168 }, { 8, 1 }, RGB(0, 248, 0));
}

Shooting_Player::~Shooting_Player()
{
	delete texture;
	delete body;
	delete bulletManager;

}

void Shooting_Player::Update()
{
	if (!isActive)
		return;

	if (hasDestroyed)
	{
		HandleExplosionFrame();
		return;
	}

	Move();
	FireWeapon();

	HandleTextureFrame();

	HandleWeaponTime();

	bulletManager->Update();
}

void Shooting_Player::Render(HDC hdc)
{
	if (!isActive)
		return;

	if (hasDestroyed)
	{
		explosionTexture->Render(body, curFrame);
		return;
	}

	texture->Render(body, curFrame);
	bulletManager->Render(hdc);

}

void Shooting_Player::ApplyDamage()
{
	if (hasDestroyed)
		return;

	Shooting_GameManager::GetInst()->UpdatePlayerHpBar(--hp);
	
	if (hp <= 0)
	{
		// player's dead
		//isActive = false;

		body->Size().x = 100.f;
		body->Size().y = 200.f;

		curFrame = { 0, 0 };
		hasDestroyed = true;
	}
}

void Shooting_Player::SetWeaponState(Weapon_State state)
{
	this->weaponState = state;

	weaponHoldTime = 0.f;

	Shooting_GameManager::GetInst()->UpdatePlayerWeaponState(state);
}

void Shooting_Player::Move()
{
	direction = {0, 0};

	if (GetAsyncKeyState(VK_LEFT))
		direction.x -= 1;

	if (GetAsyncKeyState(VK_RIGHT))
		direction.x += 1;

	if (GetAsyncKeyState(VK_UP))
		direction.y -= 1;

	if (GetAsyncKeyState(VK_DOWN))
		direction.y += 1;

	if (direction.Length())
		direction.Normalize();

	body->Pos() += direction * speed * Time::Delta();

	Shooting_GameManager::GetInst()->SetPlayerPos(body->Pos());

	HandleBoundary();
}

void Shooting_Player::FireWeapon()
{
	static bool isPressed = false;
	static float pressedTime = 0.f;

	static Spacebar_State keyState;

	keyState = KEY_IDLE;

	if (GetAsyncKeyState(VK_SPACE))
	{
		if (!isPressed)
		{
			keyState = KEY_DOWN;
			isPressed = true;
		}
		else
		{
			keyState = KEY_PRESSED;
			pressedTime += Time::Delta();
		}
	}
	else
	{
		keyState = KEY_UP;

		isPressed = false;
		pressedTime = 0.f;
	}

	if (keyState == KEY_DOWN || keyState == KEY_PRESSED)
	{
		switch (weaponState)
		{
		case PISTOL:
			if (keyState == KEY_DOWN)
				bulletManager->Fire({ body->Pos().x, body->Top() });

			if (pressedTime >= 0.2f)
			{
				pressedTime -= 0.2f;
				bulletManager->Fire({ body->Pos().x, body->Top() });
			}
			break;
		case MACHINE_GUN:
			if (pressedTime >= 0.04f)
			{
				pressedTime -= 0.04f;

				bulletManager->Fire({ body->Pos().x, body->Top() });
			}
			break;
		case SHOT_GUN:
			if (pressedTime >= 0.06f)
			{
				pressedTime -= 0.06f;

				bulletManager->Fire({ body->Pos().x, body->Top() }, 1000.f, { 0.5f, -1 });
				bulletManager->Fire({ body->Pos().x, body->Top() }, 1000.f, { 0, -1 });
				bulletManager->Fire({ body->Pos().x, body->Top() }, 1000.f, { -0.5f, -1 });
			}
			break;
		default:
			break;
		}
	}


}

void Shooting_Player::HandleTextureFrame()
{
	static float textureTime = 0.f;

	textureTime += Time::Delta();

	if (textureTime >= 0.03f)
	{
		textureTime -= 0.03f;

		if (direction.x > 0.f)
			curFrame.x = (curFrame.x == 13) ? curFrame.x : curFrame.x + 1;

		else if (direction.x < 0.f)
			curFrame.x = (curFrame.x == 0) ? curFrame.x : curFrame.x - 1;

		else
		{
			curFrame.x = (curFrame.x == 6) ? curFrame.x :
				(curFrame.x < 6) ? curFrame.x + 1 : curFrame.x - 1;
		}

	}
}

void Shooting_Player::HandleExplosionFrame()
{
	static float textureTime = 0.f;

	textureTime += Time::Delta();

	if (textureTime >= 0.1f)
	{
		textureTime -= 0.1f;

		curFrame.x++;

		if (curFrame.x == 8)
		{
			isActive = false;
			Shooting_GameManager::GetInst()->SetGameOver(true);
		}
	}
}

void Shooting_Player::HandleBoundary()
{
	if (body->Top() < 0)
		body->Pos().y = body->Size().y * 0.5f;
	if (body->Bottom() > WIN_HEIGHT)
		body->Pos().y = WIN_HEIGHT - body->Size().y * 0.5f;
	if (body->Left() < 0)
		body->Pos().x = body->Size().x * 0.5f;
	if (body->Right() > WIN_WIDTH)
		body->Pos().x = WIN_WIDTH - body->Size().x * 0.5f;
}

void Shooting_Player::HandleWeaponTime()
{
	if (weaponState == PISTOL)
		return;

	weaponHoldTime += Time::Delta();

	if (weaponHoldTime >= WEAPON_HOLD_TIME_MAX)
	{
		weaponHoldTime = 0.f;

		weaponState = PISTOL;

		Shooting_GameManager::GetInst()->UpdatePlayerWeaponState(weaponState);
	}

}
