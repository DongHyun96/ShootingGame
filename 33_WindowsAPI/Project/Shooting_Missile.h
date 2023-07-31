#pragma once

#define MISSILE_HP 3

class Shooting_Missile : public Shooting_EnemyBullet
{
public:
	Shooting_Missile(Texture* texture, Texture* explosionTexture);

	~Shooting_Missile();

	virtual void Update();
	virtual void Render(HDC hdc);

	virtual void Move() override;
	virtual void ApplyDamage() override;
	virtual bool HasDestroyed() const override { return hasDestroyed; }
	virtual void HandleDestroyed() override;

private:
	void UpdateDirection();
	void UpdateSprite();

	void HandleExplosionFrame();
	

private:

	bool hasDestroyed = false;

	POINT curFrame = {};
	
	vector<Vector2> spriteDirections = {};

	UINT hp = MISSILE_HP;
	
	Texture* explosionTexture = nullptr;

	float textureTime = 0.f;
};
