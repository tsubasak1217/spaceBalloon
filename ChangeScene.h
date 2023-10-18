#pragma once
#include "Scene.h"
#include <Novice.h>
#include "Easing.h"

class ChangeScene{
private:
	bool isStartScene_;
	bool isFinishScene_;

	int finishTimer_;
	int startTimer_;
	

	bool initOrder_;

public:

	float easeT_;
	int clearSceneRole_;

	int gameImgs_[1] = {
		Novice::LoadTexture("./Resources./Images./title./cloud3.png")
	};


	//イニシャライズ
	void Init() {
		isFinishScene_ = false;
		isStartScene_ = true;
		finishTimer_ = 120;
		clearSceneRole_ = 0;
		easeT_ = 0.0f;
	}

	void Update(Scene& scene, char* keys);

	void Draw(Scene scene);

	//アクセッサ
	int GetFinishTimer() { return finishTimer_; }
	void SetFinishTimer(int value) { finishTimer_ = value; }

	bool GetIsFinish() { return isFinishScene_; }
	void SetIsFinish(bool flag) { isFinishScene_ = flag; }

	bool GetIsStart() { return isStartScene_; }
	void SetIsStart(bool flag) { isStartScene_ = flag; }

	bool GetInitOrder() { return initOrder_; }
	void SetInitOrder(bool flag) { initOrder_ = flag; }
};

