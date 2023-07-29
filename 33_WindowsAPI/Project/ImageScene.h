#pragma once
class ImageScene : public Scene
{
public:
	ImageScene();
	~ImageScene();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

private:
	HBITMAP hBitmap;
	HDC		memDC;

	HBITMAP rockMan;

	int index = 0;

	float time = 0.f;
};
