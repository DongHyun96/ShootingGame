#pragma once
class ArkanoidScene : public Scene
{
public:
	ArkanoidScene();
	~ArkanoidScene();

	// Scene을(를) 통해 상속됨
	virtual void Update() override;

	virtual void Render(HDC hdc) override;

private:
	ArkaPlayer*			player	= nullptr;
	ArkaBall*			ball	= nullptr;
	ArkaBrickManager*	bricks	= nullptr;
};


