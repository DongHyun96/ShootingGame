#include "Framework.h"
#include "ImageScene.h"


ImageScene::ImageScene()
{
	// Project Directory, Solution Directory (��δ� project ��ΰ� �ְ�, sln ��ΰ� ����)
	hBitmap = (HBITMAP)LoadImage
	(
		hInst, 
		L"_Texture/BTS.bmp",
		IMAGE_BITMAP,
		843, 843, 
		LR_LOADFROMFILE
	);

	rockMan = (HBITMAP)LoadImage
	(
		hInst,
		L"_Texture/�ϸ�.bmp",
		IMAGE_BITMAP,
		480, 100,
		LR_LOADFROMFILE
	);

	HDC hdc = GetDC(hWnd);

	memDC = CreateCompatibleDC(hdc);

	ReleaseDC(hWnd, hdc);
}

ImageScene::~ImageScene()
{
	DeleteObject(rockMan);
	DeleteObject(hBitmap);
	DeleteDC(memDC);
}

void ImageScene::Update()
{
	time += Time::Delta();

	if (time >= 0.1f)
	{
		//index++;
		++index %= 10;

		time -= 0.1f;
	}

}

void ImageScene::Render(HDC hdc)
{
	SelectObject(memDC, hBitmap);

	// �̹����� ��� ���� BitBlt�� �� ���� ����
	BitBlt
	(
		backDC,
		0, 0,
		843, 843,
		memDC,
		0, 0,
		SRCCOPY
	);

	//StretchBlt // �̰� ���� �̹����� ���̰� �� ���� ������ ���� ����
	//(
	//	backDC,
	//	843, 0,
	//	200, 200,
	//	memDC,
	//	0, 0,
	//	843, 843,
	//	SRCCOPY
	//);

	SelectObject(memDC, rockMan);

	GdiTransparentBlt // �̰��� �� ����, ������ ���ڴ� ũ�θ�Űó�� ���� �޹�� ��
	(
		backDC,
		200, 200,
		480 / 10, 100 / 2,
		memDC,
		480 / 10 * index, 0,
		480 / 10, 100 / 2,
		COLOR_MAGENTA
	);

}
