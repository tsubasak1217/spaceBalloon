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