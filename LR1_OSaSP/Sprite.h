#pragma once
#include <Windows.h>
#include <gdiplus.h>

using namespace Gdiplus;

class Sprite {
private:
	RECT spriteRect;
	int x, y;
	int width, height;
	int rebound = 5;
	const WCHAR* image;
public:
	bool widthBoundsIsCorrect;
	bool heightBoundsIsCorrect;

	Sprite(int _x, int _y, int _rx, int _ry, const WCHAR* _image);

	void move(HWND& hWnd, int dx, int dy);

	void moveTo(HWND& hWnd, int _x, int _y);

	void correctBounds(RECT windowRect);

	void draw(HWND hwnd);
};