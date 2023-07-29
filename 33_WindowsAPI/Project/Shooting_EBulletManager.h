#pragma once

class Shooting_EBulletManager
{
public:
	Shooting_EBulletManager();
	~Shooting_EBulletManager();

	void Update();
	void Render(HDC hdc);
	
	void Fire(Point startPos, float speed = 450.f, Vector2 direction = { 0, 1 });

	vector<Shooting_EnemyBullet*>& GetBullets() { return bullets; }

private:
	vector<Shooting_EnemyBullet*> bullets = {};

	Texture* bulletTexture = nullptr;
};
