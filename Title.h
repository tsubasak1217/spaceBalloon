#pragma once
#include <Vector2.h>
#include <Novice.h>

class Title {

private:

	Vector2 titlePos[2];//タイトルのx,y
	Vector2 velocity[2];//速度
	Vector2 acceleration[2];//加速度
	Vector2 Pos[2] = { 0,0 };//タイトルの座標取得

	int time;//タイマー
	int timecount[2] = { 0 };//飛ばすフラグ
	int jumpcount[2];//飛ばす時間

public:

	int titleResources[2]{
	Novice::LoadTexture("./Resources./Images./title./space.png"),
	Novice::LoadTexture("./Resources./Images./title./balloon.png"),
	};

	void Init() {
		time = 0;
		Pos[0].x = 0.0f;
		Pos[0].y = 300.0f;
		Pos[1].x = 0.0f;
		Pos[1].y = 300.0f;

		for (int i = 1; i < 3; i++) {
			jumpcount[i - 1] = 10 * i;//跳ねる時間設定
		}

		for (int i = 0; i < 2; i++) {//位置
			if (i < 2) {
				titlePos[i].x = Pos[0].x;
				titlePos[i].y = Pos[0].y;
			}

			acceleration[i].y = 0.2f;//下へ加速

		}
	};

	//アップデート
	void Update();

	//ドロー
	void Draw();
};

