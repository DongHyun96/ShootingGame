#pragma once
class Shooting_GameManager
{
private:
	Shooting_GameManager();
	~Shooting_GameManager();

public:
	static Shooting_GameManager* GetInst()
	{
		static Shooting_GameManager singleton;
		return &singleton;
	}
	
	void Update();
	void Render(HDC hdc);

	void UpdatePlayerHpBar(const UINT& hp);
	void AddScore(const UINT& amount) { score += amount; }
	void UpdatePlayerWeaponState(const Weapon_State& weaponState);

	void SetGameOver(const bool& isGameOver) { this->isGameOver = isGameOver; }


private:
	void RenderHpBar(HDC hdc);
	void RenderScore(HDC hdc);
	void RenderWeapon(HDC hdc);
	void RenderGameOver(HDC hdc);

private:
	HFONT hFont;
	Texture* boardTexture = nullptr;

private: // player HP bar field

	Rect* frontBar = nullptr;
	Rect* backBar = nullptr;

	HPEN backPen = CreatePen(PS_SOLID, 5, RGB(253, 141, 20));
	HBRUSH backBrush = CreateSolidBrush(RGB(255, 250, 215));

	HPEN frontPen = CreatePen(PS_SOLID, 1, RGB(197, 22, 5));
	HBRUSH frontBrush = CreateSolidBrush(RGB(197, 22, 5));

private: // Scoring field
	UINT score = 0;
	Rect* scoreBoardBody = nullptr;

private: // player weapons field
	Texture* machineGunTexture	= nullptr;
	Texture* shotGunTexture		= nullptr;

	Weapon_State weaponState	= PISTOL;
	Rect*		 weaponBody		= nullptr;
	UINT		 weaponTimeLeft	= WEAPON_HOLD_TIME_MAX;
	float		 weaponTimer	= 0.f;

private: // GameOver field
	bool isGameOver = false;


};
