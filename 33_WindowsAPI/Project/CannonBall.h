#pragma once
class CannonBall
{
public:
	CannonBall();
	CannonBall(Point startPos);
	~CannonBall();

	void Update();
	void Render(HDC hdc);


	void Fire(Point startPos, float angle, float power);
	void Fire(Point startPos, Vector2 dir, float power);

	void CollisionWall();

	bool IsActive() const { return isActive; }

	Circle* GetBody() const { return body; }

	Vector2& GetDir() { return direction; }

private:
	void Move();


private:
	Circle* body		= nullptr;

	float speed			= 0.f;
	float angle			= 0.f;

	bool isActive		= false;

	float gravityAccel	= 0.98f;
	float gravity		= 0.f;

	Vector2 direction;
};
