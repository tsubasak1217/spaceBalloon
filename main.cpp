#include "Player.h"
#include "Emitter.h"
#include "Title.h"
//======================================================
//					グローバル変数/定数
//======================================================

const char kWindowTitle[] = "スペースバルーン";

//======================================================
//						構造体
//======================================================



//======================================================
//					  main関数
//======================================================

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	//乱数の初期化
	srand((unsigned)time(NULL));

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	Scene scene;
	scene.Init();

	ChangeScene changeScene;
	changeScene.Init();

	Emitter* effect = new Emitter();

	Map map;
	map.Init();

	Player player;
	player.Init(title, map);

	GlobalVariable globalV;
	globalV.Init();
	
	Title title;
	title.Init();

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		
		title.Update();

		map.Update(scene);
		player.Update(keys,preKeys,&globalV.cameraPosX_, &globalV.cameraPosY_, &globalV.miniCameraPos_, map, scene,changeScene);
		effect->Update(player,map);

		changeScene.Update(scene,keys);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

	
		effect->Draw(globalV);
		player.Draw(globalV, scene,changeScene);

		if (scene.GetSceneNum() > title) {
			map.Draw(globalV, scene, changeScene);
		}
		changeScene.Draw(scene);
		title.Draw();
		Novice::ScreenPrintf(100, 20, "%d", map.GetSavedBlockType(0, 0));
		Novice::ScreenPrintf(100, 40, "%d", map.GetBlockType(0, 0));
		Novice::ScreenPrintf(100, 60, "%d", changeScene.GetIsFinish());
		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
