#include "BloodTrajectory.h"

void BloodTrajectory::Draw(GlobalVariable globalV)
{
	theta += static_cast<float>(M_PI) / 60;
	DrawTriangle({ location.x - globalV.GetCameraPosX(),
				location.y * -1.0f + globalV.GetGroundPos() + globalV.GetCameraPosY() },
			retainSize.x,
		theta,
		color.to_int()
	);
}
