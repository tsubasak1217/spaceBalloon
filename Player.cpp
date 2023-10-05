#include "Player.h"

// アップデート
void Player::Update(char* keys, char* preKeys, int* cameraPosX, int* cameraPosY, Map map) {

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
	volume_ = (4.0f / 3.0f) * float(M_PI) * powf(size_.x * 0.5f, 3.0f);

	//密度を計算
	weight_ = 0.5f + (volume_ * 0.00095f);

	//============================上下方向の移動量の決定====================================
	velocity_.y += -CalcSinkSpeed(weight_, volume_ * 0.0012f, 0.8f);

	//============================左右方向の移動量の決定====================================
	if (keys[DIK_LEFT]) {

		if (easeT_ < 1.0f) {
			easeT_ += 0.03125f;
		}

		velocity_.x = -EaseInSine(easeT_) * speed_;

		if (keys[DIK_RIGHT] && !preKeys[DIK_RIGHT]) {
			easeT_ = 0.0f;
		}

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

		if (keys[DIK_LEFT] && !preKeys[DIK_LEFT]) {
			easeT_ = 0.0f;
		}

	} else {

		if (!keys[DIK_LEFT]) {
			easeT_ = 0.0f;
		}
	}

	//スピードの減衰
	velocity_.x *= 0.98f;

	pos_.y += velocity_.y - (airResistance_ * velocity_.y);
	pos_.x += velocity_.x;

	//==================================移動制限の壁====================================

	//下
	if (pos_.y < 0.0f + size_.y) {
		pos_.y = 0.0f + size_.y;
		//
		velocity_.y *= (-(balloonLevel_ / 32.0f) * 0.6f);
	}

	//上
	if (pos_.y > (64.0f * 240.0f) - size_.y) {
		pos_.y = (64.0f * 240.0f) - size_.y;

		velocity_.y *= (-(balloonLevel_ / 32.0f) * 0.6f);
	}

	//左
	if (pos_.x < 0.0f + size_.y) {
		pos_.x = 0.0f + size_.y;
		//
		velocity_.x *= (-(balloonLevel_ / 32.0f) * 0.6f);
	}

	//上
	if (pos_.x > (64.0f * 40.0f) - size_.x) {
		pos_.x = (64.0f * 40.0f) - size_.x;

		velocity_.x *= (-(balloonLevel_ / 32.0f) * 0.6f);
	}


	//====================================================================
	//						ブロックとの当たり判定
	//====================================================================
	address_ = { int(pos_.x) / 64,int(pos_.y) / 64 };

	Novice::ScreenPrintf(100, 100, "%d,%d", address_.x, address_.y);

	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {

			if (address_.x + i >= 0 && address_.x + i <= 39) {
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
							pos_.y = map.GetPos(address_.y + i, address_.x + j).y + size_.x;
							//ベロシティを反転、反射係数分を減衰
							velocity_.y *= -1.0f * 0.6f;
							
							break;

						case 2://風船がブロックの右面に当たった時

							//座標を押し戻して
							pos_.x = map.GetPos(address_.y + i, address_.x + j).x + map.GetSize().x + size_.x;
							//ベロシティを反転、反射係数分を減衰
							velocity_.x *= -1.0f * 0.6f;

							break;

						case 3://風船がブロックの下面に当たった時

							//座標を押し戻して
							pos_.y = map.GetPos(address_.y + i, address_.x + j).y - map.GetSize().y - size_.y;
							//ベロシティを反転、反射係数分を減衰
							velocity_.y *= -1.0f * 0.6f;

							break;

						case 4://風船がブロックの左面に当たった時

							//座標を押し戻して
							pos_.x = map.GetPos(address_.y + i, address_.x + j).x - size_.x;
							//ベロシティを反転、反射係数分を減衰
							velocity_.x *= -1.0f * 0.6f;

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