#pragma once
class TextureScene : public Scene
{
public:
	TextureScene();
	~TextureScene();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

private:
	Texture* rockMan		= nullptr;
	Rect*	 rockManBody	= nullptr;

	POINT curFrame = {};

	float time = 0.f;
};
