#pragma once
#include <Vector2.h>
#include <Novice.h>
#include "ChangeScene.h"

class Title {

private:

	//タイトルのx,y
	Vector2 titlePos_[2];
	//SPACEのx,y
	Vector2 spacePos_[7];
	//速度
	Vector2 velocity_[2];
	Vector2 spacevelocity_[5];
	//加速度
	Vector2 acceleration_[2];
	Vector2 spaceacceleration_[5];
	//タイトルの座標取得
	Vector2 Pos_[2];
	//タイマー
	int time_[2];
	//飛ばすフラグ
	int timecount_[2];
	int spacetimecount_[5];
	//飛ばす時間
	int jumpcount_[2];
	int spacejumpcount_[5];
	int passing;
	int keysHit;
	int SPACEHit;

public:

	int titleResources[3]{
	Novice::LoadTexture("./Resources./Images./title./space.png"),
	Novice::LoadTexture("./Resources./Images./title./balloon.png"),
	Novice::LoadTexture("./Resources./Images./title./unnamed.png"),
	};

	void Init() {
		//-----初期化-----//
		time_[0] = 0;
		time_[1] = 0;
		SPACEHit = 0;
		Pos_[0].x = 0.0f;
		Pos_[0].y = 650.0f;
		Pos_[1].x = 50.0f;
		Pos_[1].y = 650.0f;

		spacePos_[0].x = 525.0f;
		spacePos_[0].y = 540.0f;
		spacePos_[6].x = 496.0f + (37.0f * 6);
		spacePos_[6].y = 540.0f;

		spacetimecount_[0] = 0;
		spacetimecount_[1] = 0;
		spacetimecount_[2] = 0;
		spacetimecount_[3] = 0;
		spacetimecount_[4] = 0;
		timecount_[0] = 0;
		timecount_[1] = 0;
		keysHit = 0;
		passing = 0;

		for (int i = 1; i < 6; i++) {
			//跳ねる時間設定
			if (i <= 2) {
				jumpcount_[i - 1] = 70 + (13 * i);
			}
			spacejumpcount_[i - 1] =  + (10 * i);
		}

		for (int i = 0; i < 6; i++) {//位置
			if (i < 2) {
				titlePos_[i].x = Pos_[i].x;
				titlePos_[i].y = Pos_[i].y;
				velocity_[i].y = -12.0f;
				acceleration_[i].y = 0.1f;//下へ加速
			}
			if (i >= 1 && i < 6) {
				spacePos_[i].x = 510.0f + 37.0f * i;
				spacePos_[i].y = 540.0f;
			}
			if (i < 5) {
				spacevelocity_[i].y = -1.7f;
				spaceacceleration_[i].y = 0.1f;//下へ加速
			}
		}
	
	};
	

	//アップデート
	void Update(char* keys,char* preKeys,ChangeScene changeScene);

	//ドロー
	void Draw(ChangeScene changeScene);
};







