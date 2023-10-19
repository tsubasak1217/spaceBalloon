#include "Map.h"


void Map::Init() {

	cloudPos_[0] = { 0.0f,0.0f };
	cloudPos_[1] = { 0.0f,0.0f };

	titleLogoPos_[0] = { 0.0f,0.0f };
	titleLogoPos_[1] = { 0.0f,0.0f };

	clearResultPos_[0] = { 255.0f,300.0f };
	clearResultPos_[1] = { 255.0f,380.0f };

	//スコアアイテムの総数をカウントするやつ
	allScoreItem_ = 0;
	achievement = 0;
	for (int i = 0; i < 3; i++) {
		scoreDigit[i] = 0;
	}
	//csvからマップを読み込み
	blockType_ = LoadFile("./Resources./spaceBalloon_map.csv");

	//行を反転
	std::reverse(blockType_.begin(), blockType_.end());

	//savedBlockType_(ブロックの保存配列)にコピー
	savedBlockType_.clear();
	savedBlockType_ = blockType_;

	//大きさ
	size_ = { 64.0f,64.0f };
	miniMapSize = 4.0f;

	//初期化
	birdAddress_.clear();
	birdDirection_.clear();
	birdPos_.clear();
	allScoreItem_ = 0;

	for (int row = 0; row < mapRow; row++) {
		for (int col = 0; col < mapCol; col++) {


			//ブロックの配置
			pos_[row][col].y = size_.y * (row + 1);
			pos_[row][col].x = size_.x * col;

			//スコアアイテムの総数をカウント
			if (blockType_[row][col] == 8) {
				allScoreItem_++;
			}

			//鳥の座標を格納していく
			if (blockType_[row][col] == 6) {
				birdPos_.push_back(pos_[row][col]);
			}

			//プレイヤーの初期座標
			if (blockType_[row][col] == 99) {
				firstPlayerPos_.x = (size_.x * col) + (size_.x * 0.5f);
				firstPlayerPos_.y = (size_.y * (row + 1)) - (size_.y * 0.5f);
			}
		}
	}


	for (int i = 0; i < birdPos_.size(); i++) {
		birdAddress_.push_back(
			{
			int((birdPos_[i].x + (size_.x / 2)) / size_.x),
			int((birdPos_[i].y - (size_.y / 2)) / size_.y)
			}
		);
	}

	for (int i = 0; i < birdAddress_.size(); i++) {
		//初期の方向代入
		if (blockType_[birdAddress_[i].y][birdAddress_[i].x + 1] == 66 or
			blockType_[birdAddress_[i].y][birdAddress_[i].x + 1] == 6) {

			birdDirection_.push_back(Right);

		} else if (blockType_[birdAddress_[i].y][birdAddress_[i].x - 1] == 66 or
			blockType_[birdAddress_[i].y][birdAddress_[i].x - 1] == 6) {

			birdDirection_.push_back(Left);

		} else if (blockType_[birdAddress_[i].y + 1][birdAddress_[i].x] == 66 or
			blockType_[birdAddress_[i].y + 1][birdAddress_[i].x] == 6) {

			birdDirection_.push_back(Up);

		} else if (blockType_[birdAddress_[i].y - 1][birdAddress_[i].x] == 66 or
			blockType_[birdAddress_[i].y - 1][birdAddress_[i].x] == 6) {

			birdDirection_.push_back(Down);
		}
	}

	isTimeStop_ = false;
	stopLimit_ = 0;

}

//==================================================================================
void Map::Update(Scene scene, ChangeScene changeScene) {

	switch (scene.GetSceneNum()) {
		//=====================================================================================
		//                                      タイトル
		//=====================================================================================
	case title:

		//タイトルロゴをふわふわさせる
		timeCount_++;
		theta_ = float(timeCount_) / 256.0f;

		//雲のスクロール
		cloudPos_[0].x += 2;
		cloudPos_[1].x += 1;

		for (int i = 0; i < 2; i++) {
			if (cloudPos_[i].x >= 1280) {
				cloudPos_[i].x = 0;
			}
		}

		if (changeScene.GetFinishTimer() <= 1) {
			Init();
		}

		break;

		//=====================================================================================
		//                                     ゲーム本編
		//=====================================================================================
	case game:

		//時間が停止してないときにタイマーを増やす
		if (!isTimeStop_) {
			timeCount_++;
		}

		//スコアの更新
		achievement = (float(score_) / float(allScoreItem_)) * 100;
		scoreDigit[0] = int(achievement) / 100;
		scoreDigit[1] = int(achievement) % 100 / 10;
		scoreDigit[2] = int(achievement) % 10 / 1;

		Novice::ScreenPrintf(100, 20, "%d", achievement);
		Novice::ScreenPrintf(100, 40, "%d", allScoreItem_);
		Novice::ScreenPrintf(100, 60, "%d", score_);

		//====================外部からの命令=====================

		//ブロックの保存命令があった時の処理
		if (saveBlockOrder_) {
			savedBlockType_ = blockType_;
			saveBlockOrder_ = false;
		}

		//ブロック番号の復元命令があった時の処理
		if (resetBlockOrder_) {
			blockType_ = savedBlockType_;
			resetBlockOrder_ = false;
		}

		//=====================自分の更新処理======================

		//時間停止カウントの更新
		if (stopLimit_ > 0) {
			stopLimit_--;

		} else {
			isTimeStop_ = false;
		}

		for (int i = 0; i < birdPos_.size(); i++) {

			if (!isTimeStop_) {
				//鳥の番地更新==================================================================
				birdAddress_[i] = {
					int((birdPos_[i].x + (size_.x / 2)) / size_.x),
					int((birdPos_[i].y - (size_.y / 2)) / size_.y)
				};

				//方向と座標の更新===============================================================
				switch (birdDirection_[i]) {
				case Right:
					if (birdAddress_[i].x + 1 < 40) {
						if (blockType_[birdAddress_[i].y][birdAddress_[i].x + 1] != 66 &&
							blockType_[birdAddress_[i].y][birdAddress_[i].x + 1] != 6) {
							if (blockType_[birdAddress_[i].y][birdAddress_[i].x - 1] == 66 or
								blockType_[birdAddress_[i].y][birdAddress_[i].x - 1] == 6) {

								birdDirection_[i] = Left;
							}
						}
					} else {
						birdDirection_[i] = Left;
					}

					birdPos_[i].x += 2.0f;

					break;

				case Left:
					if (birdAddress_[i].x - 1 >= 0) {
						if (blockType_[birdAddress_[i].y][birdAddress_[i].x - 1] != 66 &&
							blockType_[birdAddress_[i].y][birdAddress_[i].x - 1] != 6) {
							if (blockType_[birdAddress_[i].y][birdAddress_[i].x + 1] == 66 or
								blockType_[birdAddress_[i].y][birdAddress_[i].x + 1] == 6) {

								birdDirection_[i] = Right;
							}
						}
					} else {
						birdDirection_[i] = Right;
					}

					birdPos_[i].x -= 2.0f;

					break;

				case Up:
					if (birdAddress_[i].y + 1 < 240) {
						if (blockType_[birdAddress_[i].y + 1][birdAddress_[i].x] != 66 &&
							blockType_[birdAddress_[i].y + 1][birdAddress_[i].x] != 6) {
							if (blockType_[birdAddress_[i].y - 1][birdAddress_[i].x] == 66 or
								blockType_[birdAddress_[i].y - 1][birdAddress_[i].x] == 6) {

								birdDirection_[i] = Down;
							}
						}
					} else {
						birdDirection_[i] = Down;
					}

					birdPos_[i].y += 2.0f;

					break;

				case Down:
					if (birdAddress_[i].y - 1 >= 0) {
						if (blockType_[birdAddress_[i].y - 1][birdAddress_[i].x] != 66 &&
							blockType_[birdAddress_[i].y - 1][birdAddress_[i].x] != 6) {
							if (blockType_[birdAddress_[i].y + 1][birdAddress_[i].x] == 66 or
								blockType_[birdAddress_[i].y + 1][birdAddress_[i].x] == 6) {

								birdDirection_[i] = Up;
							}
						}
					} else {
						birdDirection_[i] = Up;
					}

					birdPos_[i].y -= 2.0f;

					break;

				default:
					break;
				}
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


//==========================================================================================================================

void Map::DrawBG() {
	//背景
	if (!isTimeStop_) {
		Novice::DrawBox(
			0, 0,
			1280,
			720,
			0.0f,
			skyColor_,
			kFillModeSolid
		);
	} else {
		Novice::DrawBox(
			0, 0,
			1280,
			720,
			0.0f,
			GrayScale(skyColor_),
			kFillModeSolid
		);
	}
}

void Map::Draw(GlobalVariable globalV, Scene scene, ChangeScene changeScene) {

	switch (scene.GetSceneNum()) {
		//=====================================================================================
		//                                      タイトル
		//=====================================================================================
	case title:

		//背景の空
		Novice::DrawSprite(
			0, int(0 + (EaseInQuint(changeScene.easeT_) * 720)),
			titleImgs_[0],
			1, 1,
			0.0f,
			WHITE
		);

		//スクロールする雲
		for (int i = 0; i < 2; i++) {

			Novice::DrawSprite(
				int(cloudPos_[i].x),
				int(cloudPos_[i].y + (EaseInQuint(changeScene.easeT_) * 720)),
				titleImgs_[i + 1],
				1, 1,
				0.0f,
				WHITE
			);

			Novice::DrawSprite(
				int(cloudPos_[i].x - 1280),
				int(cloudPos_[i].y + (EaseInQuint(changeScene.easeT_) * 720)),
				titleImgs_[i + 1],
				1, 1,
				0.0f,
				WHITE
			);

		}

		//タイトルロゴ================================
		Novice::DrawSprite(
			int(titleLogoPos_[0].x + 28),
			int(titleLogoPos_[0].y + (24.0f * sinf(theta_ * float(M_PI))) + (EaseInQuint(changeScene.easeT_) * 720)),
			titleImgs_[3],
			1, 1,
			0.0f,
			WHITE
		);

		Novice::DrawSprite(
			int(titleLogoPos_[1].x + 32),
			int(titleLogoPos_[1].y + (24.0f * sinf(-theta_ * float(M_PI))) + (EaseInQuint(changeScene.easeT_) * 720)),
			titleImgs_[4],
			1, 1,
			0.0f,
			WHITE
		);

		break;


		//=====================================================================================
		//                                     ゲーム本編
		//=====================================================================================
	case game:

		if (changeScene.GetIsStart()) {


			for (int row = 0; row < mapRow; row++) {
				for (int col = 0; col < mapCol; col++) {

					//ブロックの座標がスクリーン内のとき
					if (int(pos_[row][col].x) - globalV.GetCameraPosX() >= 0 - size_.x &&
						int(pos_[row][col].x) - globalV.GetCameraPosX() <= 1280) {
						if (int(pos_[row][col].y * -1.0f)
							+ globalV.GetGroundPos() + globalV.GetCameraPosY() + int((EaseInQuint(1.0f - changeScene.easeT_) * -720)) >= 0 - size_.y &&
							int(pos_[row][col].y * -1.0f)
							+ globalV.GetGroundPos() + globalV.GetCameraPosY() + int((EaseInQuint(1.0f - changeScene.easeT_) * -720)) <= 720) {

							if (!isTimeStop_) {
								switch (blockType_[row][col]) {

								case normal:
									//描画
									Novice::DrawSpriteRect(
										int(pos_[row][col].x) - globalV.GetCameraPosX() - 6,
										int(pos_[row][col].y * -1.0f)
										+ globalV.GetGroundPos() + globalV.GetCameraPosY()
										+ int((EaseInQuint(1.0f - changeScene.easeT_) * -720)) - 6,
										0 + (76 * (isTimeStop_)),
										0,
										76,
										76,
										gameImgs_[0],
										76.0f / 152.0f, 1,
										0.0f,
										0xffffffff
									);

									break;

								case thunder:

									//描画
									Novice::DrawSpriteRect(
										int(pos_[row][col].x) - globalV.GetCameraPosX() - 6,
										int(pos_[row][col].y * -1.0f)
										+ globalV.GetGroundPos() + globalV.GetCameraPosY()
										+ int((EaseInQuint(1.0f - changeScene.easeT_) * -720)) - 6,
										0 + (76 * (isTimeStop_)),
										0,
										76,
										76,
										gameImgs_[1],
										76.0f / 152.0f, 1,
										0.0f,
										0xffffffff
									);

									break;

								case score:

									//描画
									Novice::DrawSpriteRect(
										int(pos_[row][col].x) - globalV.GetCameraPosX(),
										int((pos_[row][col].y * -1.0f))
										+ globalV.GetGroundPos() + globalV.GetCameraPosY()
										+ int(sinf((globalV.grandTimeCount_ / 64.0f) * float(M_PI)) * 6.0f)
										+ int((EaseInQuint(1.0f - changeScene.easeT_) * -720)),
										0 + (64 * (globalV.grandTimeCount_ / 16 % 3)),
										0,
										64,
										64,
										gameImgs_[6],
										64.0f / 256.0f, 64.0f / 128.0f,
										0.0f,
										0xffffffff
									);

									break;

								case life:

									//描画
									Novice::DrawSpriteRect(
										int(pos_[row][col].x) - globalV.GetCameraPosX(),
										int((pos_[row][col].y * -1.0f))
										+ globalV.GetGroundPos() + globalV.GetCameraPosY()
										+ int(sinf((globalV.grandTimeCount_ / 64.0f) * float(M_PI)) * 6.0f)
										+ int((EaseInQuint(1.0f - changeScene.easeT_) * -720)),
										0 + (64 * (globalV.grandTimeCount_ / 16 % 3)),
										0,
										64,
										64,
										gameImgs_[5],
										64.0f / 256.0f, 64.0f / 128.0f,
										0.0f,
										0xffffffff
									);

									break;

								case clockItem:

									//描画
									Novice::DrawBox(
										int(pos_[row][col].x) - globalV.GetCameraPosX(),
										int(pos_[row][col].y * -1.0f)
										+ globalV.GetGroundPos() + globalV.GetCameraPosY()
										+ int((EaseInQuint(1.0f - changeScene.easeT_) * -720)),
										int(size_.x),
										int(size_.y),
										0.0f,
										0x000000ff,
										kFillModeSolid
									);

									break;

								case accel:

									//描画
									Novice::DrawBox(
										int(pos_[row][col].x) - globalV.GetCameraPosX(),
										int(pos_[row][col].y * -1.0f)
										+ globalV.GetGroundPos() + globalV.GetCameraPosY()
										+ int((EaseInQuint(1.0f - changeScene.easeT_) * -720)),
										int(size_.x),
										int(size_.y),
										0.0f,
										0xff8c00ff,
										kFillModeSolid
									);

									break;

								case savePoint:

									//描画
									Novice::DrawSpriteRect(
										int(pos_[row][col].x) - globalV.GetCameraPosX(),
										int(pos_[row][col].y * -1.0f)
										+ globalV.GetGroundPos() + globalV.GetCameraPosY()
										+ int((EaseInQuint(1.0f - changeScene.easeT_) * -720)),
										0 + (64 * (timeCount_ / 4 % 3)),
										0 + (128 * isTimeStop_),
										64,
										64,
										gameImgs_[3],
										64.0f / 256.0f, 64.0f / 256.0f,
										0.0f,
										0xffffffff
									);

									break;

								default:
									break;
								}


								//風域の描画
								if (blockType_[row][col] >= wind_up &&
									blockType_[row][col] <= wind_left) {

									//描画
									Novice::DrawSpriteRect(
										int(pos_[row][col].x) - globalV.GetCameraPosX(),
										int(pos_[row][col].y * -1.0f)
										+ globalV.GetGroundPos() + globalV.GetCameraPosY()
										+ int((EaseInQuint(1.0f - changeScene.easeT_) * -720)),
										0 + (32 * (timeCount_ / 2 % 7)),
										0 + (32 * ((blockType_[row][col]) - 2)),
										32,
										32,
										gameImgs_[2],
										64.0f / 256.0f, 64.0f / 128.0f,
										0.0f,
										0xffffff7f
									);
								}

							}
						}
					}

				}
			}


			//鳥の描画
			for (int i = 0; i < birdPos_.size(); i++) {
				if (int(birdPos_[i].x) - globalV.GetCameraPosX() >= 0 - size_.x &&
					int(birdPos_[i].x) - globalV.GetCameraPosX() <= 1280) {
					if (int(birdPos_[i].y * -1.0f) + globalV.GetGroundPos() + globalV.GetCameraPosY() >= 0 - size_.y &&
						int(birdPos_[i].y * -1.0f) + globalV.GetGroundPos() + globalV.GetCameraPosY() <= 720) {

						Novice::DrawSpriteRect(
							int(birdPos_[i].x) - globalV.GetCameraPosX(),
							int(birdPos_[i].y * -1.0f)
							+ globalV.GetGroundPos() + globalV.GetCameraPosY(),
							0 + (64 * (timeCount_ / 4 % 4)),
							(64 * (birdDirection_[i] % 2)) + (128 * isTimeStop_)
							+ int((EaseInQuint(1.0f - changeScene.easeT_) * -720)),
							64,
							64,
							gameImgs_[4],
							64.0f / 320.0f, 64.0f / 256.0f,
							0.0f,
							0xffffffff
						);



					}
				}

				//ミニマップ用
				Novice::DrawBox(
					int((birdPos_[i].x / 17) + 1120),
					int((birdPos_[i].y / 17) * -1.0f) + 344
					+ int(globalV.GetMiniCameraPos() / 17),
					int(miniMapSize),
					int(miniMapSize),
					0.0f,
					0xff0000ff,
					kFillModeSolid
				);
			}


			Novice::DrawBox(
				1120,
				24,
				150,
				320,
				0.0f,
				0x00000088,
				kFillModeSolid
			);

			//ミニマップの表示
			for (int row = 0; row < mapRow; row++) {
				for (int col = 0; col < mapCol; col++) {

					if (((pos_[row][col].y / 17) * -1.0f) + 344 + int(globalV.GetMiniCameraPos() / 17) >= 24 &&
						((pos_[row][col].y / 17) * -1.0f) + 344 + int(globalV.GetMiniCameraPos() / 17) <= 340) {
						switch (blockType_[row][col]) {

						case normal:
							//描画
							Novice::DrawBox(
								int((pos_[row][col].x / 17) + 1120),
								int((pos_[row][col].y / 17) * -1.0f) + 344
								+ int(globalV.GetMiniCameraPos() / 17),
								int(miniMapSize),
								int(miniMapSize),
								0.0f,
								0xf7efdfff,
								kFillModeSolid
							);

							break;

						case thunder:

							//描画
							Novice::DrawBox(
								int((pos_[row][col].x / 17) + 1120),
								int((pos_[row][col].y / 17) * -1.0f) + 344
								+ int(globalV.GetMiniCameraPos() / 17),
								int(miniMapSize),
								int(miniMapSize),
								0.0f,
								0x666666ff,
								kFillModeSolid
							);

							break;

						default:
							break;
						}
					}
				}
			}

		} else {
			//通常時============================================================================
			for (int row = 0; row < mapRow; row++) {
				for (int col = 0; col < mapCol; col++) {

					//ブロックの座標がスクリーン内のとき
					if (int(pos_[row][col].x) - globalV.GetCameraPosX() >= 0 - size_.x &&
						int(pos_[row][col].x) - globalV.GetCameraPosX() <= 1280) {
						if (int(pos_[row][col].y * -1.0f)
							+ globalV.GetGroundPos() + globalV.GetCameraPosY() >= 0 - size_.y &&
							int(pos_[row][col].y * -1.0f)
							+ globalV.GetGroundPos() + globalV.GetCameraPosY() <= 720) {


							switch (blockType_[row][col]) {

							case normal:
								//描画
								Novice::DrawSpriteRect(
									int(pos_[row][col].x) - globalV.GetCameraPosX() - 6,
									int(pos_[row][col].y * -1.0f) + globalV.GetGroundPos() + globalV.GetCameraPosY() - 6,
									0 + (76 * (isTimeStop_)),
									0,
									76,
									76,
									gameImgs_[0],
									76.0f / 152.0f, 1,
									0.0f,
									0xffffffff
								);

								break;

							case thunder:

								//描画
								Novice::DrawSpriteRect(
									int(pos_[row][col].x) - globalV.GetCameraPosX() - 6,
									int(pos_[row][col].y * -1.0f)
									+ globalV.GetGroundPos() + globalV.GetCameraPosY() - 6,
									0 + (76 * (isTimeStop_)),
									0,
									76,
									76,
									gameImgs_[1],
									76.0f / 152.0f, 1,
									0.0f,
									0xffffffff
								);

								break;

							case score:

								//描画
								Novice::DrawSpriteRect(
									int(pos_[row][col].x) - globalV.GetCameraPosX(),
									int((pos_[row][col].y * -1.0f))
									+ globalV.GetGroundPos() + globalV.GetCameraPosY()
									+ int(sinf((globalV.grandTimeCount_ / 64.0f) * float(M_PI)) * 6.0f),
									0 + (64 * (globalV.grandTimeCount_ / 16 % 3)),
									0,
									64,
									64,
									gameImgs_[6],
									64.0f / 256.0f, 64.0f / 128.0f,
									0.0f,
									0xffffffff
								);

								break;

							case life:

								//描画
								Novice::DrawSpriteRect(
									int(pos_[row][col].x) - globalV.GetCameraPosX(),
									int((pos_[row][col].y * -1.0f))
									+ globalV.GetGroundPos() + globalV.GetCameraPosY()
									+ int(sinf((globalV.grandTimeCount_ / 64.0f) * float(M_PI)) * 6.0f),
									0 + (64 * (globalV.grandTimeCount_ / 16 % 3)),
									0,
									64,
									64,
									gameImgs_[5],
									64.0f / 256.0f, 64.0f / 128.0f,
									0.0f,
									0xffffffff
								);

								break;

							case clockItem:

								//描画
								Novice::DrawBox(
									int(pos_[row][col].x) - globalV.GetCameraPosX(),
									int(pos_[row][col].y * -1.0f) + globalV.GetGroundPos() + globalV.GetCameraPosY(),
									int(size_.x),
									int(size_.y),
									0.0f,
									0x000000ff,
									kFillModeSolid
								);

								break;

							case accel:

								//描画
								Novice::DrawBox(
									int(pos_[row][col].x) - globalV.GetCameraPosX(),
									int(pos_[row][col].y * -1.0f) + globalV.GetGroundPos() + globalV.GetCameraPosY(),
									int(size_.x),
									int(size_.y),
									0.0f,
									0xff8c00ff,
									kFillModeSolid
								);

								break;

							case savePoint:

								//描画
								if (col != playerRespawnAddress_.x && row != playerRespawnAddress_.y) {
									Novice::DrawSpriteRect(
										int(pos_[row][col].x) - globalV.GetCameraPosX(),
										int(pos_[row][col].y * -1.0f) + globalV.GetGroundPos() + globalV.GetCameraPosY(),
										0 + (64 * (timeCount_ / 4 % 3)),
										0 + (128 * isTimeStop_),
										64,
										64,
										gameImgs_[3],
										64.0f / 256.0f, 64.0f / 256.0f,
										0.0f,
										0xffffffff
									);
								} else {
									Novice::DrawSpriteRect(
										int(pos_[row][col].x) - globalV.GetCameraPosX(),
										int(pos_[row][col].y * -1.0f) + globalV.GetGroundPos() + globalV.GetCameraPosY(),
										64 + (64 * (timeCount_ / 4 % 3)),
										64 + (128 * isTimeStop_),
										64,
										64,
										gameImgs_[3],
										64.0f / 256.0f, 64.0f / 256.0f,
										0.0f,
										0xffffffff
									);
								}

								break;

							default:
								break;
							}


							//風域の描画
							if (blockType_[row][col] >= wind_up &&
								blockType_[row][col] <= wind_left) {

								//描画
								Novice::DrawSpriteRect(
									int(pos_[row][col].x) - globalV.GetCameraPosX(),
									int(pos_[row][col].y * -1.0f) + globalV.GetGroundPos() + globalV.GetCameraPosY(),
									0 + (32 * (timeCount_ / 2 % 7)),
									0 + (32 * ((blockType_[row][col]) - 2)),
									32,
									32,
									gameImgs_[2],
									64.0f / 256.0f, 64.0f / 128.0f,
									0.0f,
									0xffffff7f
								);

							}
						}
					}

				}
			}


			//鳥の描画
			for (int i = 0; i < birdPos_.size(); i++) {
				if (int(birdPos_[i].x) - globalV.GetCameraPosX() >= 0 - size_.x &&
					int(birdPos_[i].x) - globalV.GetCameraPosX() <= 1280) {
					if (int(birdPos_[i].y * -1.0f) + globalV.GetGroundPos() + globalV.GetCameraPosY() >= 0 - size_.y &&
						int(birdPos_[i].y * -1.0f) + globalV.GetGroundPos() + globalV.GetCameraPosY() <= 720) {


						Novice::DrawSpriteRect(
							int(birdPos_[i].x) - globalV.GetCameraPosX(),
							int(birdPos_[i].y * -1.0f) + globalV.GetGroundPos() + globalV.GetCameraPosY(),
							0 + (64 * (timeCount_ / 4 % 4)),
							(64 * (birdDirection_[i] % 2)) + (128 * isTimeStop_),
							64,
							64,
							gameImgs_[4],
							64.0f / 320.0f, 64.0f / 256.0f,
							0.0f,
							0xffffffff
						);

					}
				}

				if (((birdPos_[i].y / 17) * -1.0f) + 344 + int(globalV.GetMiniCameraPos() / 17) >= 24 &&
					((birdPos_[i].y / 17) * -1.0f) + 344 + int(globalV.GetMiniCameraPos() / 17) <= 340) {

					//ミニマップ用
					Novice::DrawBox(
						int((birdPos_[i].x / 17) + 1120),
						int((birdPos_[i].y / 17) * -1.0f) + 344 + int(globalV.GetMiniCameraPos() / 17),
						int(miniMapSize),
						int(miniMapSize),
						0.0f,
						0xff0000ff + int(EaseInQuint(changeScene.easeT_) * -0xff),
						kFillModeSolid
					);
				}
			}


			Novice::DrawBox(
				1120,
				24,
				150,
				320,
				0.0f,
				0x00000088 + int(EaseInQuint(changeScene.easeT_) * -0x88),
				kFillModeSolid
			);

			//ミニマップの表示
			for (int row = 0; row < mapRow; row++) {
				for (int col = 0; col < mapCol; col++) {

					if (((pos_[row][col].y / 17) * -1.0f) + 344 + int(globalV.GetMiniCameraPos() / 17) >= 24 &&
						((pos_[row][col].y / 17) * -1.0f) + 344 + int(globalV.GetMiniCameraPos() / 17) <= 340) {
						switch (blockType_[row][col]) {

						case normal:
							//描画
							Novice::DrawBox(
								int((pos_[row][col].x / 17) + 1120),
								int((pos_[row][col].y / 17) * -1.0f) + 344 + int(globalV.GetMiniCameraPos() / 17),
								int(miniMapSize),
								int(miniMapSize),
								0.0f,
								0xf7efdfff + int(EaseInQuint(changeScene.easeT_) * -0xff),
								kFillModeSolid
							);

							break;

						case thunder:

							//描画
							Novice::DrawBox(
								int((pos_[row][col].x / 17) + 1120),
								int((pos_[row][col].y / 17) * -1.0f) + 344 + int(globalV.GetMiniCameraPos() / 17),
								int(miniMapSize),
								int(miniMapSize),
								0.0f,
								0x666666ff + int(EaseInQuint(changeScene.easeT_) * -0xff),
								kFillModeSolid
							);

							break;

						default:
							break;
						}
					}
				}
			}
		}

		break;

		//=====================================================================================
		//                                     クリア画面
		//=====================================================================================
	case clear:

		Novice::ScreenPrintf(100, 40, "%d", allScoreItem_);
		Novice::ScreenPrintf(100, 60, "%d", score_);

		switch (changeScene.clearSceneRole_) {

		case 0:/*----------------------------"space balloonが中央からうっすら現れる"----------------------------*/
			Novice::DrawSpriteRect(
				int(clearResultPos_[0].x),
				int(clearResultPos_[0].y),
				0,
				0,
				774,
				112,
				clearImgs_[0],
				1,
				112.0f / 234.0f,
				0.0f,
				0xffffff00 + int(EaseInExpo(changeScene.easeT_) * 0xFF)
			);

			break;

		case 1:
			/*-----------------------"space balloon"が上に避けて、下に達成率が現れる--------------------*/

			Novice::DrawSpriteRect(
				int(clearResultPos_[0].x),
				int(clearResultPos_[0].y - 60 * EaseOutQuint(changeScene.easeT_)),
				0,
				0,
				774,
				112,
				clearImgs_[0],
				1,
				112.0f / 234.0f,
				0.0f,
				0xffffffff
			);

			Novice::DrawSpriteRect(
				int(clearResultPos_[1].x + (774 - int(774.0f * EaseInOutExpo(changeScene.easeT_)))),
				int(clearResultPos_[1].y),
				774 - int(774.0f * EaseInOutExpo(changeScene.easeT_)),
				124,
				int(774.0f * EaseInOutExpo(changeScene.easeT_)),
				107,
				clearImgs_[0],
				(774.0f * EaseInOutExpo(changeScene.easeT_)) / 774.0f,
				107.0f / 234.0f,
				0.0f,
				0xffffffff
			);


			//スコア
			if (changeScene.GetStartTimer() > 80) {
				//1桁目
				Novice::DrawSpriteRect(
					int(clearResultPos_[1].x + (2 * 57)),
					int(clearResultPos_[1].y + 20),
					57 * ((globalV.grandTimeCount_ / 3) % 9),
					0,
					57,
					81,
					clearImgs_[1],
					57.0f / 774.0f,
					81.0f / 163.0f,
					0.0f,
					0xffffffff
				);
			} else {//確定したスコア
				//1桁目
				Novice::DrawSpriteRect(
					int(clearResultPos_[1].x + (2 * 57)),
					int(clearResultPos_[1].y + 20),
					57 * scoreDigit[2],
					0,
					57,
					81,
					clearImgs_[1],
					57.0f / 774.0f,
					81.0f / 163.0f,
					0.0f,
					0xffffffff
				);
			}

			//2桁目
			if (changeScene.GetStartTimer() > 40) {
				Novice::DrawSpriteRect(
					int(clearResultPos_[1].x + (1 * 57)),
					int(clearResultPos_[1].y + 20),
					57 * (((globalV.grandTimeCount_ + 3) / 3) % 9),
					0,
					57,
					81,
					clearImgs_[1],
					57.0f / 774.0f,
					81.0f / 163.0f,
					0.0f,
					0xffffffff
				);
			} else {//確定したスコア
				//2桁目
				if (achievement >= 10) {
					Novice::DrawSpriteRect(
						int(clearResultPos_[1].x + (1 * 57)),
						int(clearResultPos_[1].y + 20),
						57 * scoreDigit[1],
						0,
						57,
						81,
						clearImgs_[1],
						57.0f / 774.0f,
						81.0f / 163.0f,
						0.0f,
						0xffffffff
					);
				}
			}

			//3桁目
			Novice::DrawSpriteRect(
				int(clearResultPos_[1].x),
				int(clearResultPos_[1].y + 20),
				57 * (((globalV.grandTimeCount_ + 6) / 3) % 9),
				0,
				57,
				81,
				clearImgs_[1],
				57.0f / 774.0f,
				81.0f / 163.0f,
				0.0f,
				0xffffffff
			);

			//左右にスコアアイテムの星を出す
			Novice::DrawSpriteRect(
				int(1039),
				int(clearResultPos_[1].y)
				+ int(sinf((globalV.grandTimeCount_ / 64.0f) * float(M_PI)) * 6.0f),
				0 + (64 * (globalV.grandTimeCount_ / 16 % 3)),
				0,
				64,
				64,
				gameImgs_[6],
				64.0f / 256.0f, 64.0f / 128.0f,
				0.0f,
				0xffffff00 + int(EaseOutSine(changeScene.easeT_) * 0xFF)
			);

			Novice::DrawSpriteRect(
				int(clearResultPos_[1].x - 74),
				int(clearResultPos_[1].y)
				+ int(sinf((globalV.grandTimeCount_ / 64.0f) * float(M_PI)) * 6.0f),
				0 + (64 * (globalV.grandTimeCount_ / 16 % 3)),
				0,
				64,
				64,
				gameImgs_[6],
				64.0f / 256.0f, 64.0f / 128.0f,
				0.0f,
				0xffffff00 + int(EaseOutSine(changeScene.easeT_) * 0xFF)
			);

			break;

		case 2:/*---------------------------------スコアが確定する-------------------------------------*/

			//space balloon 
			Novice::DrawSpriteRect(
				int(clearResultPos_[0].x),
				int(clearResultPos_[0].y - 60),
				0,
				0,
				774,
				112,
				clearImgs_[0],
				1,
				112.0f / 234.0f,
				0.0f,
				0xffffffff
			);

			//〇〇% completed
			Novice::DrawSpriteRect(
				int(clearResultPos_[1].x),
				int(clearResultPos_[1].y),
				0,
				124,
				774,
				107,
				clearImgs_[0],
				1,
				107.0f / 234.0f,
				0.0f,
				0xffffffff
			);

			//スコア

			//1桁目
			Novice::DrawSpriteRect(
				int(clearResultPos_[1].x + (2 * 57)),
				int(clearResultPos_[1].y + 20),
				57 * scoreDigit[2],
				0,
				57,
				81,
				clearImgs_[1],
				57.0f / 774.0f,
				81.0f / 163.0f,
				0.0f,
				0xffffffff
			);

			//2桁目
			if (achievement >= 10) {
				Novice::DrawSpriteRect(
					int(clearResultPos_[1].x + (1 * 57)),
					int(clearResultPos_[1].y + 20),
					57 * scoreDigit[1],
					0,
					57,
					81,
					clearImgs_[1],
					57.0f / 774.0f,
					81.0f / 163.0f,
					0.0f,
					0xffffffff
				);
			}

			//3桁目
			if (achievement >= 100) {
				Novice::DrawSpriteRect(
					int(clearResultPos_[1].x),
					int(clearResultPos_[1].y + 20),
					57 * scoreDigit[0],
					0,
					57,
					81,
					clearImgs_[1],
					57.0f / 774.0f,
					81.0f / 163.0f,
					0.0f,
					0xffffffff
				);
			}

			//左右にスコアアイテムの星を出す
			Novice::DrawSpriteRect(
				int(1039),
				int(clearResultPos_[1].y)
				+ int(sinf((globalV.grandTimeCount_ / 64.0f) * float(M_PI)) * 6.0f),
				0 + (64 * (globalV.grandTimeCount_ / 16 % 3)),
				0,
				64,
				64,
				gameImgs_[6],
				64.0f / 256.0f, 64.0f / 128.0f,
				0.0f,
				0xffffffff
			);

			Novice::DrawSpriteRect(
				int(clearResultPos_[1].x - 74),
				int(clearResultPos_[1].y)
				+ int(sinf((globalV.grandTimeCount_ / 64.0f) * float(M_PI)) * 6.0f),
				0 + (64 * (globalV.grandTimeCount_ / 16 % 3)),
				0,
				64,
				64,
				gameImgs_[6],
				64.0f / 256.0f, 64.0f / 128.0f,
				0.0f,
				0xffffffff
			);

			break;

		case 3:
			break;

		default:
			break;
		}




		break;

	default:
		break;
	}
}