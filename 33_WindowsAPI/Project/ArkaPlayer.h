#pragma once
class ArkaPlayer
{
public:
	ArkaPlayer();
	~ArkaPlayer();

	void Update();
	void Render(HDC hdc);

	Rect* GetBody() const { return body; }

	void Move();

private:
	Rect* body = nullptr;

	float speed = 500.f;

	HBRUSH hBrush;
};
