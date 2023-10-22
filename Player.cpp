#include "Player.h"

// アップデート
void Player::Update(
	char* keys, char* preKeys,
	int* cameraPosX,
	int* cameraPosY, int* miniCameraPos,
	Map& map, Scene scene, ChangeScene& changeScene,
	GlobalVariable globalV
) {
	//unsigned int currentTime = unsigned int(time(nullptr));
	//srand(currentTime);

	switch (scene.GetSceneNum()) {
		//=====================================================================================
		//                                      タイトル
		//=====================================================================================
	case titleScene:

		//カメラ座標を0に
		globalV.SetCameraPosX(0);
		globalV.SetCameraPosY(0);

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

		//膨張に合わせた風船のサイズ変更
		size_ = { 12.0f + (balloonLevel_ * 2.0f),12.0f + (balloonLevel_ * 2.0f) };

		//風船の体積を求める
		volume_ = (4.0f / 3.0f) * float(M_PI) * powf(size_.x * 0.5f, 3.0f);

		//密度を計算
		weight_ = 0.5f + (volume_ * 0.001f);

		//============================上下方向の移動量の決定====================================
		velocity_.y += -CalcSinkSpeed(weight_, volume_ * 0.0012f, 0.6f);

		//スピードの減衰
		velocity_.x *= 0.98f;
		windSpeed_.x *= 0.95f;
		windSpeed_.y *= 0.95f;

		//移動
		if (!changeScene.GetIsFinish()) {
			pos_.y += (velocity_.y + windSpeed_.y) - (airResistance_ * velocity_.y);
			pos_.x += (velocity_.x + windSpeed_.x);
		}
		//==================================移動制限の壁====================================

		//下
		if (pos_.y < 340.0f + size_.y) {
			pos_.y = 340.0f + size_.y;
			//
			velocity_.y *= -1.0f * 0.1f;
			hitDirection_ = 1;
			if (CheckBalloonLimit(hitDirection_, preHitDirection_)) {
				balloonLevel_ -= 0.4f;
			}
		}

		// 上にフレームアウトしたらシーン切り替え

		if (pos_.y >= 720.0f + 80.0f + 360) {
			changeScene.SetIsFinish(true);
		}

		//============================風船の紐===================================

		ropePos_[0] = pos_;

		for (int i = 1; i < 32; i++) {

			//ループ強制退出用
			int roopCount = 0;

			//座標を求めるための変数
			float difX = 0;
			float difY = 0;
			float normalizeX = 0;
			float normalizeY = 0;
			float leng = 0;

			//下が空いていれば紐が落ちていくようにする
			if (int(ropePos_[i].y / 64.0f) - 1 >= 0 && int(ropePos_[i].y / 64.0f) < 240) {
				if (int(ropePos_[i].x / 64.0f) >= 0 && int(ropePos_[i].x / 64.0f) < 40) {

					if (map.GetBlockType(int(ropePos_[i].y / 64.0f) - 1, int(ropePos_[i].x / 64.0f)) == 1) {

						if (!IsHitBox_BallDirection(
							{ map.GetPos(int(ropePos_[i].y / 64.0f) - 1, int(ropePos_[i].x / 64.0f)).x + 32,
							map.GetPos(int(ropePos_[i].y / 64.0f) - 1, int(ropePos_[i].x / 64.0f)).y - 32 },
							{ ropePos_[i].x,ropePos_[i].y },
							map.GetSize(),
							2
						)) {

							difX = ropePos_[i].x - ropePos_[i - 1].x;
							difY = ropePos_[i].y - 1 - ropePos_[i - 1].y;

						} else {
							difX = ropePos_[i].x - ropePos_[i - 1].x;
							difY = ropePos_[i].y - ropePos_[i - 1].y;
						}
					} else if (map.GetBlockType(int(ropePos_[i].y / 64.0f), int(ropePos_[i].x / 64.0f)) == 1) {

						difX = ropePos_[i].x - ropePos_[i - 1].x;
						difY = ropePos_[i].y - ropePos_[i - 1].y;

					} else {
						difX = ropePos_[i].x - ropePos_[i - 1].x;
						difY = ropePos_[i].y - 1 - ropePos_[i - 1].y;
					}
				}

			} else if (int(ropePos_[i].y / 64.0f) - 1 < 0) {
				difX = ropePos_[i].x - ropePos_[i - 1].x;
				difY = ropePos_[i].y - 1 - ropePos_[i - 1].y;
			}

			leng = CheckLength(ropePos_[i], ropePos_[i - 1]);

			if (leng != 0) {

				normalizeX = difX / leng;
				normalizeY = difY / leng;

				ropePos_[i].x = ropePos_[i - 1].x + (normalizeX * ropeLength_);
				ropePos_[i].y = ropePos_[i - 1].y + (normalizeY * ropeLength_);
			}


			//更新後の座標がブロックに当たっていたら、当たらなくなるまで押し戻す
			while (true) {

				if (int(ropePos_[i].y / 64.0f) >= 0 && int(ropePos_[i].y / 64.0f) < 240) {
					if (int(ropePos_[i].x / 64.0f) >= 0 && int(ropePos_[i].x / 64.0f) < 40) {
						if (map.GetBlockType(int(ropePos_[i].y / 64.0f), int(ropePos_[i].x / 64.0f)) == 1) {

							difY = (ropePos_[i].y + 4) - ropePos_[i - 1].y;
							leng = CheckLength({ ropePos_[i].x,ropePos_[i].y + 4 }, ropePos_[i - 1]);

							normalizeX = difX / leng;
							normalizeY = difY / leng;

							ropePos_[i].x = ropePos_[i - 1].x + (normalizeX * ropeLength_);
							ropePos_[i].y = ropePos_[i - 1].y + (normalizeY * ropeLength_);

						} else {
							break;
						}
					} else {
						break;
					}
				} else {
					break;
				}

				roopCount++;

				//32ループで強制退出
				if (roopCount > 32) {
					break;
				}
			}
		}


		//シーン以降終了時に初期化命令を出す
		if (changeScene.GetFinishTimer() <= 1) {
			Init(game, map);
		}

		break;

		//=====================================================================================
		//                                     ゲーム本編
		//=====================================================================================
	case game:

		if (!changeScene.GetIsFinish()) {

			//無敵時間、フラグの更新,時間停止カウントの更新
			if (unrivaledLimit_ > 0) {
				unrivaledLimit_--;

				if (unrivaledLimit_ == 0) {
					isUnrivaled_ = false;
				}
			}

			//自爆リトライ処理
			if (holdLimit_ == 0) {
				life_ = 0;
				isAlive_ = false;
			}

			//死んだときの処理==============================================
			if (!isAlive_) {

				//死亡エフェクトに関する処理--------------
				if (retryTimeCount_ == 100) {

					for (int i = 0; i < 24; i++) {
						triangleTheta_[i] = float(rand());
					}

					savePos_.x = pos_.x - globalV.GetCameraPosX();
					savePos_.y = pos_.y - globalV.GetCameraPosY();

					//破裂音出す
					Novice::PlayAudio(playerSE[8], false, 0.3f);
				}

				triangleEaseT_ += 0.025f;
				if (triangleEaseT_ > 1.0f) {
					triangleEaseT_ = 1.0f;
				}

				for (int i = 0; i < 24; i++) {
					triangleCenter_[i].x = savePos_.x + cosf((triangleTheta_[i] / 256) * float(M_PI)) * (EaseOutExpo(triangleEaseT_) * float(int(triangleTheta_[i]) % int(efectRadius_)));
					triangleCenter_[i].y = savePos_.y + sinf((triangleTheta_[i] / 256) * float(M_PI)) * (EaseOutExpo(triangleEaseT_) * float(int(triangleTheta_[i]) % int(efectRadius_)));
				}


				//リトライ処理-------------------------
				retryTimeCount_--;
				changeScene.SetMoveMode(1);

				if (retryTimeCount_ <= 80) {
					changeScene.SetIsMoveStar(true);

					if (retryTimeCount_ <= 0) {
						changeScene.SetMoveMode(0);
						map.SetResetBlockOrder(true);
						pos_ = respawnPos_;
						velocity_ = { 0.0f,0.0f };
						isAccelable_ = false;
						isDash_ = false;
						life_ = 1;
						scoreCount_ = savedScoreCount_;
						retryTimeCount_ = 100;
						triangleEaseT_ = 0.0f;
						isAlive_ = true;
						for (int i = 0; i < 24; i++) {
							triangleCenter_[i] = { -100.0f,0.0f };
						}
					}
				}
			}

			//加速のフラグに関する処理==========================================


			if (isCountStart_) {

				doublePushLimit_--;

				//ダッシュフラグを立てる
				if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
					isDash_ = true;
					doublePushLimit_ = 0;
					isAccelable_ = false;

					//ダッシュする方向の決定
					if (keys[DIK_D] or keys[DIK_RIGHT]) {
						dashDirection_ = Right;

					} else if (keys[DIK_A] or keys[DIK_LEFT]) {
						dashDirection_ = Left;

					} else if (keys[DIK_S] or keys[DIK_DOWN]) {
						dashDirection_ = Down;
					} else {
						dashDirection_ = Up;
					}

				}

				//二回押ししなかったとき、処理を終える
				if (doublePushLimit_ <= 0) {
					isCountStart_ = false;
					doublePushLimit_ = 16;
				}
			}

			if (keys[DIK_SPACE]) {

				if (isAccelable_) {

					if (!preKeys[DIK_SPACE]) {
						isCountStart_ = true;
					}
				}
			}

			if (isDash_) {
				dashLimit_--;
				if (dashLimit_ <= 0) {
					isDash_ = false;
					dashLimit_ = 300;
				}
			}

			// 風船が膨らんだりしぼんだりする処理=================================================

			if (unrivaledLimit_ < 100) {

				if (keys[DIK_SPACE]) {

					if (!((preHitDirection_ == 1 && hitDirection_ == 3) or (preHitDirection_ == 3 && hitDirection_ == 1)) &&
						!((preHitDirection_ == 2 && hitDirection_ == 4) or (preHitDirection_ == 4 && hitDirection_ == 2))) {

						if (balloonLevel_ < 32.0f) {
							balloonLevel_ += 0.4f;
						}
					}

					//自爆の制限時間を減らす(リトライ用)
					holdLimit_--;



				} else {
					if (balloonLevel_ > 0.0f) {
						balloonLevel_ -= 0.8f;
					}

					//自爆の制限時間を戻す(リトライ用)
					holdLimit_ = 300;
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
			weight_ = 0.5f + (volume_ * 0.001f);

			//============================上下方向の移動量の決定====================================
			velocity_.y += -CalcSinkSpeed(weight_, volume_ * 0.0012f, 0.6f);

			//============================左右方向の移動量の決定====================================

			if (unrivaledLimit_ < 100) {

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
			windSpeed_.x *= 0.95f;
			windSpeed_.y *= 0.95f;

			//ダッシュしている際はその方向にのみ進む
			if (isDash_) {
				switch (dashDirection_) {
				case Up:
					velocity_.y = 12.0f;
					windSpeed_.y = 0.0f;
					velocity_.x = 0.0f;
					windSpeed_.x = 0.0f;
					break;

				case Right:
					velocity_.y = 0.0f;
					windSpeed_.y = 0.0f;
					velocity_.x = 12.0f;
					windSpeed_.x = 0.0f;
					break;

				case Left:
					velocity_.y = 0.0f;
					windSpeed_.y = 0.0f;
					velocity_.x = -12.0f;
					windSpeed_.x = 0.0f;
					break;

				case Down:
					velocity_.y = -12.0f;
					windSpeed_.y = 0.0f;
					velocity_.x = 0.0f;
					windSpeed_.x = 0.0f;
					break;

				default:
					break;
				}
			}


			//移動
			pos_.y += (velocity_.y + windSpeed_.y) - (airResistance_ * velocity_.y);
			pos_.x += (velocity_.x + windSpeed_.x);

			//==================================移動制限の壁====================================

			//左
			if (pos_.x < 0.0f + size_.y) {
				pos_.x = 0.0f + size_.y;
				//
				velocity_.x *= -1.0f * 0.6f;
				knockBackCount_ = int(sqrtf(powf(velocity_.x, 2.0f))) * 8;
				hitDirection_ = 4;
				isDash_ = false;
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
				isDash_ = false;
				if (CheckBalloonLimit(hitDirection_, preHitDirection_)) {
					balloonLevel_ -= 0.4f;
				}
			}

			//======================上にフレームアウトしたらクリアフラグを立てる=========================

			if (pos_.y > 64 * 244) {
				changeScene.SetIsFinish(true);
				map.SetScore(scoreCount_);
			}

			if (pos_.y < -64.0f) {
				changeScene.SetIsReturnTitle(true);
			}

			//============================風船の紐===================================

			ropePos_[0] = pos_;

			for (int i = 1; i < 32; i++) {

				//ループ強制退出用
				int roopCount = 0;

				//座標を求めるための変数
				float difX = 0;
				float difY = 0;
				float normalizeX = 0;
				float normalizeY = 0;
				float leng = 0;

				//下が空いていれば紐が落ちていくようにする
				if (int(ropePos_[i].y / 64.0f) - 1 >= 0 && int(ropePos_[i].y / 64.0f) < 240) {
					if (int(ropePos_[i].x / 64.0f) >= 0 && int(ropePos_[i].x / 64.0f) < 40) {

						if (map.GetBlockType(int(ropePos_[i].y / 64.0f) - 1, int(ropePos_[i].x / 64.0f)) == 1) {

							if (!IsHitBox_BallDirection(
								{ map.GetPos(int(ropePos_[i].y / 64.0f) - 1, int(ropePos_[i].x / 64.0f)).x + 32,
								map.GetPos(int(ropePos_[i].y / 64.0f) - 1, int(ropePos_[i].x / 64.0f)).y - 32 },
								{ ropePos_[i].x,ropePos_[i].y },
								map.GetSize(),
								2
							)) {

								difX = ropePos_[i].x - ropePos_[i - 1].x;
								difY = ropePos_[i].y - 1 - ropePos_[i - 1].y;

							} else {
								difX = ropePos_[i].x - ropePos_[i - 1].x;
								difY = ropePos_[i].y - ropePos_[i - 1].y;
							}
						} else if (map.GetBlockType(int(ropePos_[i].y / 64.0f), int(ropePos_[i].x / 64.0f)) == 1) {

							difX = ropePos_[i].x - ropePos_[i - 1].x;
							difY = ropePos_[i].y - ropePos_[i - 1].y;

						} else {
							difX = ropePos_[i].x - ropePos_[i - 1].x;
							difY = ropePos_[i].y - 1 - ropePos_[i - 1].y;
						}
					}

				} else if (int(ropePos_[i].y / 64.0f) - 1 < 0) {
					difX = ropePos_[i].x - ropePos_[i - 1].x;
					difY = ropePos_[i].y - 1 - ropePos_[i - 1].y;
				}

				leng = CheckLength(ropePos_[i], ropePos_[i - 1]);

				if (leng != 0) {

					normalizeX = difX / leng;
					normalizeY = difY / leng;

					ropePos_[i].x = ropePos_[i - 1].x + (normalizeX * ropeLength_);
					ropePos_[i].y = ropePos_[i - 1].y + (normalizeY * ropeLength_);
				}


				//更新後の座標がブロックに当たっていたら、当たらなくなるまで押し戻す
				while (true) {

					if (int(ropePos_[i].y / 64.0f) >= 0 && int(ropePos_[i].y / 64.0f) < 240) {
						if (int(ropePos_[i].x / 64.0f) >= 0 && int(ropePos_[i].x / 64.0f) < 40) {
							if (map.GetBlockType(int(ropePos_[i].y / 64.0f), int(ropePos_[i].x / 64.0f)) == 1) {

								difY = (ropePos_[i].y + 4) - ropePos_[i - 1].y;
								leng = CheckLength({ ropePos_[i].x,ropePos_[i].y + 4 }, ropePos_[i - 1]);

								normalizeX = difX / leng;
								normalizeY = difY / leng;

								ropePos_[i].x = ropePos_[i - 1].x + (normalizeX * ropeLength_);
								ropePos_[i].y = ropePos_[i - 1].y + (normalizeY * ropeLength_);

							} else {
								break;
							}
						} else {
							break;
						}
					} else {
						break;
					}

					roopCount++;

					//32ループで強制退出
					if (roopCount > 32) {
						break;
					}
				}
			}

			//====================================================================
			//						ブロックとの当たり判定
			//====================================================================
			address_ = { int(pos_.x) / 64,int(pos_.y) / 64 };

			for (int i = -2; i < 3; i++) {
				for (int j = -2; j < 3; j++) {

					if (address_.x + j >= 0 && address_.x + j <= 39) {
						if (address_.y + i >= 0 && address_.y + i <= 239) {

							//通常ブロックとの当たり判定
							if (map.GetBlockType(address_.y + i, address_.x + j) == 1) {

								if (IsHitBox_BallDirection(
									{ map.GetPos(address_.y + i, address_.x + j).x + 32, map.GetPos(address_.y + i, address_.x + j).y - 32 },
									pos_,
									map.GetSize(),
									size_.x
								)) {

									isDash_ = false;

									if (sqrtf(powf(velocity_.x, 2)) + sqrtf(powf(velocity_.y, 2)) > 5.0f) {
										//ブロックに当たった時の音
										Novice::PlayAudio(playerSE[1], false, 0.2f);
									}
								}

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

								//雷雲との当たり判定=============================================================-
							} else if (map.GetBlockType(address_.y + i, address_.x + j) == 7) {

								if (!map.GetIsTimeStop()) {

									if (IsHitBox_BallDirection(
										{ map.GetPos(address_.y + i, address_.x + j).x + 32, map.GetPos(address_.y + i, address_.x + j).y - 32 },
										pos_,
										{ map.GetSize().x * 2, map.GetSize().y * 2 },
										size_.x
									)) {


										if (unrivaledLimit_ <= 0) {

											velocity_.x = 0.0f;
											if (velocity_.y >= 0.0f) {
												velocity_.y = 0.0f;
											} else {
												velocity_.y = 5.0f;
											}
											isUnrivaled_ = true;
											unrivaledLimit_ = 160;
											life_--;

											//感電音
											Novice::PlayAudio(playerSE[7], false, 0.3f);

											if (life_ <= 0) {
												isAlive_ = false;
											}
										}
									}
								}

								//スコアアイテムの取得判定===================================================
							} else if (map.GetBlockType(address_.y + i, address_.x + j) == 8) {

								if (IsHitBox_BallDirection(
									{ map.GetPos(address_.y + i, address_.x + j).x + 32, map.GetPos(address_.y + i, address_.x + j).y - 32 },
									pos_,
									map.GetSize(),
									size_.x
								)) {

									//スコア加算
									scoreCount_++;
									map.SetScore(scoreCount_);

									//取得音出す
									Novice::PlayAudio(playerSE[3], false, 0.3f);

									//取得済み(ブロックタイプを何もない0に変更)
									map.SetBlockType(address_.y + i, address_.x + j, 0);
								}


								//残機アイテムの取得判定====================================================
							} else if (map.GetBlockType(address_.y + i, address_.x + j) == 9) {

								if (IsHitBox_BallDirection(
									{ map.GetPos(address_.y + i, address_.x + j).x + 32, map.GetPos(address_.y + i, address_.x + j).y - 32 },
									pos_,
									map.GetSize(),
									size_.x
								)) {

									//スコア加算
									life_++;

									//取得音出す
									Novice::PlayAudio(playerSE[2], false, 0.3f);

									//取得済み(ブロックタイプを何もない0に変更)
									map.SetBlockType(address_.y + i, address_.x + j, 0);

								}

								//時間停止アイテムの取得判定===============================================
							} else if (map.GetBlockType(address_.y + i, address_.x + j) == 10) {

								if (IsHitBox_BallDirection(
									{ map.GetPos(address_.y + i, address_.x + j).x + 32, map.GetPos(address_.y + i, address_.x + j).y - 32 },
									pos_,
									map.GetSize(),
									size_.x
								)) {

									//まだ時間が止まっていないときのみ
									if (!map.GetIsTimeStop()) {
										//時間停止
										map.SetIsTimeStop(true);
										map.SetStopLimit(300);
									}

									//取得済み(ブロックタイプを何もない0に変更)
									//map.SetBlockType(address_.y + i, address_.x + j, 0);
								}

							} else if (map.GetBlockType(address_.y + i, address_.x + j) == 11) {

								if (IsHitBox_BallDirection(
									{ map.GetPos(address_.y + i, address_.x + j).x + 32, map.GetPos(address_.y + i, address_.x + j).y - 32 },
									pos_,
									map.GetSize(),
									size_.x
								)) {

									//加速可能にする							
									isAccelable_ = true;

									//取得音出す
									Novice::PlayAudio(playerSE[6], false, 0.3f);

									//取得済み(ブロックタイプを何もない0に変更)
									map.SetBlockType(address_.y + i, address_.x + j, 0);
								}

							} else if (map.GetBlockType(address_.y + i, address_.x + j) == 98) {

								if (IsHitBox_BallDirection(
									{ map.GetPos(address_.y + i, address_.x + j).x + 32, map.GetPos(address_.y + i, address_.x + j).y - 32 },
									pos_,
									map.GetSize(),
									size_.x
								)) {

									//マップファイルにブロックタイプの保存を命令する
									if ((int(respawnPos_.y) / 64 != address_.y + i) or (int(respawnPos_.x) / 64 != address_.x + j)) {
										map.SetSaveBlockOrder(true);

										//中継地点のセーブ音
										Novice::PlayAudio(playerSE[12], false, 0.3f);
									}

									//リスポーン地点の更新
									respawnPos_.x = map.GetPos(address_.y + i, address_.x + j).x + 32.0f;
									respawnPos_.y = map.GetPos(address_.y + i, address_.x + j).y - 32.0f;
									map.SetPlayerRespawnAddress(int(respawnPos_.y / map.GetSize().y), int(respawnPos_.x / map.GetSize().x));

									//スコアの保存
									savedScoreCount_ = scoreCount_;
								}
							}
						}
					}
				}

			}

			//====================================================================
			//						    鳥との当たり判定
			//====================================================================

			//鳥の数だけループ
			if (!map.GetIsTimeStop()) {
				for (int i = 0; i < map.GetBirdAddress().size(); i++) {

					//プレーヤーから半径2マス圏内にいるとき
					if (map.GetBirdAddress()[i].x >= address_.x - 2 &&
						map.GetBirdAddress()[i].x <= address_.x + 2) {
						if (map.GetBirdAddress()[i].y >= address_.y - 2 &&
							map.GetBirdAddress()[i].y <= address_.y + 2) {

							//当たり判定を行う
							if (IsHitBox_BallDirection(
								{ map.GetBirdPos()[i].x + 32, map.GetBirdPos()[i].y - 32 },
								pos_,
								map.GetSize(),
								size_.x
							)) {

								if (unrivaledLimit_ <= 0) {
									isUnrivaled_ = true;
									unrivaledLimit_ = 160;
									life_--;

									//鳥の鳴き声出す
									Novice::PlayAudio(playerSE[11], false, 0.2f);

									if (life_ <= 0) {
										isAlive_ = false;
									}
								}

							}

							switch (

								IsHitBox_BallDirection(
									{ map.GetBirdPos()[i].x + 32, map.GetBirdPos()[i].y - 32 },
									pos_,
									map.GetSize(),
									size_.x
								)) {



							case 1://風船がブロックの上面に当たった時

								//座標を押し戻して
								pos_.y = map.GetBirdPos()[i].y + size_.y;
								//ベロシティを反転、反射係数分を減衰
								velocity_.y = 15.0f;
								hitDirection_ = 1;
								if (CheckBalloonLimit(hitDirection_, preHitDirection_)) {
									balloonLevel_ -= 0.4f;
								}

								break;

							case 2://風船がブロックの右面に当たった時

								//座標を押し戻して
								pos_.x = map.GetBirdPos()[i].x + map.GetSize().x + size_.x;
								//ベロシティを反転、反射係数分を減衰
								velocity_.x = 10.0f;
								knockBackCount_ = int(sqrtf(powf(velocity_.x, 2.0f))) * 8;
								hitDirection_ = 2;
								if (CheckBalloonLimit(hitDirection_, preHitDirection_)) {
									balloonLevel_ -= 0.4f;
								}

								break;

							case 3://風船がブロックの下面に当たった時

								//座標を押し戻して
								pos_.y = map.GetBirdPos()[i].y - map.GetSize().y - size_.y;
								//ベロシティを反転、反射係数分を減衰
								velocity_.y = -10.0f;
								hitDirection_ = 3;
								if (CheckBalloonLimit(hitDirection_, preHitDirection_)) {
									balloonLevel_ -= 0.4f;
								}

								break;

							case 4://風船がブロックの左面に当たった時

								//座標を押し戻して
								pos_.x = map.GetBirdPos()[i].x - size_.x;
								//ベロシティを反転、反射係数分を減衰
								velocity_.x = -10.0f;
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


			//風を受ける処理

			if (address_.y >= 0 && address_.y < 240)
				if (!map.GetIsTimeStop()) {
					if (
						map.GetBlockType(int(address_.y), address_.x) >= 2 &&
						map.GetBlockType(address_.y, address_.x) <= 5) {//プレイヤーが風域にいるとき

						if (windT_ < 1.0f) {
							windT_ += 0.03125f;
						}

						switch (map.GetBlockType(address_.y, address_.x)) {

						case wind_up:
							if (velocity_.y < 0.0f) {
								velocity_.y += EaseInSine(windT_) * (sqrtf(powf(velocity_.y / 2, 2)));
							} else {
								windSpeed_.y = EaseInSine(windT_) * (speed_ + 2.0f);
							}
							break;

						case wind_right:
							windSpeed_.x = EaseInSine(windT_) * (speed_ + 2.0f);
							break;

						case wind_down:
							if (velocity_.y > 0.0f) {
								velocity_.y += -EaseInSine(windT_) * (sqrtf(powf(velocity_.y / 2, 2)));
							} else {
								windSpeed_.y = -EaseInSine(windT_) * (speed_ + 2.0f);
							}
							break;

						case wind_left:
							windSpeed_.x = -EaseInSine(windT_) * (speed_ + 2.0f);
							break;
						}

					} else {
						windT_ = 0.0f;

					}
				} else {
					windT_ = 0.0f;
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

			*miniCameraPos = int(pos_.y) - 2720;
			if (*miniCameraPos < 0) {
				*miniCameraPos = 0;
			} else if (*miniCameraPos > (64 * 240) - 5440) {
				*miniCameraPos = (64 * 240) - 5440;
			}

			//プレイヤーの座標によって表示する空の色を変える
			map.SetSkyColor(ChangeColor(0x40aebaff, 0x221e31ff, 239, float(address_.y)));
			if (map.GetIsTimeStop()) {
				map.SetSkyColor(GrayScale(map.GetSkyColor()));
			}

		} else {//=======================================クリア後のシーン遷移===========================================-
			//シーン以降終了時に初期化命令を出す
			if (changeScene.GetFinishTimer() <= 1) {
				Init(clear, map);
			}
		}

		if (changeScene.GetReturnTimer() == 1) {
			Init(titleScene, map);
		}

		break;

		//=====================================================================================
		//                                     クリア画面
		//=====================================================================================
	case clear:

		//シーン以降終了時に初期化命令を出す
		if (changeScene.GetFinishTimer() <= 1) {
			Init(titleScene, map);
		}


		break;

	default:
		break;
	}

}



//ドロー
void Player::Draw(GlobalVariable globalV, Scene scene, ChangeScene changeScene) {

	switch (scene.GetSceneNum()) {
		//=====================================================================================
		//                                      タイトル
		//=====================================================================================
	case titleScene:

		if (!changeScene.GetIsStart()) {
			//風船の紐
			Novice::DrawLine(
				int(pos_.x),
				int(pos_.y * -1.0f) + globalV.GetGroundPos(),
				int(pos_.x),
				int(pos_.y * -1.0f) + 360 + globalV.GetGroundPos(),
				0xffffffff
			);

			//プレイヤー
			Novice::DrawEllipse(
				int(pos_.x),
				int(pos_.y * -1.0f) + globalV.GetGroundPos(),
				int(size_.x),
				int(size_.y),
				0.0f,
				color_,
				kFillModeSolid
			);

			//プレイヤーの風船の光
			Novice::DrawEllipse(
				int(pos_.x - size_.x * 0.4f),
				int((pos_.y + size_.y * 0.4f) * -1.0f) + globalV.GetGroundPos(),
				int(size_.x * 0.3f),
				int(size_.y * 0.3f),
				0.1f,
				0xffffff1f,
				kFillModeSolid
			);

		} else {

			//風船の紐
			Novice::DrawLine(
				int(pos_.x),
				int(pos_.y * -1.0f) + 720 + globalV.GetGroundPos() + int(EaseOutQuint(changeScene.startEaseT_) * -720),
				int(pos_.x),
				int(pos_.y * -1.0f) + 360 + 720 + globalV.GetGroundPos() + int(EaseOutQuint(changeScene.startEaseT_) * -720),
				0xffffffff
			);

			//プレイヤー
			Novice::DrawEllipse(
				int(pos_.x),
				int((pos_.y * -1.0f) + 720 + globalV.GetGroundPos() + (EaseOutQuint(changeScene.startEaseT_) * -720)),
				int(size_.x),
				int(size_.y),
				0.0f,
				color_,
				kFillModeSolid
			);

			//プレイヤーの風船の光
			Novice::DrawEllipse(
				int(pos_.x - size_.x * 0.4f),
				int((pos_.y + size_.y * 0.4f) * -1.0f) + 720 + globalV.GetGroundPos() + int(EaseOutQuint(changeScene.startEaseT_) * -720),
				int(size_.x * 0.3f),
				int(size_.y * 0.3f),
				0.1f,
				0xffffff1f,
				kFillModeSolid
			);
		}

		break;

		//=====================================================================================
		//                                     ゲーム本編
		//=====================================================================================
	case game:

		if (!isUnrivaled_) {

			//加速できるときにエフェクトを出す
			if (isAccelable_) {

				for (int i = 0; i < 4; i++) {
					Novice::DrawEllipse(
						int(pos_.x) - globalV.GetCameraPosX(),
						int(pos_.y * -1.0f) + globalV.GetGroundPos() + globalV.GetCameraPosY(),
						int(size_.x + (size_.x * 0.8f) + (sinf((float(globalV.grandTimeCount_ + i * 32) / 128) * float(M_PI)) * size_.x * 0.8f)),
						int(size_.y + (size_.x * 0.8f) + (sinf((float(globalV.grandTimeCount_ + i * 32) / 128) * float(M_PI)) * size_.y * 0.8f)),
						0.0f,
						0xffb6c11F + int((sinf((float(globalV.grandTimeCount_ + i * 8) / 16) * float(M_PI)) * 0x1F)),
						kFillModeSolid
					);
				}
			}


			if (isAlive_) {
				if (changeScene.GetIsStart()) {

					//風船の紐
					for (int i = 0; i < 32 - 1; i++) {
						Novice::DrawLine(
							int(ropePos_[i].x) - globalV.GetCameraPosX(),
							int(ropePos_[i].y * -1.0f)
							+ globalV.GetGroundPos() + globalV.GetCameraPosY()
							+ int((EaseInQuint(1.0f - changeScene.easeT_) * -720)),
							int(ropePos_[i + 1].x) - globalV.GetCameraPosX(),
							int(ropePos_[i + 1].y * -1.0f)
							+ globalV.GetGroundPos() + globalV.GetCameraPosY()
							+ int((EaseInQuint(1.0f - changeScene.easeT_) * -720)),
							0xffffffff
						);
					}

					//プレイヤー
					Novice::DrawEllipse(
						int(pos_.x) - globalV.GetCameraPosX(),
						int(pos_.y * -1.0f)
						+ globalV.GetGroundPos() + globalV.GetCameraPosY()
						+ int((EaseInQuint(1.0f - changeScene.easeT_) * -720)),
						int(size_.x),
						int(size_.y),
						0.0f,
						color_,
						kFillModeSolid
					);

					//プレイヤーの風船の光
					Novice::DrawEllipse(
						int(pos_.x - size_.x * 0.4f) - globalV.GetCameraPosX(),
						int((pos_.y + size_.y * 0.4f) * -1.0f)
						+ globalV.GetGroundPos() + globalV.GetCameraPosY()
						+ int((EaseInQuint(1.0f - changeScene.easeT_) * -720)),
						int(size_.x * 0.3f),
						int(size_.y * 0.3f),
						0.1f,
						0xffffff1f,
						kFillModeSolid
					);
				} else {

					//風船の紐
					for (int i = 0; i < 32 - 1; i++) {
						Novice::DrawLine(
							int(ropePos_[i].x) - globalV.GetCameraPosX(),
							int(ropePos_[i].y * -1.0f)
							+ globalV.GetGroundPos() + globalV.GetCameraPosY(),
							int(ropePos_[i + 1].x) - globalV.GetCameraPosX(),
							int(ropePos_[i + 1].y * -1.0f)
							+ globalV.GetGroundPos() + globalV.GetCameraPosY(),
							0xffffffff
						);
					}

					//プレイヤー
					Novice::DrawEllipse(
						int(pos_.x) - globalV.GetCameraPosX(),
						int(pos_.y * -1.0f)
						+ globalV.GetGroundPos() + globalV.GetCameraPosY(),
						int(size_.x),
						int(size_.y),
						0.0f,
						color_,
						kFillModeSolid
					);

					//プレイヤーの風船の光
					Novice::DrawEllipse(
						int(pos_.x - size_.x * 0.4f) - globalV.GetCameraPosX(),
						int((pos_.y + size_.y * 0.4f) * -1.0f)
						+ globalV.GetGroundPos() + globalV.GetCameraPosY(),
						int(size_.x * 0.3f),
						int(size_.y * 0.3f),
						0.1f,
						0xffffff1f,
						kFillModeSolid
					);

				}
			}

		} else {//ダメージ受けた時の無敵時間===============================

			if (isAlive_) {

				for (int i = 0; i < 32 - 1; i++) {
					Novice::DrawLine(
						int(ropePos_[i].x) - globalV.GetCameraPosX(),
						int(ropePos_[i].y * -1.0f) + globalV.GetGroundPos() + globalV.GetCameraPosY(),
						int(ropePos_[i + 1].x) - globalV.GetCameraPosX(),
						int(ropePos_[i + 1].y * -1.0f) + globalV.GetGroundPos() + globalV.GetCameraPosY(),
						0xffffffff
					);
				}

				if (unrivaledLimit_ / 5 % 2 == 0) {
					Novice::DrawEllipse(
						int(pos_.x) - globalV.GetCameraPosX(),
						int(pos_.y * -1.0f) + globalV.GetGroundPos() + globalV.GetCameraPosY(),
						int(size_.x),
						int(size_.y),
						0.0f,
						color_,
						kFillModeSolid
					);

					//プレイヤーの風船の光
					Novice::DrawEllipse(
						int(pos_.x - size_.x * 0.4f) - globalV.GetCameraPosX(),
						int((pos_.y + size_.y * 0.4f) * -1.0f)
						+ globalV.GetGroundPos() + globalV.GetCameraPosY(),
						int(size_.x * 0.3f),
						int(size_.y * 0.3f),
						0.1f,
						0xffffff1f,
						kFillModeSolid
					);
				}
			}
		}
		

		//残機
		for (int i = 0; i < GetLife(); i++) {
			Novice::DrawEllipse(
				20 + i * 20,
				20,
				10,
				10,
				0.0f,
				color_ + int(EaseInQuint(changeScene.easeT_) * -0xff),
				kFillModeSolid
			);
		}

		//割れるまでのリミット表示
		if (holdLimit_ < 180) {
			if (isAlive_) {


			}
		}


		//死亡エフェクト
		if (!isAlive_) {
			for (int i = 0; i < 24; i++) {

				DrawTriangle(
					triangleCenter_[i],
					2.0f * i,
					((float(globalV.grandTimeCount_) / (8.0f * i))) * float(M_PI),
					color_
				);
			}
		}

		break;

		//=====================================================================================
		//                                     クリア画面
		//=====================================================================================
	case clear:
		break;

	default:
		break;
	}
}

void Player::DrawTutorial(GlobalVariable globalV) {

	if (isAccelable_) {

		//スペース二回押しの説明

		Novice::DrawBox(
			int(pos_.x - globalV.GetCameraPosX() - 122),
			int(pos_.y * -1.0f)
			+ globalV.GetGroundPos() + globalV.GetCameraPosY()
			+ int((size_.y * 0.5f) + 54),
			223 + 20,
			33 + 20,
			0.0f,
			0x0000005f + int(sinf((globalV.grandTimeCount_ / 64.0f) * float(M_PI)) * 0x3f),
			kFillModeSolid
		);

		Novice::DrawSprite(
			int(pos_.x - globalV.GetCameraPosX() - 112),
			int(pos_.y * -1.0f)
			+ globalV.GetGroundPos() + globalV.GetCameraPosY()
			+ int((size_.y * 0.5f) + 64),
			playerImg[0],
			1, 1,
			0.0f,
			0xffffffff
		);
	}
};

void Player::Sound(char* keys, char* preKeys, Scene scene, Map map) {

	bool isClose2Wind = false;
	bool isClose2Thunder = false;
	bool isClose2Bird = false;

	switch (scene.GetSceneNum()) {

	case titleScene:

		if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
			Novice::PlayAudio(playerSE[0], false, 0.2f);
		}
		break;

	case game:

		//浮上音
		if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
			Novice::PlayAudio(playerSE[0], false, 0.15f);
		}

		if (map.GetIsTimeStop()) {
			if (!Novice::IsPlayingAudio(SEHandle[9]) or SEHandle == 0) {
				SEHandle[9] = Novice::PlayAudio(playerSE[9], false, 0.2f);
			}
		} else {
			Novice::StopAudio(SEHandle[9]);
		}

		//雷雲の音
		if (!Novice::IsPlayingAudio(playerSE[5])) {
			SEHandle[5] = Novice::PlayAudio(playerSE[5], true, volume[5]);
			playerSE[5] = SEHandle[5];
		}

		//風音
		if (!Novice::IsPlayingAudio(playerSE[4])) {
			SEHandle[4] = Novice::PlayAudio(playerSE[4], true, volume[4]);
			playerSE[4] = SEHandle[4];
		}

		//羽ばたく音
		if (!Novice::IsPlayingAudio(playerSE[10])) {
			SEHandle[10] = Novice::PlayAudio(playerSE[10], true, volume[10]);
			playerSE[10] = SEHandle[10];
		}



		for (int i = -4; i < 5; i++) {
			for (int j = -4; j < 5; j++) {

				if (address_.x + j >= 0 && address_.x + j <= 39) {
					if (address_.y + i >= 0 && address_.y + i <= 239) {

						//通常ブロックとの当たり判定
						if (map.GetBlockType(address_.y + i, address_.x + j) == 1) {

							if (IsHitBox_BallDirection(
								{ map.GetPos(address_.y + i, address_.x + j).x + 32, map.GetPos(address_.y + i, address_.x + j).y - 32 },
								pos_,
								map.GetSize(),
								size_.x
							)) {

							}

						}

						if (map.GetBlockType(address_.y + i, address_.x + j) >= 2 &&
							map.GetBlockType(address_.y + i, address_.x + j) <= 5) {

							isClose2Wind = true;

							//雷雲=============================================================-
						} else if (map.GetBlockType(address_.y + i, address_.x + j) == 7) {

							//雷に接近した時
							isClose2Thunder = true;


							if (!map.GetIsTimeStop()) {

								if (IsHitBox_BallDirection(
									{ map.GetPos(address_.y + i, address_.x + j).x + 32, map.GetPos(address_.y + i, address_.x + j).y - 32 },
									pos_,
									{ map.GetSize().x * 2, map.GetSize().y * 2 },
									size_.x
								)) {
									//雷に当たった時の音

								}
							}

							//スコアアイテム===================================================
						} else if (map.GetBlockType(address_.y + i, address_.x + j) == 8) {

							if (IsHitBox_BallDirection(
								{ map.GetPos(address_.y + i, address_.x + j).x + 32, map.GetPos(address_.y + i, address_.x + j).y - 32 },
								pos_,
								map.GetSize(),
								size_.x
							)) {

								//スコア加算音
							}


							//残機アイテム====================================================
						} else if (map.GetBlockType(address_.y + i, address_.x + j) == 9) {

							if (IsHitBox_BallDirection(
								{ map.GetPos(address_.y + i, address_.x + j).x + 32, map.GetPos(address_.y + i, address_.x + j).y - 32 },
								pos_,
								map.GetSize(),
								size_.x
							)) {

								//1up音

							}

							//加速アイテム===============================================
						} else if (map.GetBlockType(address_.y + i, address_.x + j) == 11) {

							if (IsHitBox_BallDirection(
								{ map.GetPos(address_.y + i, address_.x + j).x + 32, map.GetPos(address_.y + i, address_.x + j).y - 32 },
								pos_,
								map.GetSize(),
								size_.x
							)) {

								//取得音
							}

							//中継地点
						} else if (map.GetBlockType(address_.y + i, address_.x + j) == 98) {

							if (IsHitBox_BallDirection(
								{ map.GetPos(address_.y + i, address_.x + j).x + 32, map.GetPos(address_.y + i, address_.x + j).y - 32 },
								pos_,
								map.GetSize(),
								size_.x
							)) {

								//セーブ音
							}
						}
					}
				}
			}
		}
		//鳥との距離で音を更新
		//鳥の数だけループ
		if (!map.GetIsTimeStop()) {
			for (int i = 0; i < map.GetBirdAddress().size(); i++) {

				//プレーヤーから半径4マス圏内にいるとき
				if (map.GetBirdAddress()[i].x >= address_.x - 4 &&
					map.GetBirdAddress()[i].x <= address_.x + 5) {
					if (map.GetBirdAddress()[i].y >= address_.y - 4 &&
						map.GetBirdAddress()[i].y <= address_.y + 5) {


						isClose2Bird = true;
					}
				}
			}
		}

		//風の音量更新
		if (isClose2Wind) {
			volume[4] += 0.004f;
			if (volume[4] > 0.2f) {
				volume[4] = 0.2f;
			}
		} else {
			volume[4] > 0.0f ? volume[4] -= 0.004f : false;
		}

		Novice::SetAudioVolume(playerSE[4], volume[4]);

		//雷の音量更新
		if (isClose2Thunder) {
			volume[5] += 0.008f;
			if (volume[5] > 0.4f) {
				volume[5] = 0.4f;
			}
		} else {
			volume[5] > 0.0f ? volume[5] -= 0.008f : false;
		}

		Novice::SetAudioVolume(playerSE[5], volume[5]);

		//鳥の音量更新
		if (isClose2Bird) {
			volume[10] += 0.016f;
			if (volume[10] > 0.8f) {
				volume[10] = 0.8f;
			}
		} else {
			volume[10] > 0.0f ? volume[10] -= 0.016f : false;
		}

		Novice::SetAudioVolume(playerSE[10], volume[10]);


		//時間が停止した場合
		if (map.GetIsTimeStop()) {

			Novice::PauseAudio(playerSE[4]);
			Novice::PauseAudio(playerSE[5]);
			Novice::PauseAudio(playerSE[10]);

		} else {
			Novice::ResumeAudio(playerSE[4]);
			Novice::ResumeAudio(playerSE[5]);
			Novice::ResumeAudio(playerSE[10]);
		}


		break;

	case clear:
		break;

	default:
		break;

	}
};