#include "MiniMap.h"
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
	player.Init(titleScene, map);

	GlobalVariable globalV;
	globalV.Init();
	
	Title title;
	title.Init();

	MiniMap miniMap;

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
		
		title.Update(keys,preKeys,changeScene);
		globalV.Update();
		map.Update(scene,changeScene);
		player.Update(keys,preKeys,&globalV.cameraPosX_, &globalV.cameraPosY_, &globalV.miniCameraPos_, map, scene,changeScene,globalV);
		effect->Update(player);

		changeScene.Update(scene,keys);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///


		//描画
		map.DrawBG( globalV);

		if (scene.GetSceneNum() == titleScene) {
			map.Draw(globalV, scene, changeScene,title);
			title.Draw(changeScene);
		}

		effect->Draw(globalV);
		player.Draw(globalV, scene,changeScene);

		if (scene.GetSceneNum() > titleScene) {
			map.Draw(globalV, scene, changeScene,title);
		}
	
		player.DrawTutorial(globalV);
		miniMap.Draw(globalV,scene,changeScene,map,player);
		changeScene.Draw(scene);

		//音声
		player.Sound(keys, preKeys, scene,map);
		changeScene.Sound(scene);

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
