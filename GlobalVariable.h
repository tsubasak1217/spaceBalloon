#pragma once
class GlobalVariable {

public:
	int groundPos_;
	int cameraPos_;

	void Init() {
		groundPos_ = 720;
		cameraPos_ = 0;
	}

	int GetGroundPos() { return groundPos_; }
	void SetGroundPos(int groundPos) { groundPos_ = groundPos; }

	int GetCameraPos() { return cameraPos_; }
	void SetCameraPos(int cameraPos) { cameraPos_ = cameraPos; }
};