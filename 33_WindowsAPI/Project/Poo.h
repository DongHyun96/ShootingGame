#pragma once
class Poo
{
public:
	Poo();
	~Poo();

	void Update();
	void Render(HDC hdc);

	void Move();

	Circle* GetBody() { return body; }
private:
	float	speed = 0.f;
	
	Circle*	body = nullptr;

	HBRUSH	brush;
	HPEN	pen;
};
