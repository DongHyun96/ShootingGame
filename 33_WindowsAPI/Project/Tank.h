#pragma once

#define MAX_POWER 650.f

class Tank
{
public:
	Tank();
	~Tank();

	void Update();
	void Render(HDC hdc);

	void RotateBarrel();
	void Move();
	void Fire();

	CannonBallManager* GetBalls() { return balls; }

private:
	Rect* body			= nullptr;
	Line* barrel		= nullptr;

	float barrelLength	= 200.f;
	float barrelAngle	= 0.f;	// 포신의 회전각도

	float speed			= 5.f; // 탱크의 움직임 속도

	//CannonBall* ball	= nullptr;
	CannonBallManager* balls = nullptr;

	bool isCharging = false; // power를 모으는 중인가

	float power = 0.f; // 포탄의 power

	Rect* frontBar = nullptr;
	Rect* backBar = nullptr;

	HBRUSH redBrush;

	Vector2 direction; // 포신의 direction
};
