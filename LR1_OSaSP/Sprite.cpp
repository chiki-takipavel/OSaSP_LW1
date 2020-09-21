#include "Sprite.h"
#include <gdiplus.h>

using namespace Gdiplus;

Sprite::Sprite(int _x, int _y, int _width, int _height, const WCHAR* _image) {
	x = _x;
	y = _y;
	width = _width;
	height = _height;
	image = _image;

	spriteRect.left = x - width - 1;
	spriteRect.top = y - height - 1;
	spriteRect.right = x + width + 1;
	spriteRect.bottom = y + height + 1;
	widthBoundsIsCorrect = false;
	heightBoundsIsCorrect = false;
}

void Sprite::moveTo(HWND& hWnd, int _x, int _y) {
	InvalidateRect(hWnd, &spriteRect, true);
	x = _x; y = _y;

	RECT windowRect;
	GetClientRect(hWnd, &windowRect);
	correctBounds(windowRect);

	spriteRect.left = x - width - 1;
	spriteRect.top = y - height - 1;
	spriteRect.right = x + width + 1;
	spriteRect.bottom = y + height + 1;

	InvalidateRect(hWnd, &spriteRect, false);
}

void Sprite::move(HWND& hWnd, int dx, int dy) {
	InvalidateRect(hWnd, &spriteRect, true);
	x += dx; y += dy;

	RECT windowRect;
	GetClientRect(hWnd, &windowRect);
	correctBounds(windowRect);

	spriteRect.left = x - width - 1;
	spriteRect.top = y - height - 1;
	spriteRect.right = x + height + 1;
	spriteRect.bottom = y + height + 1;

	InvalidateRect(hWnd, &spriteRect, false);
}

void Sprite::correctBounds(RECT windowRect) {
	if (x + width > windowRect.right)
	{
		x -= rebound + width / 2;
		widthBoundsIsCorrect = true;
	}
	if (x < windowRect.left)
	{
		x += rebound + width / 2;
		widthBoundsIsCorrect = true;
	}
	if (y + height > windowRect.bottom)
	{
		y -= rebound + height / 2;
		heightBoundsIsCorrect = true;
	}
	if (y < windowRect.top)
	{
		y += rebound + height / 2;
		heightBoundsIsCorrect = true;
	}
}

void Sprite::draw(HWND hWnd) {
	PAINTSTRUCT ps;
	HDC hDC = BeginPaint(hWnd, &ps);
	Graphics graphics(hDC);
	Image img = image;
	graphics.DrawImage(&img, x, y, width, height);
	EndPaint(hWnd, &ps);
}