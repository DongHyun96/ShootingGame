#pragma once

class CannonBallManager
{
public:
	CannonBallManager(UINT poolCount);
	~CannonBallManager();

	void Update();
	void Render(HDC hdc);

	void Fire(Point startPos, float angle, float power);
	void Fire(Point startPos, Vector2 dir, float power);

	vector<CannonBall*> GetObjects() const { return objects; }

private:
	vector<CannonBall*> objects; // Object Ǯ
};
