#include "Framework.h"
#include "Texture.h"



Texture::Texture(wstring path, POINT imageSize, POINT frameSize, COLORREF transColor)
	:imageSize(imageSize), frameSize(frameSize), transColor(transColor)
{
	textureSize =
	{
		imageSize.x / frameSize.x,
		imageSize.y / frameSize.y
	};

	hBitmap = (HBITMAP)LoadImage
	(
		hInst,
		path.c_str(),
		IMAGE_BITMAP,
		imageSize.x, imageSize.y,
		LR_LOADFROMFILE
	);

	HDC hdc = GetDC(hWnd);

	memDC = CreateCompatibleDC(hdc);

	ReleaseDC(hWnd, hdc);

	SelectObject(memDC, hBitmap);
}

Texture::~Texture()
{
	DeleteObject(hBitmap);
	DeleteDC(memDC);
}

void Texture::Render(Rect* body, POINT curFrame)
{

	GdiTransparentBlt
	(
		backDC,
		body->Left(), body->Top(),
		body->Size().x, body->Size().y,
		memDC,
		textureSize.x * curFrame.x, textureSize.y * curFrame.y,
		textureSize.x, textureSize.y,
		transColor
	);
}
