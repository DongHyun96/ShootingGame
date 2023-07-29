#pragma once
class Shooting_PlayerBullet
{
public:
	Shooting_PlayerBullet(Texture* texture);
	~Shooting_PlayerBullet();

	void Update();
	void Render(HDC hdc);

	Rect* GetBody() { return body; }

	void SetActive(const bool& isActive) { this->isActive = isActive; }
	bool IsActive() const { return isActive; }

	void Fire(Point startPos, float speed, Vector2 direction);

private:

	void Move();

	void HandleBoundary();

private:
	Rect*	 body		= nullptr;
	Texture* texture	= nullptr;

	bool isActive = false;

	float speed = 0.f;
	Vector2 direction = {};
};
