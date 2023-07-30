#include "Framework.h"
#include "Shooting_ItemManager.h"


Shooting_ItemManager::Shooting_ItemManager()
{
	machineGunTexture	= new Texture(L"_Texture/HeavyMachineGun.bmp", { 120, 115 }, { 1, 1 }, RGB(153, 217, 234));
	shotGunTexture		= new Texture(L"_Texture/ShotGun.bmp", { 115, 113 }, { 1, 1 }, RGB(153, 217, 234));

	for (UINT i = 0; i < 20; i++)
	{
		itemMap[ITEM_MACHINEGUN].push_back(new Shooting_Item(ITEM_MACHINEGUN, machineGunTexture));
		itemMap[ITEM_SHOTGUN].push_back(new Shooting_Item(ITEM_SHOTGUN, shotGunTexture));
	}
}

Shooting_ItemManager::~Shooting_ItemManager()
{
	delete machineGunTexture;
	delete shotGunTexture;

	for (auto& pair : itemMap)
	{
		for (Shooting_Item* item : pair.second)
			delete item;
	}

	itemMap.clear();
}

void Shooting_ItemManager::Update()
{
	for (auto& pair : itemMap)
	{
		for (Shooting_Item* item : pair.second)
			item->Update();
	}
}

void Shooting_ItemManager::Render(HDC hdc)
{
	for (auto& pair : itemMap)
	{
		for (Shooting_Item* item : pair.second)
			item->Render(hdc);
	}
}

void Shooting_ItemManager::SpawnRandomItem(Point spawnPos)
{
	for (Shooting_Item* item : itemMap[(ItemType)(rand() % itemMap.size())])
	{
		if (item->IsActive())
			continue;

		item->Spawn(spawnPos);
		break;
	}
}

