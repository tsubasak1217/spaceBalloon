#pragma once
#include "Scene.h"

class ChangeScene{
private:
	bool isChangeScene_;
	int shiftTimer_;

public:

	//イニシャライズ
	void Init() {
		isChangeScene_ = false;
		shiftTimer_ = 120;
	}

	void Update();

	void Draw();

	//アクセッサ
	int GetShiftTimer() { return shiftTimer_; }
	void SetShiftTimer(int value) { shiftTimer_ = value; }

	bool GetIsChange() { return isChangeScene_; }
	void SetIsChange(bool flag) { isChangeScene_ = flag; }
};

