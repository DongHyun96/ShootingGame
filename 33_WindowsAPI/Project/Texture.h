#pragma once
class Texture
{
public:
	Texture(wstring path, POINT imageSize, POINT frameSize = {1, 1}, COLORREF transColor = COLOR_MAGENTA); // frameSize�� ���� ����( x 10�� y 2�� )
	~Texture();

	void Render(Rect* body, POINT curFrame = {0, 0}); // �簢�� ������ �׸��� �׸��� ���� ����, �ɰ� �������� index

private:
	HBITMAP hBitmap;
	HDC		memDC;

	COLORREF transColor;

	POINT imageSize		= {}; // ���� �̹��� ũ��
	POINT frameSize		= {}; // �ڸ� �������� ����
	POINT textureSize	= {}; // �߸� �̹����� ũ��

};
