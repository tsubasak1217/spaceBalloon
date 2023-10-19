#include "ChangeScene.h"

void ChangeScene::Update(Scene& scene) {

	if (isStartScene_) {
		startTimer_--;
	}

	if (isFinishScene_) {
		finishTimer_--;
	}

	if (initOrder_) {
		initOrder_ = false;
	}

	if (finishTimer_ <= 0) {
		initOrder_ = true;
	}

	switch (scene.GetSceneNum()) {


	case titleScene://========================================================


		//シーン遷移

		if (isStartScene_) {

			easeT_ += 0.01f;
			if (easeT_ > 1.0f) {
				easeT_ = 1.0f;
			}

			if (startTimer_ <= 0) {
				isStartScene_ = false;
				startTimer_ = 120;
				easeT_ = 0.0f;
			}

		}

		if (isFinishScene_) {

			easeT_ += 0.01f;
			if (easeT_ > 1.0f) {
				easeT_ = 1.0f;
			}

			if (finishTimer_ <= 0) {
				isFinishScene_ = false;
				isStartScene_ = true;
				finishTimer_ = 120;
				easeT_ = 0;
				scene.SetSceneNum(game);
			}
		}

		break;

	case game://========================================================

		//シーン遷移
		if (isStartScene_) {

			easeT_ += 0.01f;
			if (easeT_ > 1.0f) {
				easeT_ = 1.0f;
			}

			if (startTimer_ <= 0) {
				isStartScene_ = false;
				startTimer_ = 60;
				easeT_ = 0.0f;
			}

		}

		if (isFinishScene_) {

			if (finishTimer_ <= 0) {
				isFinishScene_ = false;
				isStartScene_ = true;
				finishTimer_ = 240;
				easeT_ = 0;
				scene.SetSceneNum(clear);
			}
		}
		break;

	case clear://========================================================

		//シーン遷移
		if (isStartScene_) {

			if (startTimer_ <= 0) {
				isStartScene_ = false;
				startTimer_ = 60;
			}

		}

		if (isFinishScene_) {

			if (finishTimer_ <= 0) {
				isFinishScene_ = false;
				isStartScene_ = true;
				finishTimer_ = 120;
				easeT_ = 0;
				scene.SetSceneNum(titleScene);
			}
		}
		break;

	default:
		break;


	}
}

void ChangeScene::Draw(Scene scene) {

	switch (scene.GetSceneNum()) {

	case titleScene://========================================================

		if (isStartScene_) {

		}

		//雲が上から来る
		if (isFinishScene_) {
			Novice::DrawBox(
				0,
				int(-720 + (EaseInQuint(easeT_)) * 720),
				1280,
				720,
				0.0f,
				WHITE,
				kFillModeSolid
			);
		}

		break;

	case game:

		if (isStartScene_) {

			Novice::DrawSprite(
				0,
				int(0 + (EaseOutQuint(easeT_)) * 720),
				gameImgs_[0],
				1,1,
				0.0f,
				WHITE
			);
		}

		//雲が上から来る
		if (isFinishScene_) {
		}

		break;

	case clear:
		break;

	default:
		break;
	}
}
