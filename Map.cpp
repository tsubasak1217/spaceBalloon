#include "Map.h"

void Map::Init() {
	blockCsv = LoadFile("./Resources./spaceBalloon_map.csv");

	//下から順にコピーしていく
	for (int row = int(blockCsv.size()) - 1; row >= 0; row--) {
		for (int col = 0; col < int(blockCsv[0].size()); col++) {
			blockType_[(blockCsv.size() - 1) - row][col] = blockCsv[row][col];
		}
	}

	size_ = { 64.0f,64.0f };

	//ブロックの配置
	for (int row = 0; row < mapRow; row++) {
		for (int col = 0; col < mapCol; col++) {

			pos_[row][col].y = size_.y * (row + 1);
			pos_[row][col].x = size_.x * col;
		}
	}
}

void Map::Draw(GlobalVariable globalV) {

	for (int row = 0; row < mapRow; row++) {
		for (int col = 0; col < mapCol; col++) {

			//ブロックが存在していて
			if (blockType_[row][col] == 1) {

				//その座標がスクリーン内のときのみ
				if (int(pos_[row][col].x) - globalV.GetCameraPosX() >= 0 - size_.x &&
					int(pos_[row][col].x) - globalV.GetCameraPosX() <= 1280) {

					if (int(pos_[row][col].y * -1.0f) + globalV.GetGroundPos() + globalV.GetCameraPosY() >= 0 - size_.y &&
						int(pos_[row][col].y * -1.0f) + globalV.GetGroundPos() + globalV.GetCameraPosY() <= 720) {

						//描画する
						Novice::DrawBox(
							int(pos_[row][col].x) - globalV.GetCameraPosX(),
							int(pos_[row][col].y * -1.0f) + globalV.GetGroundPos() + globalV.GetCameraPosY(),
							int(size_.x),
							int(size_.y),
							0.0f,
							0x000000ff,
							kFillModeSolid
						);
					}
				}
			}
		}
	}
}