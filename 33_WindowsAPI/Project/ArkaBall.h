#pragma once
class ArkaBall
{
public:
	ArkaBall();
	ArkaBall(Point pos, float radius);
	~ArkaBall();

	void Update();
	void Render(HDC hdc);
	
	void Move();

	Circle* GetBody() const { return body; }

	void Initialize();

	void CollisionWall();
	void CollisionPlayer();
	void CollisionBricks();

	void SetPlayerInfo(ArkaPlayer*			playerInfo) { this->playerInfo = playerInfo; }
	void SetBricksInfo(ArkaBrickManager*	bricksInfo) { this->bricksInfo = bricksInfo; }


private:
	Circle* body = nullptr;

	HBRUSH hBrush;

	float speed = 500.f;

	Vector2 dir = {};

	bool isPlay = false;

	ArkaPlayer*			playerInfo = nullptr; // 플레이어의 위쪽에 공을 배치해야 하는 순간이 있기 때문에 player 포인터를 지속적으로 받아옴
	ArkaBrickManager*	bricksInfo = nullptr;
};
