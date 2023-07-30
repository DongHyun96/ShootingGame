#pragma once
class Shooting_ItemManager
{
public:
	Shooting_ItemManager();
	~Shooting_ItemManager();

	void Update();
	void Render(HDC hdc);

	void SpawnRandomItem(Point spawnPos);

	map<ItemType, vector<Shooting_Item*>>& GetItemMap() { return itemMap; }

private:
	map<ItemType, vector<Shooting_Item*>> itemMap = {
		{ITEM_MACHINEGUN, {}},
		{ITEM_SHOTGUN, {}}
	};

	Texture* machineGunTexture = nullptr;
	Texture* shotGunTexture = nullptr;

};
