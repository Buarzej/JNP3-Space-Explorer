#ifndef SPACESHOOTER_ENTITY_H
#define SPACESHOOTER_ENTITY_H

#include <d2d1_3.h>

class Entity {

protected:
	INT x, y, width, height;
	FLOAT angle;

public:
	Entity();
	
	Entity(
		INT x,
		INT y,
		INT width,
		INT height,
		FLOAT angle
	);

	virtual ~Entity() = 0;

	void SetX(INT newX);

	void SetY(INT newY);

	void SetWidth(INT newWidth);

	void SetHeight(INT newHeight);

	void SetAngle(FLOAT newAngle);

	INT GetX();

	INT GetY();

	INT GetWidth();

	INT GetHeight();

	FLOAT GetAngle();

	D2D1_RECT_F GetRect();
};

#endif // SPACESHOOTER_ENTITY_H