#pragma once

class Shooting_EBulletManager
{
public:
	Shooting_EBulletManager();
	~Shooting_EBulletManager();

	void Update();
	void Render(HDC hdc);
	
	void FireDefaultRound(Point startPos, float speed = 450.f, Vector2 direction = { 0, 1 });
	void FireMissile(Point startPos, float speed = 450.f, Vector2 direction = { 0, 1 });

	vector<Shooting_EnemyBullet*>& GetBullets() { return bullets; }
	vector<Shooting_Missile*>& GetMissiles() { return missiles; }

private:
	vector<Shooting_EnemyBullet*> bullets = {};

	vector<Shooting_Missile*> missiles = {};

	Texture* bulletTexture = nullptr;
	Texture* missileTexture = nullptr;
};
