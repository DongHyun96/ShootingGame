#pragma once
class ArkaBrickManager
{
public:
	ArkaBrickManager();
	~ArkaBrickManager();

	void Render(HDC hdc);

	void Stage1();
	void Stage2();

	bool IsClear();

	void Clear();

	vector<ArkaBrick*> GetObjects() { return objects; }

private:
	vector<ArkaBrick*> objects;
};
