#pragma once
class AvoidScene : public Scene
{
public:
	AvoidScene();
	~AvoidScene();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

private:
	vector<Poo*> objects;

	int time = 0;
};
