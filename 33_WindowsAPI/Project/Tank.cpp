#include "Framework.h"
#include "Tank.h"


Tank::Tank()
{
	body = new Rect(Point(200, 500), Point(200, 100));

	barrel = new Line(body->Pos(), { body->Pos().x + barrelLength, body->Pos().y });

	//ball = new CannonBall(barrel->end);
	balls = new CannonBallManager(30);

	frontBar = new Rect(50, 650, 50, 700);
	backBar  = new Rect(50, 650, 50 + MAX_POWER, 700);

	redBrush = CreateSolidBrush(RGB(255, 0, 0));
}

Tank::~Tank()
{
	delete body;
	delete barrel;
	//delete ball;
	delete balls;

	delete frontBar;
	delete backBar;

	DeleteObject(redBrush);
}

void Tank::Update()
{
	RotateBarrel();
	Move();
	Fire();

	//ball->Update();
	balls->Update();

}

void Tank::Render(HDC hdc)
{
	body->Render(hdc);
	barrel->Render(hdc);

	//ball->Render(hdc);
	balls->Render(hdc);

	backBar->Render(hdc);
	SelectObject(hdc, redBrush);
	frontBar->Render(hdc);
}

void Tank::RotateBarrel()
{
	/*if (GetAsyncKeyState('W'))
		barrelAngle += 0.05f;
	if (GetAsyncKeyState('S'))
		barrelAngle -= 0.05f;*/

	// Barrel의 angle을 mousePos에 의해 결정
	if ((mousePos - barrel->start).Length() != 0)
		direction = mousePos - barrel->start;
	
	direction.Normalize();
	
	barrel->end = barrel->start + direction * barrelLength;

	//barrelAngle = atanf(-direction.y / direction.x);

	/*barrelAngle = atan2f(-direction.y, direction.x); // atan2f는 부호를 알아서 정해줌

	barrel->end =
	{
		barrel->start.x + barrelLength * cosf(barrelAngle),
		barrel->start.y - barrelLength * sinf(barrelAngle)
	};*/
}

void Tank::Move()
{
	if (GetAsyncKeyState('A'))
		body->Pos().x -= speed;

	if (GetAsyncKeyState('D'))
		body->Pos().x += speed;
	
	barrel->start = body->Pos();

}

void Tank::Fire()
{
	if (GetAsyncKeyState(VK_SPACE))
	{
		isCharging = true;

		power += 3.f;

		if (power > MAX_POWER)
			power = MAX_POWER;
		//ball->Fire(barrel->end, barrelAngle, 100.f);

		frontBar->SetRect
		(
			frontBar->Left(),
			frontBar->Top(),
			frontBar->Left() + power,
			frontBar->Bottom()
		);
	}
	else
	{
		if (isCharging)
		{
			isCharging = false;

			//balls->Fire(barrel->end, barrelAngle, power);
			balls->Fire(barrel->end, direction, power);

			power = 0.f;
		}
	}
}
