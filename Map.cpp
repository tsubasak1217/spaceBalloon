#include "Map.h"

void Map::Init() {
	blockType_ = LoadFile("./Resources./spaceBalloon_map.csv");

	//行を反転
	std::reverse(blockType_.begin(), blockType_.end());

	//大きさ
	size_ = { 64.0f,64.0f };
	miniMapSize = 4.0f;

	//ブロックの配置
	for (int row = 0; row < mapRow; row++) {
		for (int col = 0; col < mapCol; col++) {

			pos_[row][col].y = size_.y * (row + 1);
			pos_[row][col].x = size_.x * col;

			if (blockType_[row][col] == 6) {
				birdPos_.push_back(pos_[row][col]);
			}
		}
	}

	//鳥の初期番地計算
	for (int i = 0; i < birdPos_.size(); i++) {
		birdAddress_.push_back(
			{
			int((birdPos_[i].x + (size_.x / 2)) / size_.x),
			int((birdPos_[i].y - (size_.y / 2)) / size_.y)
			}
		);

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

}

//==================================================================================
void Map::Update() {

	for (int i = 0; i < birdPos_.size(); i++) {

		//鳥の番地更新==================================================================
		birdAddress_[i] = {
			int((birdPos_[i].x + (size_.x / 2)) / size_.x),
			int((birdPos_[i].y - (size_.y / 2)) / size_.y)
		};

		//方向と座標の更新===============================================================
		switch(birdDirection_[i]){
		case Right:
			if (birdAddress_[i].x + 1 < 40 && birdAddress_[i].x - 1 >= 0) {
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
			if (birdAddress_[i].x + 1 < 40 && birdAddress_[i].x - 1 >= 0) {
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
			if (birdAddress_[i].y + 1 < 240 && birdAddress_[i].y - 1 >= 0) {
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
			if (birdAddress_[i].y + 1 < 240 && birdAddress_[i].y - 1 >= 0) {
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


	//==================================================================================
	void Map::Draw(GlobalVariable globalV) {

		for (int row = 0; row < mapRow; row++) {
			for (int col = 0; col < mapCol; col++) {



				//ブロックの座標がスクリーン内のとき
				if (int(pos_[row][col].x) - globalV.GetCameraPosX() >= 0 - size_.x &&
					int(pos_[row][col].x) - globalV.GetCameraPosX() <= 1280) {
					if (int(pos_[row][col].y * -1.0f) + globalV.GetGroundPos() + globalV.GetCameraPosY() >= 0 - size_.y &&
						int(pos_[row][col].y * -1.0f) + globalV.GetGroundPos() + globalV.GetCameraPosY() <= 720) {


						switch (blockType_[row][col]) {

						case normal:
							//描画
							Novice::DrawBox(
								int(pos_[row][col].x) - globalV.GetCameraPosX(),
								int(pos_[row][col].y * -1.0f) + globalV.GetGroundPos() + globalV.GetCameraPosY(),
								int(size_.x),
								int(size_.y),
								0.0f,
								0xf7efdfff,
								kFillModeSolid
							);

							break;

						case wind_up:

							//描画
							Novice::DrawBox(
								int(pos_[row][col].x) - globalV.GetCameraPosX(),
								int(pos_[row][col].y * -1.0f) + globalV.GetGroundPos() + globalV.GetCameraPosY(),
								int(size_.x),
								int(size_.y),
								0.0f,
								0xff5d5064,
								kFillModeSolid
							);

							break;

						case wind_right:

							//描画
							Novice::DrawBox(
								int(pos_[row][col].x) - globalV.GetCameraPosX(),
								int(pos_[row][col].y * -1.0f) + globalV.GetGroundPos() + globalV.GetCameraPosY(),
								int(size_.x),
								int(size_.y),
								0.0f,
								0xffdd5064,
								kFillModeSolid
							);

							break;

						case wind_down:

							//描画
							Novice::DrawBox(
								int(pos_[row][col].x) - globalV.GetCameraPosX(),
								int(pos_[row][col].y * -1.0f) + globalV.GetGroundPos() + globalV.GetCameraPosY(),
								int(size_.x),
								int(size_.y),
								0.0f,
								0xa7ff5064,
								kFillModeSolid
							);

							break;

						case wind_left:

							//描画
							Novice::DrawBox(
								int(pos_[row][col].x) - globalV.GetCameraPosX(),
								int(pos_[row][col].y * -1.0f) + globalV.GetGroundPos() + globalV.GetCameraPosY(),
								int(size_.x),
								int(size_.y),
								0.0f,
								0x50ffda64,
								kFillModeSolid
							);

							break;

						case thunder:

							//描画
							Novice::DrawBox(
								int(pos_[row][col].x) - globalV.GetCameraPosX(),
								int(pos_[row][col].y * -1.0f) + globalV.GetGroundPos() + globalV.GetCameraPosY(),
								int(size_.x),
								int(size_.y),
								0.0f,
								0x666666ff,
								kFillModeSolid
							);

							break;
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

					Novice::DrawBox(
						int(birdPos_[i].x) - globalV.GetCameraPosX(),
						int(birdPos_[i].y * -1.0f) + globalV.GetGroundPos() + globalV.GetCameraPosY(),
						int(size_.x),
						int(size_.y),
						0.0f,
						RED,
						kFillModeSolid
					);

				}
			}
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
							int((pos_[row][col].y / 17) * -1.0f) + 344 + int(globalV.GetMiniCameraPos() / 17),
							int(miniMapSize),
							int(miniMapSize),
							0.0f,
							0xf7efdfff,
							kFillModeSolid
						);

						break;

					case bird:

						//描画
						Novice::DrawBox(
							int((pos_[row][col].x / 17) + 1120),
							int((pos_[row][col].y / 17) * -1.0f) + 344 + int(globalV.GetMiniCameraPos() / 17),
							int(miniMapSize),
							int(miniMapSize),
							0.0f,
							RED,
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
	}