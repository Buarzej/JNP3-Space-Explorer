#ifndef SPACESHOOTER_GRAPHICS_ENGINE_H
#define SPACESHOOTER_GRAPHICS_ENGINE_H

#include "entities/Entity.h"
#include "entities/GradientEntity.h"
#include "entities/BitmapEntity.h"
#include "entities/TextEntity.h"
#include <d2d1_3.h>

// Colors.
D2D1_COLOR_F const bgColor1 =
{ .r = 0.f, .g = 0.f, .b = 0.f, .a = 1.0f };

D2D1_COLOR_F const bgColor2 =
{ .r = 0.1875f, .g = 0.015625f, .b = 0.28125f, .a = 1.0f };

D2D1_COLOR_F const textColor =
{ .r = 1.0f, .g = 1.0f, .b = 1.0f, .a = 1.0f };

template <class T> void SafeRelease(T** ppT) {
	if (*ppT) {
		(*ppT)->Release();
		*ppT = NULL;
	}
}

class GraphicsEngine {
	ID2D1Factory* d2dFactory;
	ID2D1HwndRenderTarget* d2dRenderTarget;
	IWICImagingFactory* IWICFactory;
	IDWriteFactory* dWriteFactory;

private:
	HRESULT LoadBitmapFromFile(
		ID2D1RenderTarget* pRenderTarget,
		IWICImagingFactory* pIWICFactory,
		PCWSTR uri,
		ID2D1Bitmap** ppBitmap
	);

	void ApplyRotation(Entity* entity);

public:
	GraphicsEngine();

	~GraphicsEngine();

	HRESULT UpdateTarget(HWND hwnd, RECT rc);

	void BeginDraw(const D2D1_COLOR_F* bgColor = NULL);

	HRESULT EndDraw();

	void DrawEntity(GradientEntity* entity);

	void DrawEntity(TextEntity* entity);

	void DrawEntity(BitmapEntity* entity);
};

#endif // SPACESHOOTER_GRAPHICS_ENGINE_H