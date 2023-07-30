#pragma once

#define MISSILE_HP 5

class Shooting_Missile : public Shooting_EnemyBullet
{
public:
	Shooting_Missile(Texture* texture);

	~Shooting_Missile();

	virtual void Update();
	virtual void Render(HDC hdc);

	virtual void Move();
	virtual void ApplyDamage();

private:
	void UpdateDirection();
	void UpdateSprite();

private:
	POINT curFrame = {};
	
	vector<Vector2> spriteDirections = {};

	UINT hp = MISSILE_HP;
};
