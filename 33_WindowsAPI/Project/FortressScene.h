#pragma once
class FortressScene : public Scene
{
public:
	FortressScene();
	~FortressScene();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

private:
	Tank* tank = nullptr;
	Rect* brick = nullptr;
};
