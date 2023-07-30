#pragma once

#define PLAYER_HP_MAX 30
#define WEAPON_HOLD_TIME_MAX 15.f

enum Weapon_State
{
	PISTOL,
	MACHINE_GUN,
	SHOT_GUN
};

enum Spacebar_State
{
	KEY_DOWN,
	KEY_PRESSED,
	KEY_UP,
	KEY_IDLE
};

class Shooting_Player
{
public:
	Shooting_Player();
	~Shooting_Player();

	void Update();
	void Render(HDC hdc);

	Rect* GetBody() { return body; }
	Shooting_PBulletManager* GetBulletManager() { return bulletManager; }

	void ApplyDamage();

	void SetWeaponState(Weapon_State state);

	bool IsActive() const { return isActive; }

private:
	void Move();
	void FireWeapon();

	void HandleTextureFrame();
	void HandleExplosionFrame();
	void HandleBoundary();

	void HandleWeaponTime();

private:
	Rect* body = nullptr;
	Texture* texture = nullptr;

	Texture* explosionTexture = nullptr;

	POINT curFrame = {};

	//float textureTime = 0.f;
	float speed = 600.f;

	Vector2 direction = {};

	Weapon_State weaponState = PISTOL;
	float weaponHoldTime = 0.f;

	Shooting_PBulletManager* bulletManager = nullptr;

	UINT hp = PLAYER_HP_MAX;

	bool isActive = true;
	bool hasDestroyed = false;

};
