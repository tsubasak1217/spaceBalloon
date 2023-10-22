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

void ChangeScene::DrawClearStar() {

}

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

	if (isReturnTitle_) {
		if (returnTitleTimer_ > 0) {
			returnTitleTimer_--;
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
				finishTimer_ = 240;
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

		//クリア
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
				finishTimer_ = 120;
				easeT_ = 0;
				scene.SetSceneNum(clear);
			}
		}

		//タイトルに戻る
		if (isReturnTitle_) {

			returnEaseT_ += 0.01f;
			if (returnEaseT_ > 1.0f) {
				returnEaseT_ = 1.0f;
			}

			if (returnTitleTimer_ <= 0) {
				returnEaseT_ = 0;
				returnTitleTimer_ = 80;
				scene.SetSceneNum(titleScene);
				isReturnTitle_ = false;
				isStartScene_ = true;
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
			/*	Novice::DrawBox(
					0,
					int((EaseOutQuint(easeT_)) * -720),
					1280,
					720,
					0.0f,
					WHITE,
					kFillModeSolid
				);*/
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

		//雲を降りる
		if (isReturnTitle_) {

			Novice::DrawSprite(
				0,
				int(720 + (EaseOutQuint(returnEaseT_)) * -820),
				gameImgs_[0],
				1, 1,
				0.0f,
				WHITE
			);

			Novice::DrawBox(
				0,
				int(900 + ((EaseOutQuint(returnEaseT_)) * -720)),
				1280,
				720,
				0.0f,
				WHITE,
				kFillModeSolid
			);
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

void ChangeScene::Sound(Scene scene) {

	switch (scene.GetSceneNum()) {

	case titleScene:

		//開始時BGMを止める
		Novice::StopAudio(BGMHandle[1]);
		Novice::StopAudio(BGMHandle[2]);
		Novice::StopAudio(BGMHandle[3]);


		//風の音
		volume[0] = 0.3f;

		if (!Novice::IsPlayingAudio(BGMHandle[0]) or BGMHandle[0] == 0) {
			BGMHandle[0] = Novice::PlayAudio(BGM_[0], true, volume[0]);
		}

		break;

	case game:
		
		Novice::SetAudioVolume(BGMHandle[0], volume[0]);
		Novice::SetAudioVolume(BGMHandle[1], volume[1]);
		Novice::SetAudioVolume(BGMHandle[2], volume[2]);

		if (!Novice::IsPlayingAudio(BGMHandle[1]) or BGMHandle[1] == 0) {
			BGMHandle[1] = Novice::PlayAudio(BGM_[1], true, volume[1]);
		}

		if (!Novice::IsPlayingAudio(BGMHandle[2]) or BGMHandle[2] == 0) {
			BGMHandle[2] = Novice::PlayAudio(BGM_[2], true, volume[2]);
		}

		if (isFinishScene_) {
			volume[0] -= 0.001f;
			volume[1] -= 0.001f;
			volume[2] -= 0.001f;
		}

		break;

	case clear:

		//風の音を止める
		Novice::StopAudio(BGMHandle[0]);
		
		//クリアミュージック
		Novice::SetAudioVolume(BGMHandle[3], volume[3]);

		if (!Novice::IsPlayingAudio(BGMHandle[3]) or BGMHandle[3] == 0) {
			BGMHandle[3] = Novice::PlayAudio(BGM_[3], true, volume[3]);
		}

		//シーン開始時,終了時に音をフェードアウトする
		if (isFinishScene_) {
			volume[3] > 0.0f ? volume[3] -= 0.001f : false;
		} else {
			volume[3] = 0.1f;
		}

		break;

	default:
		break;
	}

}