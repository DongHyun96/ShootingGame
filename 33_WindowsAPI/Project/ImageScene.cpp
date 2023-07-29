#include "Framework.h"
#include "ImageScene.h"


ImageScene::ImageScene()
{
	// Project Directory, Solution Directory (경로는 project 경로가 있고, sln 경로가 있음)
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
		L"_Texture/록맨.bmp",
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

	// 이미지를 띄울 때는 BitBlt를 잘 쓰지 않음
	BitBlt
	(
		backDC,
		0, 0,
		843, 843,
		memDC,
		0, 0,
		SRCCOPY
	);

	//StretchBlt // 이것 역시 이미지를 줄이고 할 수는 있지만 많이 깨짐
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

	GdiTransparentBlt // 이것을 쓸 것임, 마지막 인자는 크로마키처럼 날릴 뒷배경 색
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
