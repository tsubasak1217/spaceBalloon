#pragma once
class GlobalVariable {

public:
	int groundPos_;
	int cameraPosY_;
	int cameraPosX_;
	int miniCameraPos_;

	void Init() {
		groundPos_ = 720;
		cameraPosX_ = 0;
		cameraPosY_ = 0;
		miniCameraPos_ = 0;
	}

	int GetGroundPos() { return groundPos_; }
	void SetGroundPos(int groundPos) { groundPos_ = groundPos; }

	int GetCameraPosX() { return cameraPosX_; }
	void SetCameraPosX(int cameraPosX) { cameraPosX_ = cameraPosX; }

	int GetCameraPosY() { return cameraPosY_; }
	void SetCameraPosY(int cameraPosY) { cameraPosY_ = cameraPosY; }

	int GetMiniCameraPos() { return miniCameraPos_; }
};

enum BlockType {
	normal = 1,
	wind_up = 2,
	wind_right = 3,
	wind_down = 4,
	wind_left = 5,
	bird = 6,
	birdArea = 66,
	thunder = 7,
	score = 8,
	life = 9,
	clockItem = 10,
	accel = 11,
	savePoint = 98,
	firstPos = 99
};

struct Vector2Int final {
	int x;
	int y;
};