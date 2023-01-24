#ifndef SPACESHOOTER_GRADIENT_ENTITY_H
#define SPACESHOOTER_GRADIENT_ENTITY_H

#include "Entity.h"
#include <d2d1_3.h>
#include <array>

class GradientEntity : public Entity {
	D2D1_POINT_2F gradStart, gradEnd;
	D2D1_GRADIENT_STOP stopStart, stopEnd;

public:
	GradientEntity();

	GradientEntity(
		INT x,
		INT y,
		INT width,
		INT height,
		FLOAT angle,
		D2D1_POINT_2F gradStart,
		D2D1_POINT_2F gradEnd,
		D2D1_GRADIENT_STOP stopStart,
		D2D1_GRADIENT_STOP stopEnd
	);

	~GradientEntity();

	D2D1_POINT_2F GetGradStart();

	D2D1_POINT_2F GetGradEnd();

	D2D1_GRADIENT_STOP GetStopStart();

	D2D1_GRADIENT_STOP GetStopEnd();

	void SetGradStart(D2D1_POINT_2F newStart);

	void SetGradEnd(D2D1_POINT_2F newEnd);
};

#endif // SPACESHOOTER_GRADIENT_ENTITY_H