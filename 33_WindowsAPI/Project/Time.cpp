#include "Framework.h"
#include "Time.h"

Time* Time::instance = nullptr;

float Time::timeElapsed = 0.f;

Time::Time()
{
	QueryPerformanceFrequency((LARGE_INTEGER*)&ticksPerSecond); // CPU의 초당 진동수를 기록해주는 함수

	QueryPerformanceCounter((LARGE_INTEGER*)&lastTick); // CPU의 진동(Tick) 누적 값
}

Time::~Time()
{
}

Time* Time::GetInstance()
{
	if (instance == nullptr)
		instance = new Time();

	return instance;
}

void Time::Delete()
{
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}

void Time::Update()
{
	QueryPerformanceCounter((LARGE_INTEGER*)&curTick);

	timeElapsed = (float)(curTick - lastTick) / (float)ticksPerSecond;

	runningTime += timeElapsed;

	oneSecCount += timeElapsed; // oneSecCount - 1초를 체크하기 위한 변수

	if (oneSecCount >= 1.0f) // 1초가 흘렀을 때
	{
		frameRate = frameCount;
		frameCount = 0;

		oneSecCount -= 1.0f;	// 정확히 딱 1초에서 안 멈출 수 있기 때문에 0으로 초기화를 시키지 않음
								// 살짝 지난 시간을 다음 계산에 넣어주어야 오차가 생기지 않음
	}

	frameCount++;

	lastTick = curTick;
}

void Time::Render()
{
	wstring str;

	str = L"RunningTime : " + to_wstring((int)runningTime);
	TextOut(backDC, 0, 0, str.c_str(), str.size());

	str = L"FPS : " + to_wstring((int)frameRate);
	TextOut(backDC, 0, 20, str.c_str(), str.size());
}

