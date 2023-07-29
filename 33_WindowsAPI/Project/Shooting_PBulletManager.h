#pragma once

class Shooting_PBulletManager
{
public:
	Shooting_PBulletManager();
	~Shooting_PBulletManager();

	void Update();
	void Render(HDC hdc);
	
	void Fire(Point startPos, float speed = 1000.f, Vector2 direction = { 0, -1 });

	vector<Shooting_PlayerBullet*>& GetBullets() { return bullets; }

private:
	vector<Shooting_PlayerBullet*> bullets;

	Texture* bulletTexture = nullptr;

};
