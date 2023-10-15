#include "Player.h"

// アップデート
void Player::Update(
	char* keys, char* preKeys,
	int* cameraPosX,
	int* cameraPosY, int* miniCameraPos,
	Map& map, Scene scene, ChangeScene& changeScene
) {



	switch (scene.GetSceneNum()) {
		//=====================================================================================
		//                                      タイトル
		//=====================================================================================
	case title:

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
		if (pos_.y < 260.0f + size_.y) {
			pos_.y = 260.0f + size_.y;
			//
			velocity_.y *= -1.0f * 0.1f;
			hitDirection_ = 1;
			if (CheckBalloonLimit(hitDirection_, preHitDirection_)) {
				balloonLevel_ -= 0.4f;
			}
		}

		// 上にフレームアウトしたらシーン切り替え

		if (pos_.y >= 720.0f + 80.0f) {
			changeScene.SetIsFinish(true);
		}

		//シーン以降終了時に初期化命令を出す
		if (changeScene.GetFinishTimer() <= 1) {
			changeScene.SetInitOrder(true);
		}

		if (changeScene.GetInitOrder()) {
			Init(game);
		}

		break;

		//=====================================================================================
		//                                     ゲーム本編
		//=====================================================================================
	case game:

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

		if (!isAlive_) {
			map.SetResetBlockOrder(true);
			pos_ = respawnPos_;
			life_ = 1;
			isAlive_ = true;
		}

		// 風船が膨らんだりしぼんだりする処理

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

		//移動
		pos_.y += (velocity_.y + windSpeed_.y) - (airResistance_ * velocity_.y);
		pos_.x += (velocity_.x + windSpeed_.x);

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

		//============================風船の紐===================================

		ropePos_[0] = pos_;

		for (int i = 1; i < 32; i++) {

			//ループ強制退出用
			int roopCount = 0;

			//座標を求めるための変数
			float difX;
			float difY;
			float normalizeX;
			float normalizeY;
			float leng;

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

									if (life_ <= 0) {
										isAlive_ = false;
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

								//時間停止
								map.SetIsTimeStop(true);
								map.SetStopLimit(300);

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
								}

								Novice::ScreenPrintf(200, 20, "%d,%d", int(respawnPos_.y) / 64, int(respawnPos_.x) / 64);
								Novice::ScreenPrintf(200, 40, "%d,%d", address_.y + i, address_.x + j);

								//リスポーン地点の更新
								respawnPos_.x = map.GetPos(address_.y + i, address_.x + j).x + 32.0f;
								respawnPos_.y = map.GetPos(address_.y + i, address_.x + j).y - 32.0f;
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


		//風を受ける処理
		if (
			map.GetBlockType(int(address_.y), address_.x) >= 2 &&
			map.GetBlockType(address_.y, address_.x) <= 5) {//プレイヤーが風域にいるとき

			if (windT_ < 1.0f) {
				windT_ += 0.03125f;
			}

			switch (map.GetBlockType(address_.y, address_.x)) {

			case wind_up:
				windSpeed_.y = EaseInSine(windT_) * (speed_ * 2.0f);
				break;

			case wind_right:
				windSpeed_.x = EaseInSine(windT_) * (speed_ + 2.0f);
				break;

			case wind_down:
				windSpeed_.y = -EaseInSine(windT_) * (speed_ * 2.0f);
				break;

			case wind_left:
				windSpeed_.x = -EaseInSine(windT_) * (speed_ + 2.0f);
				break;
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

		//シーン以降終了時に初期化命令を出す
		if (changeScene.GetFinishTimer() <= 1) {
			changeScene.SetInitOrder(true);
		}

		if (changeScene.GetInitOrder()) {
			Init(clear);
		}

		break;

		//=====================================================================================
		//                                     クリア画面
		//=====================================================================================
	case clear:

		//シーン以降終了時に初期化命令を出す
		if (changeScene.GetFinishTimer() <= 1) {
			changeScene.SetInitOrder(true);
		}

		if (changeScene.GetInitOrder()) {
			Init(title);
		}
		break;

	default:
		break;
	}

}



//ドロー
void Player::Draw(GlobalVariable globalV, Scene scene) {

	switch (scene.GetSceneNum()) {
		//=====================================================================================
		//                                      タイトル
		//=====================================================================================
	case title:

		Novice::DrawEllipse(
			int(pos_.x),
			int(pos_.y * -1.0f) + globalV.GetGroundPos(),
			int(size_.x),
			int(size_.y),
			0.0f,
			color_,
			kFillModeSolid
		);

		break;

		//=====================================================================================
		//                                     ゲーム本編
		//=====================================================================================
	case game:

		if (!isUnrivaled_) {

			for (int i = 0; i < 32 - 1; i++) {
				Novice::DrawLine(
					int(ropePos_[i].x) - globalV.GetCameraPosX(),
					int(ropePos_[i].y * -1.0f) + globalV.GetGroundPos() + globalV.GetCameraPosY(),
					int(ropePos_[i + 1].x) - globalV.GetCameraPosX(),
					int(ropePos_[i + 1].y * -1.0f) + globalV.GetGroundPos() + globalV.GetCameraPosY(),
					0xffffffff
				);
			}

			Novice::DrawEllipse(
				int(pos_.x) - globalV.GetCameraPosX(),
				int(pos_.y * -1.0f) + globalV.GetGroundPos() + globalV.GetCameraPosY(),
				int(size_.x),
				int(size_.y),
				0.0f,
				color_,
				kFillModeSolid
			);

		} else {

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
			}
		}

		//ミニマップ用
		Novice::DrawEllipse(
			int(pos_.x / 17) + 1120,
			int((pos_.y / 17) * -1.0f) + 344 + int(globalV.GetMiniCameraPos() / 17),
			4,
			4,
			0.0f,
			color_,
			kFillModeSolid
		);

		Novice::DrawLine(//左上→右上
			int(pos_.x / 17) + 1120 - 38,
			int((pos_.y / 17) * -1.0f) + 344 + int(globalV.GetMiniCameraPos() / 17) - 21,
			int(pos_.x / 17) + 1120 + 38,
			int((pos_.y / 17) * -1.0f) + 344 + int(globalV.GetMiniCameraPos() / 17) - 21,
			RED
		);

		Novice::DrawLine(//左上→右上
			int(pos_.x / 17) + 1120 - 38,
			int((pos_.y / 17) * -1.0f) + 344 + int(globalV.GetMiniCameraPos() / 17) + 21,
			int(pos_.x / 17) + 1120 + 38,
			int((pos_.y / 17) * -1.0f) + 344 + int(globalV.GetMiniCameraPos() / 17) + 21,
			RED
		);

		Novice::DrawLine(//左上→右上
			int(pos_.x / 17) + 1120 - 38,
			int((pos_.y / 17) * -1.0f) + 344 + int(globalV.GetMiniCameraPos() / 17) + 21,
			int(pos_.x / 17) + 1120 - 38,
			int((pos_.y / 17) * -1.0f) + 344 + int(globalV.GetMiniCameraPos() / 17) - 21,
			RED
		);

		Novice::DrawLine(//左上→右上
			int(pos_.x / 17) + 1120 + 38,
			int((pos_.y / 17) * -1.0f) + 344 + int(globalV.GetMiniCameraPos() / 17) + 21,
			int(pos_.x / 17) + 1120 + 38,
			int((pos_.y / 17) * -1.0f) + 344 + int(globalV.GetMiniCameraPos() / 17) - 21,
			RED
		);



		//残機
		for (int i = 0; i < GetLife(); i++) {
			Novice::DrawEllipse(
				20 + i * 20,
				20,
				10,
				10,
				0.0f,
				color_,
				kFillModeSolid
			);
		}

		if (isAlive_) {
			Novice::ScreenPrintf(20, 40, "Alive");
		} else {
			Novice::ScreenPrintf(20, 40, "Dead");
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