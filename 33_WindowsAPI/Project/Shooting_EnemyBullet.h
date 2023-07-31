#pragma once
class Shooting_EnemyBullet
{
public:
	Shooting_EnemyBullet(Texture* texture);
	virtual ~Shooting_EnemyBullet();

	virtual void Update();
	virtual void Render(HDC hdc);

	Rect* GetBody() { return body; }

	void SetActive(const bool& isActive) { this->isActive = isActive; }
	bool IsActive() const { return isActive; }

	void Fire(Point startPos, float speed, Vector2 direction);

	virtual void ApplyDamage();

	virtual bool HasDestroyed() const;
	virtual void HandleDestroyed();

protected:

	virtual void Move();

	void HandleBoundary();

protected:
	Rect* body = nullptr;
	Texture* texture = nullptr;

	bool isActive = false;

	float speed = 0.f;
	Vector2 direction = {};
};
