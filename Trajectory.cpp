#include "Trajectory.h"
#include <Novice.h>

void Trajectory::Update()
{
	lifespan--;
	color->subAlpha(4);

	location.x += vector.x;
	location.y += vector.y;
}

void Trajectory::Draw(GlobalVariable globalV)
{
	Novice::DrawEllipse(
		int(location.x) - globalV.GetCameraPosX(),
		int(location.y * -1.0f) + globalV.GetGroundPos() + globalV.GetCameraPosY(),
		int(size),
		int(size),
		0.0f,
		color->to_int(),
		kFillModeSolid
	);
}
