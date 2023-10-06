#pragma once
class GlobalVariable {

public:
	int groundPos_;
	int cameraPosY_;
	int cameraPosX_;

	void Init() {
		groundPos_ = 720;
		cameraPosX_ = 0;
		cameraPosY_ = 0;
	}

	int GetGroundPos() { return groundPos_; }
	void SetGroundPos(int groundPos) { groundPos_ = groundPos; }

	int GetCameraPosX() { return cameraPosX_; }
	void SetCameraPosX(int cameraPosX) { cameraPosX_ = cameraPosX; }

	int GetCameraPosY() { return cameraPosY_; }
	void SetCameraPosY(int cameraPosY) { cameraPosY_ = cameraPosY; }
};

enum BlockType {
	normal = 1,
	wind_up = 2,
	wind_right = 3,
	wind_down = 4,
	wind_left = 5,
	bird = 6,
	birdArea = 66,
	thunder = 7
};