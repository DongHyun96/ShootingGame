#include "Framework.h"
#include "Shooting_Background.h"


Shooting_Background::Shooting_Background()
{
	Rect* body1 = new Rect(Point( WIN_WIDTH * 0.5f, -WIN_HEIGHT * 1.5f), { WIN_WIDTH, WIN_HEIGHT } );
	Rect* body2 = new Rect(Point(WIN_WIDTH * 0.5f, -WIN_HEIGHT * 0.5f), { WIN_WIDTH, WIN_HEIGHT });
	Rect* body3 = new Rect(WIN_CENTER, { WIN_WIDTH, WIN_HEIGHT });

	bodies.push_back(body1);
	bodies.push_back(body2);
	bodies.push_back(body3);

	texture = new Texture(L"_Texture/SpaceBackgound.bmp", { 512, 1024 }, { 1, 1 });
}

Shooting_Background::~Shooting_Background()
{
	delete texture;

	for (Rect* body : bodies)
		delete body;

	bodies.clear();
}

void Shooting_Background::Update()
{
	PullDownTextures();
	HandleSwapTexture();
}

void Shooting_Background::Render(HDC hdc)
{
	for (Rect* body : bodies)
		texture->Render(body);
}

void Shooting_Background::PullDownTextures()
{
	for (Rect* body : bodies)
		body->Pos() += Vector2(0, 1) * textureSpeed * Time::Delta();
}

void Shooting_Background::HandleSwapTexture()
{
	for (UINT i = 0; i < bodies.size(); i++)
	{
		if (bodies[i]->Top() >= WIN_HEIGHT)
		{
			bodies[i]->Pos() = Point(WIN_WIDTH * 0.5f, -WIN_HEIGHT * 1.5f);

			bodies[i]->SetRect
			(
				bodies[i]->Left(),
				bodies[topIdx]->Top() - WIN_HEIGHT,
				bodies[i]->Right(),
				bodies[topIdx]->Top()
			);

			topIdx = i;

			return;
		}
	}
}
