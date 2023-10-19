#include "ChangeScene.h"


void ChangeScene::DrawChangeStar() {

	if (moveMode_ == 1) {
		starT_ += 0.01f;
		if (starT_ > 1.0f) {
			starT_ = 1.0f;
		}
	} else {
		starT_ -= 0.01f;
		if (starT_ < 0.0f) {
			starT_ = 0.0f;
			isMoveStar_ = false;
		}
	}


	starTheta_ += (1.0f / 48.0f) * float(M_PI);


	DrawStar(
		{ 640.0f,360.0f },
		EaseInOutExpo(starT_) * 8000,
		starTheta_,
		starColor_[2]
	);

	DrawStar(
		{ 640.0f,360.0f },
		EaseInOutExpo(starT_) * 4000,
		starTheta_,
		starColor_[1]
	);

	DrawStar(
		{ 640.0f,360.0f },
		EaseInOutExpo(starT_) * 2000,
		starTheta_,
		starColor_[0]
	);


};

void ChangeScene::Update(Scene& scene, char* keys) {

	if (isStartScene_) {
		if (startTimer_ > 0) {
			startTimer_--;
		}
	}

	if (isFinishScene_) {
		if (finishTimer_ > 0) {
			finishTimer_--;
		}
	}


	switch (scene.GetSceneNum()) {


	case titleScene://========================================================


		//シーン遷移

		if (isStartScene_) {

			//easeT_ += 0.01f;
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
				startTimer_ = 120;
				easeT_ = 0.0f;
			}

		}

		if (isFinishScene_) {

			if (finishTimer_ <= 120) {
				easeT_ += 0.01f;
				if (easeT_ > 1.0f) {
					easeT_ = 1.0f;
				}
			}

			if (finishTimer_ <= 0) {
				isFinishScene_ = false;
				isStartScene_ = true;
				finishTimer_ = 30;
				easeT_ = 0;
				scene.SetSceneNum(clear);
			}
		}
		break;

	case clear://========================================================

		//シーン遷移
		if (isStartScene_) {

			easeT_ += 0.01f;
			if (easeT_ > 1.0f) {
				easeT_ = 1.0f;
			}


			if (startTimer_ <= 0) {

				if (clearSceneRole_ == 1) {
					clearSceneRole_++;
				}

				if (keys[DIK_SPACE]) {
					clearSceneRole_++;
					easeT_ = 0.0f;

					if (clearSceneRole_ == 1) {
						startTimer_ = 240;
					} else {
						startTimer_ = 120;
					}
				}


				if (clearSceneRole_ >= 3) {
					isStartScene_ = false;
					isFinishScene_ = true;
					clearSceneRole_ = 0;
				}
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
				1, 1,
				0.0f,
				WHITE
			);
		}

		//雲が上から来る
		if (isFinishScene_) {
		}

		if (isMoveStar_) {
			DrawChangeStar();
		}

		break;

	case clear:
		break;

	default:
		break;
	}
}
