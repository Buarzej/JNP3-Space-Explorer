#ifndef SPACESHOOTER_TEXT_ENTITY_H
#define SPACESHOOTER_TEXT_ENTITY_H

#include "Entity.h"
#include <d2d1_3.h>

class TextEntity : public Entity {
	PCWSTR text;
	UINT32 textLength;
	PCWSTR fontName;
	FLOAT fontSize;
	D2D1_COLOR_F fontColor;

public:
	TextEntity();

	TextEntity(
		INT x,
		INT y,
		INT width,
		INT height,
		FLOAT angle,
		PCWSTR text,
		UINT32 textLength,
		PCWSTR fontName,
		FLOAT fontSize,
		D2D1_COLOR_F fontColor
	);

	~TextEntity();

	PCWSTR GetText();

	UINT32 GetTextLength();

	PCWSTR GetFontName();

	FLOAT GetFontSize();

	D2D1_COLOR_F GetFontColor();
};

#endif // SPACESHOOTER_TEXT_ENTITY_H