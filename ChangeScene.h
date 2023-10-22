#pragma once
#include "Scene.h"

class ChangeScene{
private:
	bool isStartScene_;
	bool isFinishScene_;
	bool isReturnTitle_;

	int finishTimer_;
	int startTimer_;
	int returnTitleTimer_;

	bool initOrder_;

	//星の表示に関するもの
	bool isMoveStar_;
	bool moveMode_;
	float starT_;
	float starRadius_;
	float starTheta_;
	unsigned int starColor_[3] = {
		0xffffffff,
		0x7dfae3ff,
		0xff5181ff
	};

	//クリア時
	Vector2 clearStarPos_[32];
	float clearStarT_[32];
	float clearStarTheta_;
	float clearStarRadius_;
	int clearStarTimeCount_;



public:

	float easeT_;
	float startEaseT_;
	float returnEaseT_;
	int clearSceneRole_;

	int gameImgs_[1] = {
		Novice::LoadTexture("./Resources./Images./title./cloud3.png")
	};

	int whiteGH = Novice::LoadTexture("white1x1.png");

	//音声の変数
	int BGM_[4] = {
		Novice::LoadAudio("./Resources/Sounds/wind_BG.mp3"),
		Novice::LoadAudio("./Resources/Sounds/spaceBalloon_theme.wav"),
		Novice::LoadAudio("./Resources/Sounds/spaceBalloon_themeFX.wav"),
		Novice::LoadAudio("./Resources/Sounds/spaceBalloon_clear.wav"),
	};

	int BGMHandle[4] = {false};

	float volume[4] = { 0.0f };

	//イニシャライズ
	void Init() {
		isFinishScene_ = false;
		isStartScene_ = true;
		isReturnTitle_ = false;
		finishTimer_ = 120;
		returnTitleTimer_ = 80;
		clearSceneRole_ = 0;
		
		easeT_ = 0.0f;
		returnEaseT_ = 0.0f;
		startEaseT_ = 0.0f;
		
		isMoveStar_ = false;
		starT_ = 0.0f;
		starRadius_ = 0.0f;
		moveMode_ = 1;

		clearStarTheta_ = 0.0f;
		clearStarTimeCount_ = 0;
		clearStarRadius_ = 48.0f;
		for (int i = 0; i < 32; i++) {
			clearStarPos_[i].x = clearStarRadius_ + ((2.0f * clearStarRadius_) * i);
			clearStarPos_[i].y = -clearStarRadius_ * 2.0f;
			clearStarT_[i] = 0.0f;
		}
	}

	void Update(Scene& scene, char* keys);

	void DrawChangeStar();
	void DrawClearStar();
	void Draw(Scene scene);
	void Sound(Scene scene);

	//アクセッサ
	int GetFinishTimer() { return finishTimer_; }
	void SetFinishTimer(int value) { finishTimer_ = value; }

	int GetStartTimer() { return startTimer_; }
	void SetStartTimer(int value) { startTimer_ = value; }

	int GetReturnTimer() { return returnTitleTimer_; }
	void SetReturnTimer(int value) { returnTitleTimer_ = value; }

	bool GetIsFinish() { return isFinishScene_; }
	void SetIsFinish(bool flag) { isFinishScene_ = flag; }

	bool GetIsStart() { return isStartScene_; }
	void SetIsStart(bool flag) { isStartScene_ = flag; }

	bool GetIsReturnTitle() { return isReturnTitle_; }
	void SetIsReturnTitle(bool flag) { isReturnTitle_ = flag; }

	bool GetInitOrder() { return initOrder_; }
	void SetInitOrder(bool flag) { initOrder_ = flag; }

	void SetIsMoveStar(bool flag) { isMoveStar_ = flag; }
	void SetMoveMode(bool flag) { moveMode_ = flag; }
};

