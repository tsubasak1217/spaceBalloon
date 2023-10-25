#include "MiniMap.h"

void MiniMap::Draw(GlobalVariable globalV, Scene scene, ChangeScene changeScene, Map map, Player player) {

	if (scene.GetSceneNum() == game) {

		if (changeScene.GetIsStart()) {

			//ミニマップの表示
			Novice::DrawBox(
				1120,
				24,
				150,
				320,
				0.0f,
				0x05143600 + int(EaseInQuint(changeScene.startEaseT_) * 0x88),
				kFillModeSolid
			);

			Novice::DrawBox(
				1120,
				24,
				150,
				320,
				0.0f,
				0xffffff00 + int(EaseInQuint(changeScene.startEaseT_) * 0xff),
				kFillModeWireFrame
			);

			//リトライ方法表示
			Novice::DrawSprite(
				1100,
				360,
				miniMapImgs[4],
				1,
				1,
				0.0f,
				0xffffff00 + int(EaseInQuint(changeScene.startEaseT_) * 0xff)
			);

			//メーター表示
			for (int i = 0; i <= 40; i++) {

				if (i % 5 != 0 && i != 0) {
					Novice::DrawLine(
						1120,
						24 + int(320 / 40) * i,
						1110,
						24 + int(320 / 40) * i,
						0xffffff00 + int(EaseInQuint(changeScene.startEaseT_) * 0xff)
					);
				} else {
					Novice::DrawLine(
						1120,
						24 + int(320 / 40) * i,
						1100,
						24 + int(320 / 40) * i,
						0xffffff00 + int(EaseInQuint(changeScene.startEaseT_) * 0xff)
					);
				}
			}

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
								0xf7efdf00 + int(EaseInQuint(changeScene.startEaseT_) * 0xff),
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
								0x88888800 + int(EaseInQuint(changeScene.startEaseT_) * 0xff),
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
								0xffff0000 + int(EaseInQuint(changeScene.startEaseT_) * 0xff)
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
								0xff518100 + int(EaseInQuint(changeScene.startEaseT_) * 0xff),
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
								0xff8c0000 + int(EaseInQuint(changeScene.startEaseT_) * 0xff),
								kFillModeSolid
							);

							break;

						case clockItem:

							//描画
							Novice::DrawSprite(
								int((map.GetPos(row, col).x / 17) + 1120 - 2),
								int((map.GetPos(row, col).y / 17 * -1.0f) + 344 + int(globalV.GetMiniCameraPos() / 17) - 2),
								miniMapImgs[0],
								1,
								1,
								0.0f,
								0xffffff00 + int(EaseInQuint(changeScene.startEaseT_) * 0xff)
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
								0xffffff00 + int(EaseInQuint(changeScene.startEaseT_) * 0xff)
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

				if (((map.GetBirdPos()[i].y / 17) * -1.0f) + 344 + int(globalV.GetMiniCameraPos() / 17) >= 24 &&
					((map.GetBirdPos()[i].y / 17) * -1.0f) + 344 + int(globalV.GetMiniCameraPos() / 17) <= 340) {

					//ミニマップ用
					Novice::DrawBox(
						int((map.GetBirdPos()[i].x / 17) + 1120),
						int((map.GetBirdPos()[i].y / 17) * -1.0f) + 344 + int(globalV.GetMiniCameraPos() / 17),
						int(miniMapSize),
						int(miniMapSize),
						0.0f,
						0xff000000 + int(EaseInQuint(changeScene.startEaseT_) * 0xff),
						kFillModeSolid
					);
				}
			}

			//ミニマップ用
			Novice::DrawEllipse(
				int(player.GetPos().x / 17) + 1120,
				int((player.GetPos().y / 17) * -1.0f) + 344 + int(globalV.GetMiniCameraPos() / 17),
				4,
				4,
				0.0f,
				0xff518100 + int(EaseInQuint(changeScene.startEaseT_) * 0xff),
				kFillModeSolid
			);

			Novice::DrawLine(//左上→右上
				int(player.GetFramePos(0).x / 17) + 1120,
				int((player.GetFramePos(0).y / 17) * -1.0f) + 344 + int(globalV.GetMiniCameraPos() / 17),
				int(player.GetFramePos(1).x / 17) + 1120,
				int((player.GetFramePos(1).y / 17) * -1.0f) + 344 + int(globalV.GetMiniCameraPos() / 17),
				0xff000000 + int(EaseInQuint(changeScene.easeT_) * 0xff)
			);

			Novice::DrawLine(//左上→右上
				int(player.GetFramePos(1).x / 17) + 1120,
				int((player.GetFramePos(1).y / 17) * -1.0f) + 344 + int(globalV.GetMiniCameraPos() / 17),
				int(player.GetFramePos(3).x / 17) + 1120,
				int((player.GetFramePos(3).y / 17) * -1.0f) + 344 + int(globalV.GetMiniCameraPos() / 17),
				0xff000000 + int(EaseInQuint(changeScene.easeT_) * 0xff)
			);

			Novice::DrawLine(//左上→右上
				int(player.GetFramePos(2).x / 17) + 1120,
				int((player.GetFramePos(2).y / 17) * -1.0f) + 344 + int(globalV.GetMiniCameraPos() / 17),
				int(player.GetFramePos(3).x / 17) + 1120,
				int((player.GetFramePos(3).y / 17) * -1.0f) + 344 + int(globalV.GetMiniCameraPos() / 17),
				0xff000000 + int(EaseInQuint(changeScene.easeT_) * 0xff)
			);

			Novice::DrawLine(//左上→右上
				int(player.GetFramePos(0).x / 17) + 1120,
				int((player.GetFramePos(0).y / 17) * -1.0f) + 344 + int(globalV.GetMiniCameraPos() / 17),
				int(player.GetFramePos(2).x / 17) + 1120,
				int((player.GetFramePos(2).y / 17) * -1.0f) + 344 + int(globalV.GetMiniCameraPos() / 17),
				0xff000000 + int(EaseInQuint(changeScene.easeT_) * 0xff)
			);

			//現在のプレイヤー高度描画
			Novice::DrawSprite(
				int(1120 - 26),
				int(344 - (320 * (player.GetPos().y / 15360))),
				miniMapImgs[2],
				0.7f,
				0.7f,
				0.0f,
				0xffffff00 + int(EaseInQuint(changeScene.startEaseT_) * 0xff)
			);

		} else {

			//ミニマップの表示
			Novice::DrawBox(
				1120,
				24,
				150,
				320,
				0.0f,
				0x05143688 + int(EaseInQuint(changeScene.easeT_) * -0x88),
				kFillModeSolid
			);

			Novice::DrawBox(
				1120,
				24,
				150,
				320,
				0.0f,
				0xffffffff + int(EaseInQuint(changeScene.easeT_) * -0xff),
				kFillModeWireFrame
			);

			//リトライ方法表示
			Novice::DrawSprite(
				1100,
				360,
				miniMapImgs[4],
				1,
				1,
				0.0f,
				0xffffffff + int(EaseInQuint(changeScene.easeT_) * -0xff)
			);


			//メーター表示
			for (int i = 0; i <= 40; i++) {

				if (i % 5 != 0 && i != 0) {
					Novice::DrawLine(
						1120,
						24 + int(320 / 40) * i,
						1110,
						24 + int(320 / 40) * i,
						0xffffffff + int(EaseInQuint(changeScene.easeT_) * -0xff)
					);
				} else {
					Novice::DrawLine(
						1120,
						24 + int(320 / 40) * i,
						1100,
						24 + int(320 / 40) * i,
						0xffffffff + int(EaseInQuint(changeScene.easeT_) * -0xff)
					);
				}
			}

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
								0x888888ff + int(EaseInQuint(changeScene.easeT_) * -0xff),
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
								int((map.GetPos(row, col).x / 17) + 1120 - 2),
								int((map.GetPos(row, col).y / 17 * -1.0f) + 344 + int(globalV.GetMiniCameraPos() / 17) - 2),
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
			}

			//プレイヤー描画
			if ((player.GetPos().y / 17 * -1.0f) + 344 + int(globalV.GetMiniCameraPos() / 17) >= 24 &&
				(player.GetPos().y / 17 * -1.0f) + 344 + int(globalV.GetMiniCameraPos() / 17) <= 340) {

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
					int(player.GetFramePos(0).x / 17) + 1120,
					int((player.GetFramePos(0).y / 17) * -1.0f) + 344 + int(globalV.GetMiniCameraPos() / 17),
					int(player.GetFramePos(1).x / 17) + 1120,
					int((player.GetFramePos(1).y / 17) * -1.0f) + 344 + int(globalV.GetMiniCameraPos() / 17),
					RED + int(EaseInQuint(changeScene.easeT_) * -0xff)
				);

				Novice::DrawLine(//左上→右上
					int(player.GetFramePos(1).x / 17) + 1120,
					int((player.GetFramePos(1).y / 17) * -1.0f) + 344 + int(globalV.GetMiniCameraPos() / 17),
					int(player.GetFramePos(3).x / 17) + 1120 ,
					int((player.GetFramePos(3).y / 17) * -1.0f) + 344 + int(globalV.GetMiniCameraPos() / 17),
					RED + int(EaseInQuint(changeScene.easeT_) * -0xff)
				);

				Novice::DrawLine(//左上→右上
					int(player.GetFramePos(2).x / 17) + 1120,
					int((player.GetFramePos(2).y / 17) * -1.0f) + 344 + int(globalV.GetMiniCameraPos() / 17),
					int(player.GetFramePos(3).x / 17) + 1120,
					int((player.GetFramePos(3).y / 17) * -1.0f) + 344 + int(globalV.GetMiniCameraPos() / 17),
					RED + int(EaseInQuint(changeScene.easeT_) * -0xff)
				);

				Novice::DrawLine(//左上→右上
					int(player.GetFramePos(0).x / 17) + 1120 ,
					int((player.GetFramePos(0).y / 17) * -1.0f) + 344 + int(globalV.GetMiniCameraPos() / 17),
					int(player.GetFramePos(2).x / 17) + 1120,
					int((player.GetFramePos(2).y / 17) * -1.0f) + 344 + int(globalV.GetMiniCameraPos() / 17),
					RED + int(EaseInQuint(changeScene.easeT_) * -0xff)
				);
				
			}

			//現在のプレイヤー高度描画
			Novice::DrawSprite(
				int(1120 - 26),
				int(344 - (320 * (player.GetPos().y / 15360))),
				miniMapImgs[2],
				0.7f,
				0.7f,
				0.0f,
				0xffffffff + int(EaseInQuint(changeScene.easeT_) * -0xff)
			);
		}


		//プレイヤーのライフ表示
		for (int i = 0; i < player.GetLife(); i++) {

			Novice::DrawSpriteRect(
				720 + ((i % 10) * 36),
				30 + (i / 10) * 36,
				0, 0,
				32, 32,
				miniMapImgs[3],
				32.0f / 64.0f, 1.0f,
				0.0f,
				0xffffffaf
			);
		}

		//プレイヤーのゲームオーバー数表示
		for (int i = 0; i < player.GetDeadCount(); i++) {

			Novice::DrawSpriteRect(
				530 + ((i%15) * -36),
				30 + int(i/15) * 36,
				32, 0,
				32, 32,
				miniMapImgs[3],
				32.0f / 64.0f, 1.0f,
				0.0f,
				0xffffffaf
			);
		}
	}

	if (scene.GetSceneNum() == clear) {

		//プレイヤーのライフ表示
		for (int i = 0; i < player.GetLife(); i++) {

			Novice::DrawSpriteRect(
				720 + ((i % 10)* 36),
				30 + (i / 10) * 36,
				0, 0,
				32, 32,
				miniMapImgs[3],
				32.0f / 64.0f, 1.0f,
				0.0f,
				0xffffffaf
			);
		}


		//プレイヤーのゲームオーバー数表示
		for (int i = 0; i < player.GetDeadCount(); i++) {

			Novice::DrawSpriteRect(
				530 + ((i % 15) * -36),
				30 + int(i / 15) * 36,
				32, 0,
				32, 32,
				miniMapImgs[3],
				32.0f / 64.0f, 1.0f,
				0.0f,
				0xffffffaf
			);
		}
	}
}