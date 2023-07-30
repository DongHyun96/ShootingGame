#include "Framework.h"
#include "Shooting_GameManager.h"


Shooting_GameManager::Shooting_GameManager()
{
	backBar = new Rect(Point(120, WIN_HEIGHT * 0.97f), Point(200, 20));
	frontBar = new Rect(Point(120, WIN_HEIGHT * 0.97f), Point(195, 15));

	hFont = CreateFont(
		30,				  // Desired font size
		0,                // Font width
		0,                // Font escapement
		0,                // Orientation
		FW_NORMAL,        // Font weight
		FALSE,            // Italic
		FALSE,            // Underline
		FALSE,            // Strikeout
		DEFAULT_CHARSET,  // Character set
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE,
		TEXT("Impact")     // Font name
	);

	boardTexture		= new Texture(L"_Texture/Card.bmp", { 1097, 677 }, { 1, 1 });
	scoreBoardBody		= new Rect(WIN_WIDTH * 0.83f, WIN_HEIGHT * 0.92f, WIN_WIDTH, WIN_HEIGHT);

	machineGunTexture	= new Texture(L"_Texture/HeavyMachineGun.bmp", { 120, 115 }, { 1, 1 }, RGB(153, 217, 234));
	shotGunTexture		= new Texture(L"_Texture/ShotGun.bmp", { 115, 113 }, { 1, 1 }, RGB(153, 217, 234));

	weaponBody			= new Rect(Point(WIN_WIDTH * 0.05, WIN_HEIGHT * 0.92), Point(40, 40));
}

Shooting_GameManager::~Shooting_GameManager()
{
	delete frontBar;
	delete backBar;

	delete boardTexture;
	delete scoreBoardBody;

	delete machineGunTexture;
	delete shotGunTexture;

	DeleteObject(frontPen);
	DeleteObject(frontBrush);

	DeleteObject(backPen);
	DeleteObject(backBrush);

	DeleteObject(hFont);
}

void Shooting_GameManager::Update()
{
	if (isGameOver)
		return;

	if (weaponState != PISTOL)
	{
		weaponTimer += Time::Delta();

		if (weaponTimer >= 1.f)
		{
			weaponTimer -= 1.f;
			
			weaponTimeLeft = (weaponTimeLeft == 0) ? weaponTimeLeft : weaponTimeLeft - 1;
		}
	}
}

void Shooting_GameManager::Render(HDC hdc)
{
	HFONT oldFont = (HFONT)SelectObject(hdc, hFont);
	UINT prevAlign = SetTextAlign(hdc, TA_CENTER);
	int prevMode = SetBkMode(hdc, TRANSPARENT);

	RenderHpBar(hdc);
	RenderScore(hdc);

	if (isGameOver)
	{
		// Render GameOver
		RenderGameOver(hdc);

		SelectObject(hdc, oldFont);
		SetTextAlign(hdc, prevAlign);
		SetBkMode(hdc, prevMode);

		DeleteObject(oldFont);

		return;
	}

	RenderWeapon(hdc);

	SelectObject(hdc, oldFont);
	SetTextAlign(hdc, prevAlign);
	SetBkMode(hdc, prevMode);

	DeleteObject(oldFont);
}

void Shooting_GameManager::UpdatePlayerHpBar(const UINT& hp)
{
	float newXSize = MappingtoNewRange((float)hp, 0.f, (float)PLAYER_HP_MAX, 0.f, backBar->Size().x);

	// Update HP bar
	frontBar->SetRect
	(
		frontBar->Left(),
		frontBar->Top(),
		frontBar->Left() + newXSize,
		frontBar->Bottom()
	);
}

void Shooting_GameManager::UpdatePlayerWeaponState(const Weapon_State& weaponState)
{
	this->weaponState = weaponState;

	weaponTimeLeft = WEAPON_HOLD_TIME_MAX;
	weaponTimer = 0.f;
}

void Shooting_GameManager::RenderHpBar(HDC hdc)
{
	HPEN prevPen = (HPEN)SelectObject(hdc, backPen);
	HBRUSH prevBrush = (HBRUSH)SelectObject(hdc, backBrush);

	backBar->Render(hdc);

	SelectObject(hdc, frontPen);
	SelectObject(hdc, frontBrush);

	frontBar->Render(hdc);

	SelectObject(hdc, prevPen);
	SelectObject(hdc, prevBrush);
}

void Shooting_GameManager::RenderScore(HDC hdc)
{
	boardTexture->Render(scoreBoardBody);

	COLORREF prevColor = SetTextColor(hdc, RGB(238, 226, 222));

	wsprintf(lpOut, TEXT("== Score =="));
	TextOut(hdc, scoreBoardBody->Pos().x, scoreBoardBody->Pos().y - 35 , lpOut, lstrlen(lpOut));

	SetTextColor(hdc, RGB(179, 19, 18));

	TextOut(hdc, scoreBoardBody->Pos().x, scoreBoardBody->Pos().y - 5, to_wstring(score).c_str(), to_wstring(score).size());


	SetTextColor(hdc, prevColor);
}

void Shooting_GameManager::RenderWeapon(HDC hdc)
{
	switch (weaponState)
	{
	case PISTOL:
		return;
	case MACHINE_GUN:
	{

		machineGunTexture->Render(weaponBody);

		COLORREF prevColor = SetTextColor(hdc, RGB(238, 226, 222));
		TextOut(hdc, WIN_WIDTH * 0.1, WIN_HEIGHT * 0.905, to_wstring(weaponTimeLeft).c_str(), to_wstring(weaponTimeLeft).size());
		SetTextColor(hdc, prevColor);
	}
		break;
	case SHOT_GUN:
	{

		shotGunTexture->Render(weaponBody);

		COLORREF prevColor = SetTextColor(hdc, RGB(238, 226, 222));
		TextOut(hdc, WIN_WIDTH * 0.1, WIN_HEIGHT * 0.905, to_wstring(weaponTimeLeft).c_str(), to_wstring(weaponTimeLeft).size());
		SetTextColor(hdc, prevColor);
	}
		break;
	default:
		break;
	}
}

void Shooting_GameManager::RenderGameOver(HDC hdc)
{
	COLORREF prevColor = SetTextColor(hdc, RGB(255, 0, 0));

	wsprintf(lpOut, TEXT("GAME OVER!"));
	TextOut(hdc, WIN_WIDTH / 2, WIN_HEIGHT / 2, lpOut, lstrlen(lpOut));

	SetTextColor(hdc, prevColor);
}

