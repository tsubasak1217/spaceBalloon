#include "Player.h"
#include "Emitter.h"

//======================================================
//					グローバル変数/定数
//======================================================

const char kWindowTitle[] = "スペースバルーン";

//======================================================
//						構造体
//======================================================
//a


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
	char keys[256] = {0};
	char preKeys[256] = {0};

	Player player;
	player.Init();

	Emitter* effect = new Emitter();

	Map map;
	map.Init();

	GlobalVariable globalV;
	globalV.Init();

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

		map.Update();
		player.Update(keys,preKeys,&globalV.cameraPosX_, &globalV.cameraPosY_, &globalV.miniCameraPos_, map);
		effect->Update(player);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		
		Novice::DrawBox(
			0, 0,
			1280,
			720,
			0.0f,
			0x2e4c80ff,
			kFillModeSolid
		);

		map.Draw(globalV);
		effect->Draw(globalV);
		player.Draw(globalV);

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
