#pragma once

class Shooting_Enemy
{
public:
	Shooting_Enemy();

	Shooting_Enemy(Texture* texture, Texture* explodeTexture, Shooting_EBulletManager* bulletManager, Shooting_ItemManager* itemManager);

	virtual ~Shooting_Enemy();

	void Update();
	void Render(HDC hdc);

	Rect* GetBody() { return body; }
	Point GetEndPos() const { return endPos; }

	void SetActive(const bool& isActive) { this->isActive = isActive; }
	bool IsActive() const { return isActive; }

	bool HasDestroyed() const { return hasDestroyed; }

	void Spawn(Point startPos, Point endPos);

	void ApplyDamage();

private:
	void Move();

	void HandleExplosionFrame();

protected:
	virtual void FireWeapon() = 0;
	virtual void HandleTextureFrame() = 0;

protected:
	
	bool hasDestroyed = false;
	bool isActive = false;

	Rect* body = nullptr;
	Texture* texture = nullptr;
	Point endPos = {};

	Rect* explodeBody		= nullptr;
	Texture* explodeTexture = nullptr;

	float textureTime = 0.f;

	POINT curFrame = {};

	float speed = 0.f;
	Vector2 direction = {};
	Point destination = {};

	UINT hp = 0;

	Shooting_EBulletManager* bulletManager = nullptr;

	Shooting_ItemManager* itemManager = nullptr;

	float fireTime = 0.f;

};
