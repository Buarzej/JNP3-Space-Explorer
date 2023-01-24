#include "GradientEntity.h"
#include <d2d1_3.h>
#include <math.h>

using D2D1::RectF;

GradientEntity::GradientEntity() = default;

GradientEntity::GradientEntity(
	INT x,
	INT y,
	INT width,
	INT height,
	FLOAT angle,
	D2D1_POINT_2F gradStart,
	D2D1_POINT_2F gradEnd,
	D2D1_GRADIENT_STOP stopStart,
	D2D1_GRADIENT_STOP stopEnd
)
	: Entity(x, y, width, height, angle),
	gradStart(gradStart),
	gradEnd(gradEnd),
	stopStart(stopStart),
	stopEnd(stopEnd)
{ }

GradientEntity::~GradientEntity() = default;

D2D1_POINT_2F GradientEntity::GetGradStart() {
	return gradStart;
}

D2D1_POINT_2F GradientEntity::GetGradEnd() {
	return gradEnd;
}

D2D1_GRADIENT_STOP GradientEntity::GetStopStart() {
	return stopStart;
}

D2D1_GRADIENT_STOP GradientEntity::GetStopEnd() {
	return stopEnd;
}

void GradientEntity::SetGradStart(D2D1_POINT_2F newStart) {
	gradStart = newStart;
}

void GradientEntity::SetGradEnd(D2D1_POINT_2F newEnd) {
	gradEnd = newEnd;
}