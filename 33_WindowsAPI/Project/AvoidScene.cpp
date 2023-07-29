#include "Framework.h"
#include "AvoidScene.h"


AvoidScene::AvoidScene()
{
}

AvoidScene::~AvoidScene()
{
	for (Poo* poo : objects)
		delete poo;
	
	objects.clear();
}

void AvoidScene::Update()
{
	if (time > 10)
	{
		objects.push_back(new Poo);
		time = 0;
	}

	time++;
	
	int index = 0;

	for (Poo* poo : objects)
	{
		poo->Update();

		if (poo->GetBody()->Bottom() >= WIN_HEIGHT)
		{
			delete poo;
			objects.erase(objects.begin() + index);
		}

		index++;
	}
}

void AvoidScene::Render(HDC hdc)
{
	for (Poo* poo : objects)
		poo->Render(hdc);
}
