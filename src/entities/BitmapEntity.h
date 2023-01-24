#ifndef SPACESHOOTER_BITMAP_ENTITY_H
#define SPACESHOOTER_BITMAP_ENTITY_H

#include "Entity.h"
#include <d2d1_3.h>

class BitmapEntity : public Entity {
	PCWSTR bitmapUri;
	FLOAT opacity;
	D2D1_BITMAP_INTERPOLATION_MODE interpolation;

public:
	BitmapEntity();

	BitmapEntity(
		INT x,
		INT y,
		INT width,
		INT height,
		FLOAT angle,
		PCWSTR bitmapUri,
		FLOAT opacity = 1.0f,
		BOOL smoothInterpolation = FALSE
	);

	~BitmapEntity();

	PCWSTR GetBitmapUri();

	FLOAT GetOpacity();

	D2D1_BITMAP_INTERPOLATION_MODE GetInterpolation();
};

#endif // SPACESHOOTER_BITMAP_ENTITY_H