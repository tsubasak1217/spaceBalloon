#include "Trajectory.h"
#include <Novice.h>

void Trajectory::Update()
{
	lifespan--;
	color->subAlpha(4);

	location += vector;
}

void Trajectory::Draw(GlobalVariable globalV)
{
	Novice::DrawEllipse(
		int(location.x), int(location.y * -1.0f) + globalV.GetGroundPos() + globalV.GetCameraPos(),
		10,
		10,
		0.0f,
		color->to_int(),
		kFillModeSolid
	);
}
