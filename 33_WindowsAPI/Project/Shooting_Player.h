#pragma once

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

private:
	void Move();
	void FireWeapon();

	void HandleTextureFrame();
	void HandleBoundary();

	void RenderHpBar(HDC hdc);

private:
	Rect* body = nullptr;
	Texture* texture = nullptr;

	POINT curFrame = {};

	//float textureTime = 0.f;
	float speed = 600.f;

	Vector2 direction = {};

	Weapon_State weaponState = MACHINE_GUN;

	Shooting_PBulletManager* bulletManager = nullptr;

	UINT hp = 30;

	bool isActive = true;

private:
	Rect* frontBar = nullptr;
	Rect* backBar = nullptr;

	HPEN backPen = CreatePen(PS_SOLID, 5, RGB(253, 141, 20));
	HBRUSH backBrush = CreateSolidBrush(RGB(255, 250, 215));

	HPEN frontPen = CreatePen(PS_SOLID, 1, RGB(197, 22, 5));
	HBRUSH frontBrush = CreateSolidBrush(RGB(197, 22, 5));

};
