#include "Title.h"
#include <Novice.h>

void Title::Update() {
		if (time > 200) {
			time = 0;
		}
		time++;
		if (time <= 4) {
			for (int i = 0; i < 12; i++) {
				velocity_[i].y = -8.0;
			}
		}

		for (int i = 0; i < 12; i++) {
			for (int j = 0; j < 12; j++){
				if (time == jumpcount_[j] && j == i) {//タイマーと設定時間が合ったとき
					timecount[i] = 1;
				}
			}
			if (timecount[i] == 1) {
				velocity_[i].y += acceleration_[i].y;
				titlePos_[i].y += velocity_[i].y;
			}
			
			//落下を止める処理
			
				if (i < 5) {
					if (titlePos_[i].y > 300.0) {
						titlePos_[i].y = 300.0;
						timecount[i] = 0;
						velocity_[i].y = 0.0f;
					}
				}
				else if (i >= 5) {
					if (titlePos_[i].y > 500.0) {
						titlePos_[i].y = 500.0;
						timecount[i] = 0;
						velocity_[i].y = 0.0f;
					}
				}
		}
};

void Title::Draw() {
	
	Novice::ScreenPrintf(0,215,"time = %d", time);

	for (int i = 0; i < 12; i++) {
		if (timecount[i] == 0) {
			Novice::DrawBox(
				int(titlePos_[i].x),
				int(titlePos_[i].y),
				50,50,
				0.0f,
				GREEN,
				kFillModeSolid);
		}
		else if (timecount[i] == 1) {
			Novice::DrawBox(
				int(titlePos_[i].x),
				int(titlePos_[i].y),
				50,50,
				0.0f,
				RED, 
				kFillModeSolid);
		}
	}

}


