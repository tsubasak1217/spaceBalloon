#include "Trajectory.h"
#include <Novice.h>
#include "Map.h"

void Trajectory::Update(Map map)
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
		int(retainSize.x),
		int(retainSize.y),
		0.0f,
		color->to_int(),
		kFillModeSolid
	);
}
