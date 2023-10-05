#include "Player.h"

// アップデート
void Player::Update(char* keys,int* cameraPosX, int* cameraPosY) {

	// 風船が膨らんだりしぼんだりする処理
	if (keys[DIK_SPACE]) {
		if (balloonLevel_ < 32.0f) {
			balloonLevel_ += 0.4f;
		}

	} else {
		if (balloonLevel_ > 0.0f) {
			balloonLevel_ -= 0.8f;
		}
	}

	//膨張に合わせた風船のサイズ変更
	size_ = { 10.0f + (balloonLevel_ * 2.0f),10.0f + (balloonLevel_ * 2.0f) };

	//風船の体積を求める
	volume_ = (4.0f/3.0f) * float(M_PI) * powf(size_.x * 0.5f,3.0f);

	//密度を計算
	weight_ = 0.5f + (volume_ * 0.001f);
	
	//============================上下方向の移動量の決定====================================
	velocity_.y += -CalcSinkSpeed(weight_, volume_ * 0.0012f, 0.8f);

	//============================左右方向の移動量の決定====================================
	if (keys[DIK_LEFT]) {

		if (easeT_ < 1.0f) {
			easeT_ += 0.03125f;
		}

		velocity_.x = -EaseInSine(easeT_) * speed_;

	} else {

		if (!keys[DIK_RIGHT]) {
			easeT_ = 0.0f;
		}
	}

	if (keys[DIK_RIGHT]) {

		if (easeT_ < 1.0f) {
			easeT_ += 0.03125f;
		}
		velocity_.x = EaseInSine(easeT_) * speed_;

	} else {

		if (!keys[DIK_LEFT]) {
			easeT_ = 0.0f;
		}
	}

	//スピードの減衰
	velocity_.x *= 0.98f;

	pos_.y += velocity_.y - (airResistance_ * velocity_.y);
	pos_.x += velocity_.x;

	Novice::ScreenPrintf(100, 100, "%d",Novice::CheckHitKey(keys[DIK_RIGHT]));

	//移動制限の壁
	if (pos_.y < 0.0f + size_.y) {
		pos_.y = 0.0f + size_.y;
		//
		velocity_.y *= (-(balloonLevel_/32.0f) * 0.6f);
	}

	//カメラ座標の計算
	*cameraPosX = int(pos_.x) - 640;
	if (*cameraPosX < 0) {
		*cameraPosX = 0;
	}

	*cameraPosY = int(pos_.y) - 360;
	if (*cameraPosY < 0) {
		*cameraPosY = 0;
	}
}



//ドロー
void Player::Draw(GlobalVariable globalV) {

	Novice::DrawEllipse(
		int(pos_.x) - globalV.GetCameraPosX(),
		int(pos_.y * -1.0f) + globalV.GetGroundPos() + globalV.GetCameraPosY(),
		int(size_.x),
		int(size_.y),
		0.0f,
		color_,
		kFillModeSolid
	);

	
	Novice::ScreenPrintf(20, 80, "%f", volume_);
}