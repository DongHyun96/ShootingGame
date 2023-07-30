#pragma once
class Texture
{
public:
	Texture(wstring path, POINT imageSize, POINT frameSize = {1, 1}, COLORREF transColor = COLOR_MAGENTA); // frameSize는 동작 개수( x 10개 y 2개 )
	~Texture();

	void Render(Rect* body, POINT curFrame = {0, 0}); // 사각형 영역에 그림을 그리게 만들 것임, 쪼갤 프레임의 index

private:
	HBITMAP hBitmap;
	HDC		memDC;

	COLORREF transColor;

	POINT imageSize		= {}; // 원본 이미지 크기
	POINT frameSize		= {}; // 자를 프레임의 개수
	POINT textureSize	= {}; // 잘린 이미지의 크기

};
