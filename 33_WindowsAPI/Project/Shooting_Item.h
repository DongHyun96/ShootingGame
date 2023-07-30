#pragma once

enum ItemType
{
	ITEM_MACHINEGUN,
	ITEM_SHOTGUN
};

class Shooting_Item
{
public:
	Shooting_Item(ItemType type, Texture* texture);
	~Shooting_Item();

	void Update();
	void Render(HDC hdc);
	
	void Spawn(const Point& spawnPos);

	void SetActive(const bool& isActive) { this->isActive = isActive; }
	bool IsActive() const { return isActive; }

	Rect* GetBody() { return body; }

private:
	void Move();
	void HandleCollisionWall();
	void CheckTimeElapsed();

private:

	ItemType type;

	Texture* texture = nullptr;
	Rect* body = nullptr;

	bool isActive = false;

	float speed = 400.f;
	Vector2 direction = {};

	float timeElapsed = 0.f;
};
