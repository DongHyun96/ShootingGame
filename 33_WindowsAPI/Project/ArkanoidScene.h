#pragma once
class ArkanoidScene : public Scene
{
public:
	ArkanoidScene();
	~ArkanoidScene();

	// Scene��(��) ���� ��ӵ�
	virtual void Update() override;

	virtual void Render(HDC hdc) override;

private:
	ArkaPlayer*			player	= nullptr;
	ArkaBall*			ball	= nullptr;
	ArkaBrickManager*	bricks	= nullptr;
};

