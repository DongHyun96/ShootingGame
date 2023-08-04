#include "Framework.h"
#include "MainGame.h"

MainGame::MainGame()
{
	srand(time(NULL));

	HDC hdc = GetDC(hWnd); // �� hWnd�� ����Ǿ� �ִ� hdc(���� hdc)�� ������

	hBitmap = CreateCompatibleBitmap(hdc, WIN_WIDTH, WIN_HEIGHT); // �� hdc�� ȣȯ ������ ��Ʈ�� ���� 
	backDC = CreateCompatibleDC(hdc);

	SelectObject(backDC, hBitmap);

	ReleaseDC(hWnd, hdc);

	//SetFullScreen();

	//scene = new PaintScene;
	//scene = new CollisionScene;
	//scene = new AvoidScene;
	//scene = new FortressScene;
	//scene = new ArkanoidScene;
	//scene = new ImageScene;
	//scene = new TextureScene;
	scene = new ShootingScene;
}

MainGame::~MainGame()
{
	delete scene;

	DeleteDC(backDC);
	DeleteObject(hBitmap);

	Time::Delete();
}

void MainGame::Update()
{
	scene->Update();

	Time::GetInstance()->Update();
}

void MainGame::Render(HDC hdc)
{
	// backDC invalidateRect
	PatBlt // Ư�� �������� ȭ���� �ʱ�ȭ���ִ� �Լ� , ȭ���� �Ͼ�� �ʱ�ȭ (�̰� InvalidateRect�Լ��� ����� �Լ�)
	(
		backDC, 0, 0, WIN_WIDTH, WIN_HEIGHT, WHITENESS
	);

	scene->Render(backDC); // backDC�� �׸�

	Time::GetInstance()->Render();

	// ���� hdc�� backDC�� ����
	BitBlt // bit�� �Լ� / ��� ���� (ȭ���� �������ִ� �Լ�), Src(Source, ����) -> Dest(Destination, ������, ���)
	(
		hdc, 0, 0, WIN_WIDTH, WIN_HEIGHT, backDC, 0, 0, SRCCOPY
	);
}

void MainGame::SetFullScreen()
{
	// Remove window borders and title bar
	LONG_PTR style = GetWindowLongPtr(hWnd, GWL_STYLE);
	SetWindowLongPtr(hWnd, GWL_STYLE, style & ~(WS_CAPTION | WS_THICKFRAME | WS_BORDER | WS_SYSMENU));

	// Maximize the window to cover the entire screen
	SetWindowPos(hWnd, NULL, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), SWP_FRAMECHANGED);
}
