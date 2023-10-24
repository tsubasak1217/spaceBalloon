#include "Trajectory.h"
#include <Novice.h>
#include "Map.h"
#include <math.h>

void Trajectory::Update()
{
	lifespan--;
	color.subAlpha(4);
	location.x += vector.x;
	location.y += vector.y;
}

void Trajectory::Draw(GlobalVariable globalV,Scene scene)
{
   	switch (scene.GetSceneNum()) {

	case titleScene:
		Novice::DrawEllipse(
			int(location.x),
			int(location.y * -1.0f) + globalV.GetGroundPos(),
			int(retainSize.x),
			int(retainSize.y),
			0.0f,
			color.to_int(),
			kFillModeSolid
		);
		break;

	default:
		
   		Novice::DrawEllipse(
			int(location.x) - globalV.GetCameraPosX(),
			int(location.y * -1.0f) + globalV.GetGroundPos() + globalV.GetCameraPosY(),
			int(retainSize.x),
			int(retainSize.y),
			0.0f,
			color.to_int(),
			kFillModeSolid
		);
		break;
	}
	
}
