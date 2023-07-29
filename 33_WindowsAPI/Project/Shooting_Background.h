#pragma once

class Shooting_Background
{
public:
	Shooting_Background();
	~Shooting_Background();

	void Update();
	void Render(HDC hdc);

private:
	void PullDownTextures();
	void HandleSwapTexture();

private:
	
	Texture* texture = nullptr;

	vector<Rect*> bodies = {};

	float textureSpeed = 700.f;

	UINT topIdx = 0;
};
