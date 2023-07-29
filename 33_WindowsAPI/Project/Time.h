#pragma once
class Time
{
private:
	Time();
	~Time();

public:
	static Time* GetInstance();
	static void Delete();

public:
	void Update();
	void Render(); // backDC에 그릴 것이고 전역

	static float Delta() { return timeElapsed; }

private:
	static Time* instance;


private:
	static float timeElapsed; // 총 경과한 시간

	// Tick은 cpu의 진동수
	INT64 curTick			= 0;
	INT64 lastTick			= 0;
	INT64 ticksPerSecond	= 0;

	UINT frameCount			= 0;
	UINT frameRate			= 0;

	float runningTime		= 0.f; // 프로그램 시작 이후로 흐른 시간
	float scanningRate		= 0.f; // 주사율 -> 주사율에 맞게 frameRate를 제한 -> vSync
	
	float oneSecCount		= 0.f;
	
};
