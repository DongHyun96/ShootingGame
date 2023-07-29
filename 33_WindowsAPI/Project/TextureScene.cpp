#include "Framework.h"
#include "TextureScene.h"


TextureScene::TextureScene()
{
	rockMan = new Texture(L"_Texture/·Ï¸Ç.bmp", { 480, 100 }, { 10, 2 });

	rockManBody = new Rect(WIN_CENTER, { 300, 300 });
}

TextureScene::~TextureScene()
{
	delete rockMan;
	delete rockManBody;
}

void TextureScene::Update()
{
	time += Time::Delta();

	if (time >= 0.05f)
	{
		time -= 0.05f;
		//++curFrame.x %= 10;

		curFrame.x--;
		curFrame.y = 1;

		if (curFrame.x < 0)
			curFrame.x = 9;

	}
}

void TextureScene::Render(HDC hdc)
{
	rockMan->Render(rockManBody, curFrame);
}
