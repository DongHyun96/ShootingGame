#pragma once

class CollisionScene : public Scene
{
public:
	CollisionScene();
	~CollisionScene();

	// Scene을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

private:
	Circle* circle1;
	Circle* circle2;

	Rect* rect1;
	Rect* rect2;

	Line* line1;
	Line* line2;

	HBRUSH redBrush;
	HBRUSH blueBrush;
};
