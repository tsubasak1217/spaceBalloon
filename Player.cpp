#include "Player.h"

// アップデート
void Player::Update(char* keys, char* preKeys, int* cameraPosX, int* cameraPosY, Map map) {


	// 風船が膨らんだりしぼんだりする処理
	

		if (keys[DIK_SPACE]) {
			if (!((preHitDirection_ == 1 && hitDirection_ == 3) or (preHitDirection_ == 3 && hitDirection_ == 1)) &&
				!((preHitDirection_ == 2 && hitDirection_ == 4) or (preHitDirection_ == 4 && hitDirection_ == 2))) {

				if (balloonLevel_ < 32.0f) {
					balloonLevel_ += 0.4f;
				}
			}

		} else {
			if (balloonLevel_ > 0.0f) {
				balloonLevel_ -= 0.8f;
			}
		}
	
		//下限、上限
		if (balloonLevel_ < 0.0f) {
			balloonLevel_ = 0.0f;
		}

		if (balloonLevel_ > 32.0f) {
			balloonLevel_ = 32.0f;
		}
	//
	preHitDirection_ = hitDirection_;
	hitDirection_ = 0;

	//膨張に合わせた風船のサイズ変更
	size_ = { 12.0f + (balloonLevel_ * 2.0f),12.0f + (balloonLevel_ * 2.0f) };

	//風船の体積を求める
	volume_ = (4.0f / 3.0f) * float(M_PI) * powf(size_.x * 0.5f, 3.0f);

	//密度を計算
	weight_ = 0.5f + (volume_ * 0.00095f);

	//============================上下方向の移動量の決定====================================
	velocity_.y += -CalcSinkSpeed(weight_, volume_ * 0.0012f, 0.8f);

	//============================左右方向の移動量の決定====================================
	if (keys[DIK_LEFT] or keys[DIK_A]) {

		if (knockBackCount_ <= 0) {

			if (easeT_ < 1.0f) {
				easeT_ += 0.03125f;
			}

			velocity_.x = -EaseInSine(easeT_) * speed_;
		} else {
			if (velocity_.x < 0) {
				velocity_.x = -EaseInSine(easeT_) * speed_;
			}
		}

		if ((keys[DIK_RIGHT] && !preKeys[DIK_RIGHT]) or (keys[DIK_D] && !preKeys[DIK_D])) {
			easeT_ = 0.0f;
		}

	} else {

		if (!keys[DIK_RIGHT] && !keys[DIK_D]) {
			easeT_ = 0.0f;
		}
	}

	if (keys[DIK_RIGHT] or keys[DIK_D]) {

		if (knockBackCount_ <= 0) {
			if (easeT_ < 1.0f) {
				easeT_ += 0.03125f;
			}
			velocity_.x = EaseInSine(easeT_) * speed_;
		} else {
			if (velocity_.x >= 0) {
				velocity_.x = EaseInSine(easeT_) * speed_;
			}
		}


		if ((keys[DIK_LEFT] && !preKeys[DIK_LEFT]) or (keys[DIK_A] && !preKeys[DIK_A])) {
			easeT_ = 0.0f;
		}

	} else {

		if (!keys[DIK_LEFT] && !keys[DIK_A]) {
			easeT_ = 0.0f;
		}
	}

	//ノックバックカウントのディクリメント
	if (knockBackCount_ > 0) {
		knockBackCount_--;

		if (knockBackCount_ == 1) {
			easeT_ = 0.0f;
		}
	}

	//スピードの減衰
	velocity_.x *= 0.98f;

	//移動
	pos_.y += velocity_.y - (airResistance_ * velocity_.y);
	pos_.x += velocity_.x;

	//==================================移動制限の壁====================================

	//下
	if (pos_.y < 0.0f + size_.y) {
		pos_.y = 0.0f + size_.y;
		//
		velocity_.y *= -1.0f * 0.6f;
		hitDirection_ = 1;
		if (CheckBalloonLimit(hitDirection_, preHitDirection_)) {
			balloonLevel_ -= 0.4f;
		}
	}

	//上
	if (pos_.y > (64.0f * 240.0f) - size_.y) {
		pos_.y = (64.0f * 240.0f) - size_.y;

		velocity_.y *= -1.0f * 0.6f;
		hitDirection_ = 3;
		if (CheckBalloonLimit(hitDirection_, preHitDirection_)) {
			balloonLevel_ -= 0.4f;
		}
	}

	//左
	if (pos_.x < 0.0f + size_.y) {
		pos_.x = 0.0f + size_.y;
		//
		velocity_.x *= -1.0f * 0.6f;
		knockBackCount_ = int(sqrtf(powf(velocity_.x, 2.0f))) * 8;
		hitDirection_ = 4;
		if (CheckBalloonLimit(hitDirection_, preHitDirection_)) {
			balloonLevel_ -= 0.4f;
		}
	}

	//右
	if (pos_.x > (64.0f * 40.0f) - size_.x) {
		pos_.x = (64.0f * 40.0f) - size_.x;

		velocity_.x *= -1.0f * 0.6f;
		knockBackCount_ = int(sqrtf(powf(velocity_.x, 2.0f))) * 8;
		hitDirection_ = 2;
		if (CheckBalloonLimit(hitDirection_, preHitDirection_)) {
			balloonLevel_ -= 0.4f;
		}
	}


	//====================================================================
	//						ブロックとの当たり判定
	//====================================================================
	address_ = { int(pos_.x) / 64,int(pos_.y) / 64 };

	Novice::ScreenPrintf(100, 100, "%f,%f", size_.x,size_.y);
	Novice::ScreenPrintf(100, 120, "%f", balloonLevel_);

	for (int i = -2; i < 3; i++) {
		for (int j = -2; j < 3; j++) {

			if (address_.x + j >= 0 && address_.x + j <= 39) {
				if (address_.y + i >= 0 && address_.y + i <= 239) {
					if (map.GetBlockType(address_.y + i, address_.x + j) == 1) {
						switch (

							IsHitBox_BallDirection(
								{ map.GetPos(address_.y + i, address_.x + j).x + 32, map.GetPos(address_.y + i, address_.x + j).y - 32 },
								pos_,
								map.GetSize(),
								size_.x
							)) {



						case 1://風船がブロックの上面に当たった時

							//座標を押し戻して
							pos_.y = map.GetPos(address_.y + i, address_.x + j).y + size_.y;
							//ベロシティを反転、反射係数分を減衰
							velocity_.y *= -1.0f * 0.6f;
							hitDirection_ = 1;
							if (CheckBalloonLimit(hitDirection_, preHitDirection_)) {
								balloonLevel_ -= 0.4f;
							}

							break;

						case 2://風船がブロックの右面に当たった時

							//座標を押し戻して
							pos_.x = map.GetPos(address_.y + i, address_.x + j).x + map.GetSize().x + size_.x;
							//ベロシティを反転、反射係数分を減衰
							velocity_.x *= -1.0f * 0.6f;
							knockBackCount_ = int(sqrtf(powf(velocity_.x, 2.0f))) * 8;
							hitDirection_ = 2;
							if (CheckBalloonLimit(hitDirection_, preHitDirection_)) {
								balloonLevel_ -= 0.4f;
							}

							break;

						case 3://風船がブロックの下面に当たった時

							//座標を押し戻して
							pos_.y = map.GetPos(address_.y + i, address_.x + j).y - map.GetSize().y - size_.y;
							//ベロシティを反転、反射係数分を減衰
							velocity_.y *= -1.0f * 0.6f;
							hitDirection_ = 3;
							if (CheckBalloonLimit(hitDirection_, preHitDirection_)) {
								balloonLevel_ -= 0.4f;
							}

							break;

						case 4://風船がブロックの左面に当たった時

							//座標を押し戻して
							pos_.x = map.GetPos(address_.y + i, address_.x + j).x - size_.x;
							//ベロシティを反転、反射係数分を減衰
							velocity_.x *= -1.0f * 0.6f;
							knockBackCount_ = int(sqrtf(powf(velocity_.x, 2.0f))) * 8;
							hitDirection_ = 4;
							if (CheckBalloonLimit(hitDirection_, preHitDirection_)) {
								balloonLevel_ -= 0.4f;
							}

							break;

						default://風船がブロックに当たっていない時
							break;
						}

					}
				}
			}
		}
	}


	//カメラ座標の計算
	*cameraPosX = int(pos_.x) - 640;
	if (*cameraPosX < 0) {
		*cameraPosX = 0;
	} else if (*cameraPosX > (64 * 40) - 1280) {
		*cameraPosX = (64 * 40) - 1280;
	}

	*cameraPosY = int(pos_.y) - 360;
	if (*cameraPosY < 0) {
		*cameraPosY = 0;
	} else if (*cameraPosY > (64 * 240) - 640) {
		*cameraPosY = (64 * 240) - 640;
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