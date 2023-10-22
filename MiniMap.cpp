#include "MiniMap.h"

void MiniMap::Draw(GlobalVariable globalV, Scene scene, ChangeScene changeScene, Map map, Player player) {

	if (scene.GetSceneNum() == game) {

		//ミニマップの表示
		for (int row = 0; row < 240; row++) {
			for (int col = 0; col < 40; col++) {

				if ((map.GetPos(row, col).y / 17 * -1.0f) + 344 + int(globalV.GetMiniCameraPos() / 17) >= 24 &&
					(map.GetPos(row, col).y / 17 * -1.0f) + 344 + int(globalV.GetMiniCameraPos() / 17) <= 340) {

					switch (map.GetBlockType(row, col)) {

					case normal:
						//描画
						Novice::DrawBox(
							int((map.GetPos(row, col).x / 17) + 1120),
							int((map.GetPos(row, col).y / 17 * -1.0f) + 344 + int(globalV.GetMiniCameraPos() / 17)),
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
							int((map.GetPos(row, col).x / 17) + 1120),
							int((map.GetPos(row, col).y / 17 * -1.0f) + 344 + int(globalV.GetMiniCameraPos() / 17)),
							int(miniMapSize),
							int(miniMapSize),
							0.0f,
							0x666666ff + int(EaseInQuint(changeScene.easeT_) * -0xff),
							kFillModeSolid
						);

						break;

					case score:

						//描画
						DrawStar(
							{ (map.GetPos(row,col).x / 17) + 1120 + (miniMapSize * 0.5f),
							((map.GetPos(row,col).y / 17 * -1.0f) + 344 + int(globalV.GetMiniCameraPos() / 17) + (miniMapSize * 0.5f)) },
							miniMapSize,
							0.0f,
							0xffff00ff + int(EaseInQuint(changeScene.easeT_) * -0xff)
						);

						break;

					case life:

						//描画
						Novice::DrawBox(
							int((map.GetPos(row, col).x / 17) + 1120),
							int((map.GetPos(row, col).y / 17 * -1.0f) + 344 + int(globalV.GetMiniCameraPos() / 17)),
							int(miniMapSize),
							int(miniMapSize),
							0.0f,
							0xff5181ff + int(EaseInQuint(changeScene.easeT_) * -0xff),
							kFillModeSolid
						);
						break;

					case accel:

						//描画
						Novice::DrawBox(
							int((map.GetPos(row, col).x / 17) + 1120),
							int((map.GetPos(row, col).y / 17 * -1.0f) + 344 + int(globalV.GetMiniCameraPos() / 17)),
							int(miniMapSize),
							int(miniMapSize),
							0.0f,
							0xff8c00ff + int(EaseInQuint(changeScene.easeT_) * -0xff),
							kFillModeSolid
						);

						break;

					case clockItem:

						//描画
						Novice::DrawSprite(
							int((map.GetPos(row, col).x / 17) + 1120 -2),
							int((map.GetPos(row, col).y / 17 * -1.0f) + 344 + int(globalV.GetMiniCameraPos() / 17) -2),
							miniMapImgs[0],
							1,
							1,
							0.0f,
							0xffffffff + int(EaseInQuint(changeScene.easeT_) * -0xff)
						);
						break;

					case savePoint:

						//描画
						Novice::DrawSprite(
							int((map.GetPos(row, col).x / 17) + 1120 - 3),
							int((map.GetPos(row, col).y / 17 * -1.0f) + 344 + int(globalV.GetMiniCameraPos() / 17) - 3),
							miniMapImgs[1],
							1.5f,
							1.5f,
							0.0f,
							0xffffffff + int(EaseInQuint(changeScene.easeT_) * -0xff)
						);
						break;

					default:
						break;
					}
				}
			}
		}

		//鳥の描画
		for (int i = 0; i < map.GetBirdPos().size(); i++) {
			//if (int(map.GetBirdPos()[i].x) - globalV.GetCameraPosX() >= 0 - map.GetSize().x &&
			//	int(map.GetBirdPos()[i].x) - globalV.GetCameraPosX() <= 1280) {


				if (((map.GetBirdPos()[i].y / 17) * -1.0f) + 344 + int(globalV.GetMiniCameraPos() / 17) >= 24 &&
					((map.GetBirdPos()[i].y / 17) * -1.0f) + 344 + int(globalV.GetMiniCameraPos() / 17) <= 340) {

					//ミニマップ用
					Novice::DrawBox(
						int((map.GetBirdPos()[i].x / 17) + 1120),
						int((map.GetBirdPos()[i].y / 17) * -1.0f) + 344 + int(globalV.GetMiniCameraPos() / 17),
						int(miniMapSize),
						int(miniMapSize),
						0.0f,
						0xff0000ff + int(EaseInQuint(changeScene.easeT_) * -0xff),
						kFillModeSolid
					);
				}
			//}
		}

		//ミニマップ用
		Novice::DrawEllipse(
			int(player.GetPos().x / 17) + 1120,
			int((player.GetPos().y / 17) * -1.0f) + 344 + int(globalV.GetMiniCameraPos() / 17),
			4,
			4,
			0.0f,
			0xff5181ff + int(EaseInQuint(changeScene.easeT_) * -0xff),
			kFillModeSolid
		);

		Novice::DrawLine(//左上→右上
			int(player.GetPos().x / 17) + 1120 - 38,
			int((player.GetPos().y / 17) * -1.0f) + 344 + int(globalV.GetMiniCameraPos() / 17) - 21,
			int(player.GetPos().x / 17) + 1120 + 38,
			int((player.GetPos().y / 17) * -1.0f) + 344 + int(globalV.GetMiniCameraPos() / 17) - 21,
			RED + int(EaseInQuint(changeScene.easeT_) * -0xff)
		);

		Novice::DrawLine(//左上→右上
			int(player.GetPos().x / 17) + 1120 - 38,
			int((player.GetPos().y / 17) * -1.0f) + 344 + int(globalV.GetMiniCameraPos() / 17) + 21,
			int(player.GetPos().x / 17) + 1120 + 38,
			int((player.GetPos().y / 17) * -1.0f) + 344 + int(globalV.GetMiniCameraPos() / 17) + 21,
			RED + int(EaseInQuint(changeScene.easeT_) * -0xff)
		);

		Novice::DrawLine(//左上→右上
			int(player.GetPos().x / 17) + 1120 - 38,
			int((player.GetPos().y / 17) * -1.0f) + 344 + int(globalV.GetMiniCameraPos() / 17) + 21,
			int(player.GetPos().x / 17) + 1120 - 38,
			int((player.GetPos().y / 17) * -1.0f) + 344 + int(globalV.GetMiniCameraPos() / 17) - 21,
			RED + int(EaseInQuint(changeScene.easeT_) * -0xff)
		);

		Novice::DrawLine(//左上→右上
			int(player.GetPos().x / 17) + 1120 + 38,
			int((player.GetPos().y / 17) * -1.0f) + 344 + int(globalV.GetMiniCameraPos() / 17) + 21,
			int(player.GetPos().x / 17) + 1120 + 38,
			int((player.GetPos().y / 17) * -1.0f) + 344 + int(globalV.GetMiniCameraPos() / 17) - 21,
			RED + int(EaseInQuint(changeScene.easeT_) * -0xff)
		);

	//現在のプレイヤー高度描画
	Novice::DrawSprite(
		int(1120 - 26),
		int(344 -(320 * (player.GetPos().y/15360))),
		miniMapImgs[2],
		0.7f,
		0.7f,
		0.0f,
		0xffffffff + int(EaseInQuint(changeScene.easeT_) * -0xff)
	);

	}

}