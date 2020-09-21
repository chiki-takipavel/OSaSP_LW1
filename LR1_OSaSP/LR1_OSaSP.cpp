// LR1_OSaSP.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "LR1_OSaSP.h"
#include "Sprite.h"
#include <cmath>
#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")

#define PI 3.14159265
#define IMAGE_FILE L"image.png"
#define MAX_LOADSTRING 100
#define TIMER_ID 1
#define TIMER_TIME 30

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

Sprite* sprite;

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL); // Начало работы GDI+

	sprite = new Sprite(0, 0, 62, 80, IMAGE_FILE);

	// Инициализация глобальных строк
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_LR1OSASP, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Выполнить инициализацию приложения:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LR1OSASP));

	MSG msg;

	// Цикл основного сообщения:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	GdiplusShutdown(gdiplusToken); // Завершение работы GDI+

	return (int)msg.wParam;
}

//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LR1OSASP));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

int x, y, angle;
static int dx = 5;
static int dy = 5;
bool mousePressed = false;
//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_KEYDOWN:
		switch (wParam) {
		case VK_LEFT:
			sprite->move(hWnd, -dx, 0);
			break;

		case VK_RIGHT:
			sprite->move(hWnd, dx, 0);
			break;

		case VK_UP:
			sprite->move(hWnd, 0, -dy);
			break;

		case VK_DOWN:
			sprite->move(hWnd, 0, dy);
			break;

		case VK_SPACE:
			SetTimer(hWnd, TIMER_ID, TIMER_TIME, 0);
			break;

		case VK_ESCAPE:
			KillTimer(hWnd, TIMER_ID);
			break;
		}
		break;

	case WM_LBUTTONDOWN:
		mousePressed = true;
		angle = rand() % 360;

		x = LOWORD(lParam);
		y = HIWORD(lParam);
		sprite->moveTo(hWnd, x, y);
		break;

	case WM_LBUTTONUP:
		mousePressed = false;
		break;

	case WM_MOUSEMOVE:
		if (mousePressed)
		{
			x = LOWORD(lParam);
			y = HIWORD(lParam);
			sprite->moveTo(hWnd, x, y);
		}
		break;

	case WM_MOUSEWHEEL:
	{
		int key = GET_KEYSTATE_WPARAM(wParam);
		int delta = GET_WHEEL_DELTA_WPARAM(wParam);

		if (delta > 0) {
			if (key == MK_SHIFT) {
				sprite->move(hWnd, dx, 0);
			}
			else {
				sprite->move(hWnd, 0, dy);
			}
		}
		else {
			if (key == MK_SHIFT) {
				sprite->move(hWnd, -dx, 0);
			}
			else {
				sprite->move(hWnd, 0, -dy);
			}
		}
	}
	break;

	case WM_PAINT:
		sprite->move(hWnd, 0, 0);
		sprite->draw(hWnd);
		break;

	case WM_TIMER:
		sprite->move(hWnd, dx * cos(angle * PI / 180.0), dy * sin(angle * PI / 180.0));
		if (sprite->widthBoundsIsCorrect)
		{
			dx = -dx;
			sprite->widthBoundsIsCorrect = false;
		}
		if (sprite->heightBoundsIsCorrect)
		{
			dy = -dy;
			sprite->heightBoundsIsCorrect = false;
		}
		break;

	case WM_DESTROY:
		delete sprite;
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
