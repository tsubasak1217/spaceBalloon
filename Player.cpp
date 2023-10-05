#include "Player.h"

// アップデート
void Player::Update(char* keys,int* cameraPos) {

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
	
	//上下方向の蚊測量
	velocity_.y += -CalcSinkSpeed(weight_, volume_ * 0.0012f, 0.8f);

	pos_.y += velocity_.y - (airResistance_ * velocity_.y);


	//移動制限の壁
	if (pos_.y < 0.0f + size_.y) {
		pos_.y = 0.0f + size_.y;
		//
		velocity_.y *= (-(balloonLevel_/32.0f) * 0.6f);
	}

	//カメラ座標の計算
	*cameraPos = int(pos_.y) - 360;
	if (*cameraPos < 0) {
		*cameraPos = 0;
	}
}



//ドロー
void Player::Draw(GlobalVariable globalV) {

	Novice::DrawEllipse(
		int(pos_.x),
		int(pos_.y * -1.0f) + globalV.GetGroundPos() + globalV.GetCameraPos(),
		int(size_.x),
		int(size_.y),
		0.0f,
		color_,
		kFillModeSolid
	);

	
	Novice::ScreenPrintf(20, 80, "%f", volume_);
}