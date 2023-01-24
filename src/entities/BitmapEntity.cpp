#include "BitmapEntity.h"
#include <d2d1_3.h>
#include <math.h>

using D2D1::RectF;

BitmapEntity::BitmapEntity() = default;

BitmapEntity::BitmapEntity(
	INT x,
	INT y,
	INT width,
	INT height,
	FLOAT angle,
	PCWSTR bitmapUri,
	FLOAT opacity,
	BOOL smoothInterpolation
)
	: Entity(x, y, width, height, angle),
	bitmapUri(bitmapUri),
	opacity(opacity),
	interpolation(
		smoothInterpolation ?
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR
		: D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR)
{ }

BitmapEntity::~BitmapEntity() = default;

PCWSTR BitmapEntity::GetBitmapUri() {
	return bitmapUri;
}

FLOAT BitmapEntity::GetOpacity() {
	return opacity;
}

D2D1_BITMAP_INTERPOLATION_MODE BitmapEntity::GetInterpolation() {
	return interpolation;
}