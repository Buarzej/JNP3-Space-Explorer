#include "Entity.h"
#include <d2d1_3.h>
#include <math.h>

using D2D1::RectF;

Entity::Entity() = default;

Entity::Entity(
	INT x,
	INT y,
	INT width,
	INT height,
	FLOAT angle
)
	: x(x), y(y),
	width(width),
	height(height),
	angle(angle)
{ }

Entity::~Entity() { };

void Entity::SetX(INT newX) {
	x = newX;
}

void Entity::SetY(INT newY) {
	y = newY;
}

void Entity::SetWidth(INT newWidth) {
	width = newWidth;
}

void Entity::SetHeight(INT newHeight) {
	height = newHeight;
}

void Entity::SetAngle(FLOAT newAngle) {
	angle = fmodf(newAngle, 360.0f);
}

INT Entity::GetX() {
	return x;
}

INT Entity::GetY() {
	return y;
}

INT Entity::GetWidth() {
	return width;
}

INT Entity::GetHeight() {
	return height;
}

FLOAT Entity::GetAngle() {
	return angle;
}

D2D1_RECT_F Entity::GetRect() {
	return RectF(x, y, x + width, y + height);
}