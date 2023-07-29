#pragma once
class Shooting_Enemy
{
public:
	Shooting_Enemy(Texture* texture, Shooting_EBulletManager* bulletManager);
	~Shooting_Enemy();

	void Update();
	void Render(HDC hdc);

	Rect* GetBody() { return body; }

	void SetActive(const bool& isActive) { this->isActive = isActive; }
	bool IsActive() const { return isActive; }

	void Spawn(Point startPos, Point endPos);

	void ApplyDamage();

private:
	void Move();
	void FireWeapon();

	void HandleTextureFrame();

private:
	
	bool isActive = false;

	Rect* body = nullptr;
	Texture* texture = nullptr;

	POINT curFrame = {};

	float speed = 0.f;
	Vector2 direction = {};
	Point destination = {};

	UINT hp = 0;

	Shooting_EBulletManager* bulletManager = nullptr;


};
