#ifndef UNICODE
#define UNICODE
#endif 

#include "GraphicsEngine.h"
#include <stdexcept>
#include <wincodec.h>
#include <dwrite_3.h>

using D2D1::HwndRenderTargetProperties;
using D2D1::RenderTargetProperties;
using D2D1::SizeU;
using D2D1::RectF;
using D2D1::Point2F;
using D2D1::Matrix3x2F;
using D2D1::LinearGradientBrushProperties;

HRESULT GraphicsEngine::LoadBitmapFromFile(
	ID2D1RenderTarget* pRenderTarget,
	IWICImagingFactory* pIWICFactory,
	PCWSTR uri,
	ID2D1Bitmap** ppBitmap
) {
	IWICBitmapDecoder* pDecoder = NULL;
	IWICBitmapFrameDecode* pSource = NULL;
	IWICStream* pStream = NULL;
	IWICFormatConverter* pConverter = NULL;
	IWICBitmapScaler* pScaler = NULL;

	HRESULT hr = pIWICFactory->CreateDecoderFromFilename(
		uri,
		NULL,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&pDecoder
	);

	if (SUCCEEDED(hr))
		// Create the initial frame.
		hr = pDecoder->GetFrame(0, &pSource);

	if (SUCCEEDED(hr))
		// Convert the image format to 32bppPBGRA
		// (DXGI_FORMAT_B8G8R8A8_UNORM + D2D1_ALPHA_MODE_PREMULTIPLIED).
		hr = pIWICFactory->CreateFormatConverter(&pConverter);

	if (SUCCEEDED(hr))
		hr = pConverter->Initialize(
			pSource,
			GUID_WICPixelFormat32bppPBGRA,
			WICBitmapDitherTypeNone,
			NULL,
			0.f,
			WICBitmapPaletteTypeMedianCut
		);

	if (SUCCEEDED(hr))
		// Create a Direct2D bitmap from the WIC bitmap.
		hr = pRenderTarget->CreateBitmapFromWicBitmap(
			pConverter,
			NULL,
			ppBitmap
		);

	SafeRelease(&pDecoder);
	SafeRelease(&pSource);
	SafeRelease(&pStream);
	SafeRelease(&pConverter);
	SafeRelease(&pScaler);

	return hr;
}

void GraphicsEngine::ApplyRotation(Entity* entity) {
	if (entity->GetAngle() != 0.f) {
		UINT xCenter = entity->GetX() + entity->GetWidth() / 2;
		UINT yCenter = entity->GetY() + entity->GetHeight() / 2;
		d2dRenderTarget->SetTransform(
			Matrix3x2F::Rotation(
				entity->GetAngle(),
				Point2F(xCenter, yCenter)
			));
	}
	else {
		d2dRenderTarget->SetTransform(Matrix3x2F::Identity());
	}
}

GraphicsEngine::GraphicsEngine() {
	d2dRenderTarget = NULL;

	if (!SUCCEEDED(
		D2D1CreateFactory(
			D2D1_FACTORY_TYPE_SINGLE_THREADED,
			&d2dFactory)))
		throw std::runtime_error("Failed to create D2D factory.");

	// Initalize COM library.
	if (!SUCCEEDED(
		CoInitializeEx(
			NULL,
			COINIT_APARTMENTTHREADED)))
		throw std::runtime_error("Failed to initialize COM library.");

	// Create WIC factory.
	if (!SUCCEEDED(
		CoCreateInstance(
			CLSID_WICImagingFactory,
			NULL,
			CLSCTX_INPROC_SERVER,
			__uuidof(IWICImagingFactory),
			reinterpret_cast<LPVOID*>(&IWICFactory))))
		throw std::runtime_error("Failed to create WIC factory.");

	// Create DirectWrite factory.
	if (!SUCCEEDED(
		DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(IDWriteFactory),
			reinterpret_cast<IUnknown**>(&dWriteFactory))))
		throw std::runtime_error("Failed to create DirectWrite factory.");
}

GraphicsEngine::~GraphicsEngine() {
	SafeRelease(&d2dFactory);
	SafeRelease(&IWICFactory);
	SafeRelease(&dWriteFactory);
	SafeRelease(&d2dRenderTarget);
}

HRESULT GraphicsEngine::UpdateTarget(HWND hwnd, RECT rc) {
	SafeRelease(&d2dRenderTarget);

	return d2dFactory->CreateHwndRenderTarget(
		RenderTargetProperties(),
		HwndRenderTargetProperties(hwnd,
			SizeU(static_cast<UINT32>(rc.right) -
				static_cast<UINT32>(rc.left),
				static_cast<UINT32>(rc.bottom) -
				static_cast<UINT32>(rc.top))),
		&d2dRenderTarget);
}

void GraphicsEngine::BeginDraw(const D2D1_COLOR_F* bgColor) {
	if (!d2dRenderTarget)
		throw std::logic_error("Error while drawing: render target is not set.");

	d2dRenderTarget->BeginDraw();
	d2dRenderTarget->Clear(bgColor);
};

HRESULT GraphicsEngine::EndDraw() {
	HRESULT hr = d2dRenderTarget->EndDraw();

	return hr;
};

void GraphicsEngine::DrawEntity(GradientEntity* entity) {
	ID2D1LinearGradientBrush* brush = NULL;
	ID2D1GradientStopCollection* stops = NULL;

	D2D1_GRADIENT_STOP stopData[2];
	stopData[0] = entity->GetStopStart();
	stopData[1] = entity->GetStopEnd();

	if (!SUCCEEDED(
		d2dRenderTarget->CreateGradientStopCollection(
			stopData,
			2,
			&stops)))
		throw std::runtime_error("Failed to create gradient stop collection.");

	if (stops)
		if (!SUCCEEDED(d2dRenderTarget->CreateLinearGradientBrush(
			LinearGradientBrushProperties(
				entity->GetGradStart(), entity->GetGradEnd()
			), stops, &brush)))
			throw std::runtime_error("Failed to create gradient brush.");

	// Draw gradient.
	ApplyRotation(entity);
	d2dRenderTarget->FillRectangle(
		RectF(
			entity->GetX(),
			entity->GetY(),
			entity->GetX() + entity->GetWidth(),
			entity->GetY() + entity->GetHeight()
		),
		brush
	);

	SafeRelease(&brush);
	SafeRelease(&stops);
}

void GraphicsEngine::DrawEntity(TextEntity* entity) {
	ID2D1SolidColorBrush* brush = NULL;
	IDWriteTextFormat* textFormat = NULL;

	if (!SUCCEEDED(
		d2dRenderTarget->CreateSolidColorBrush(
			entity->GetFontColor(), &brush)))
		throw std::runtime_error("Failed to create brush.");

	if (!SUCCEEDED(
		dWriteFactory->CreateTextFormat(
			entity->GetFontName(),
			nullptr,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			entity->GetFontSize(),
			TEXT("en-us"),
			&textFormat)))
		throw std::runtime_error("Failed to create text format.");

	// Draw text.
	ApplyRotation(entity);
	d2dRenderTarget->DrawText(
		entity->GetText(),
		entity->GetTextLength(),
		textFormat,
		RectF(
			entity->GetX(),
			entity->GetY(),
			entity->GetX() + entity->GetWidth(),
			entity->GetY() + entity->GetHeight()
		),
		brush
	);

	SafeRelease(&brush);
	SafeRelease(&textFormat);
}

void GraphicsEngine::DrawEntity(BitmapEntity* entity) {

	ID2D1Bitmap* bitmap = NULL;

	if (!SUCCEEDED(
		LoadBitmapFromFile(
			d2dRenderTarget,
			IWICFactory,
			entity->GetBitmapUri(),
			&bitmap
		)
	))
		throw std::runtime_error("Failed to load bitmap.");

	// Draw bitmap.
	ApplyRotation(entity);
	d2dRenderTarget->DrawBitmap(
		bitmap,
		entity->GetRect(),
		entity->GetOpacity(),
		entity->GetInterpolation()
	);

	SafeRelease(&bitmap);
}