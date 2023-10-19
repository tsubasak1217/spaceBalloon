#pragma once
#include <Vector2.h>

class Title {

private:

	Vector2 titlePos_[12];//タイトルのx,y
	Vector2 velocity_[12];//速度
  	Vector2 acceleration_[12];//加速度
	Vector2 Pos_[2] = { 0,0 };//タイトルの座標取得

	int time;//タイマー
	int timecount[12] = { 0 };//飛ばすフラグ
	int jumpcount_[12];//飛ばす時間

	//int titleResources_[12];//タイトル画像   

public:



	void Init() {
		time = 0;
		Pos_[0].x = 300.0f;
		Pos_[0].y = 300.0f;
		Pos_[1].x = 1000.0f;
		Pos_[1].y = 500.0f;

		//titleResources_[0] = Novice::LoadTexture("./Resources/Images/title/05.png");

		for (int i = 1; i < 13; i++) {
			jumpcount_[i-1] = 5 * i;//跳ねる時間設定
		}

		for (int i = 0; i < 12; i++) {//位置
			if (i < 5) {
				titlePos_[i].x = Pos_[0].x;
				titlePos_[i].y = Pos_[0].y;
				Pos_[0].x += 120;
			}
			if (i >= 5) {
				titlePos_[i].x = Pos_[1].x;
				titlePos_[i].y = Pos_[1].y;
				Pos_[1].x -= 120;
			}
			acceleration_[i].y = 0.2f;//下へ加速
		}
	};
	
	//アップデート
	void Update();

	//ドロー
	void Draw();


	
};

