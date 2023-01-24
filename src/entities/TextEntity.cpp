#include "TextEntity.h"
#include "../GraphicsEngine.h"
#include <d2d1_3.h>
#include <math.h>

TextEntity::TextEntity() = default;

TextEntity::TextEntity(
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
)
	: Entity(x, y, width, height, angle),
	text(text), textLength(textLength),
	fontName(fontName), fontSize(fontSize),
	fontColor(fontColor)
{ }

TextEntity::~TextEntity() = default;

PCWSTR TextEntity::GetText() {
	return text;
}

UINT32 TextEntity::GetTextLength() {
	return textLength;
}

PCWSTR TextEntity::GetFontName() {
	return fontName;
}

FLOAT TextEntity::GetFontSize() {
	return fontSize;
}

D2D1_COLOR_F TextEntity::GetFontColor() {
	return fontColor;
}