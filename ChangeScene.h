#pragma once
#include "Scene.h"
#include <Novice.h>
#include "Easing.h"
#include "MyFunc.h"

class ChangeScene{
private:
	bool isStartScene_;
	bool isFinishScene_;

	int finishTimer_;
	int startTimer_;
	
	bool initOrder_;

	//星の表示に関するもの
	bool isMoveStar_;
	float starT_;
	float starRadius_;
	float starTheta_;
	unsigned int starColor_[3] = {
		0xffa500ff,
		0xffff00ff,
		0xffffffff
	};


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
		isMoveStar_ = false;
		starT_ = 0.0f;
		starRadius_ = 0.0f;
		starTheta_ = 0.0f;
	}

	void Update(Scene& scene, char* keys);

	void DrawChangeStar();
	void Draw(Scene scene);

	//アクセッサ
	int GetFinishTimer() { return finishTimer_; }
	void SetFinishTimer(int value) { finishTimer_ = value; }

	int GetStartTimer() { return startTimer_; }
	void SetStartTimer(int value) { startTimer_ = value; }

	bool GetIsFinish() { return isFinishScene_; }
	void SetIsFinish(bool flag) { isFinishScene_ = flag; }

	bool GetIsStart() { return isStartScene_; }
	void SetIsStart(bool flag) { isStartScene_ = flag; }

	bool GetInitOrder() { return initOrder_; }
	void SetInitOrder(bool flag) { initOrder_ = flag; }

	void SetIsMoveStar(bool flag) { isMoveStar_ = flag; }
};

