#include "Framework.h"
#include "ArkanoidScene.h"


ArkanoidScene::ArkanoidScene()
{
	player = new ArkaPlayer;

	Point pos =
	{
		player->GetBody()->Pos().x,
		player->GetBody()->Top() - 10
	};

	ball = new ArkaBall(pos, 10);

	bricks = new ArkaBrickManager;

	ball->SetBricksInfo(bricks);
}

ArkanoidScene::~ArkanoidScene()
{
	delete player;
	delete ball;
	delete bricks;
}

void ArkanoidScene::Update()
{
	player->Update();

	ball->SetPlayerInfo(player);
	ball->Update();
}

void ArkanoidScene::Render(HDC hdc)
{
	player->Render(hdc);
	ball->Render(hdc);
	bricks->Render(hdc);
}
