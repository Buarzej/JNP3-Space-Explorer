#ifndef UNICODE
#define UNICODE
#endif 

#include "MainWindow.h"
#include "GraphicsEngine.h"
#include "GameEngine.h"
#include <windows.h>
#include <windowsx.h>
#include <d2d1_3.h>
#include <wincodec.h>
#include <stdexcept>
#include <sysinfoapi.h>

using D2D1::RenderTargetProperties;
using D2D1::HwndRenderTargetProperties;
using D2D1::SizeU;
using D2D1::BitmapProperties;
using D2D1::PixelFormat;
using D2D1::RectF;
using D2D1::Matrix3x2F;

static GraphicsEngine* graphicsEngine;
static GameEngine* gameEngine;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI wWinMain(_In_ [[maybe_unused]] HINSTANCE hInstance,
	_In_opt_ [[maybe_unused]] HINSTANCE hPrevInstance,
	_In_ [[maybe_unused]] PWSTR pCmdLine,
	_In_ [[maybe_unused]] INT nCmdShow) {

	static const DWORD gameTick = 30; // in miliseconds

	// Register the window class.
	const wchar_t WND_CLASS_NAME[] = TEXT("Space Explorer");

	WNDCLASSEX wc = { };

	wc.lpfnWndProc = WindowProc;
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;
	wc.lpszClassName = WND_CLASS_NAME;
	wc.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);

	if (RegisterClassEx(&wc) == 0)
		return 1;

	// Create the window.
	HWND hWnd = CreateWindowEx(
		0,                     // Optional window styles.
		WND_CLASS_NAME,        // Window class
		TEXT("Space Shooter"),	   // Window text
		WS_OVERLAPPEDWINDOW,   // Window style

		// Size and position
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

		NULL,       // Parent window    
		NULL,       // Menu
		hInstance,  // Instance handle
		NULL        // Additional application data
	);

	if (hWnd == NULL)
		return 1;

	ShowWindow(hWnd, nCmdShow);

	// Run the message loop.
	MSG msg = { };
	DWORD lastTickCount = GetTickCount64();
	do {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message != WM_QUIT) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
	} while (msg.message != WM_QUIT);

	return 0;
}

LRESULT CALLBACK WindowProc(
	HWND hwnd, UINT uMsg,
	WPARAM wParam, LPARAM lParam
) {
	switch (uMsg) {
	case WM_CREATE:
		graphicsEngine = new GraphicsEngine();
		gameEngine = new GameEngine(graphicsEngine);

		return 0;

	case WM_DESTROY:
		delete graphicsEngine;
		delete gameEngine;

		PostQuitMessage(0);
		return 0;

	case WM_CLOSE:
		DestroyWindow(hwnd);
		return 0;

	case WM_LBUTTONDOWN:
		if (!gameEngine->IsGameRunning()) {
			gameEngine->StartGame();
			gameEngine->UpdateRelativeValues(
				GET_X_LPARAM(lParam),
				GET_Y_LPARAM(lParam)
			);
			gameEngine->RenderCurrState();
		}
		else {
			gameEngine->GameTick();
		}
		return 0;

	case WM_MOUSEMOVE:
		if (gameEngine->IsGameRunning()) {
			gameEngine->UpdateRelativeValues(
				GET_X_LPARAM(lParam),
				GET_Y_LPARAM(lParam)
			);
			gameEngine->RenderCurrState();
		}

		return 0;

	case WM_PAINT:
		RECT rc;
		GetClientRect(hwnd, &rc);

		graphicsEngine->UpdateTarget(hwnd, rc);

		gameEngine->UpdateRelativeValues(rc);
		gameEngine->RenderCurrState();

		return 0;
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}