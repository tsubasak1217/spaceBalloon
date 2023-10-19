#include "Title.h"
#include <Novice.h>

void Title::Update() {
	if (time > 230) {
		time = 0;
	}
	time++;
	if (time == 1) {
		for (int i = 0; i < 2; i++) {
			velocity[i].y = -10.0;
		}
	}

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			if (time == jumpcount[j] && j == i) {//タイマーと設定時間が合ったとき
				timecount[i] = 1;
			}
		}
		if (timecount[i] == 1) {
			velocity[i].y += acceleration[i].y;
			titlePos[i].y += velocity[i].y;
		}

		//落下を止める処理

		if (i < 2) {
			if (titlePos[i].y > 300.0) {
				titlePos[i].y = 300.0;
				timecount[i] = 0;
				velocity[i].y = 0.0f;
			}
		}
	
	}
};

void Title::Draw() {

	Novice::ScreenPrintf(0, 215, "time = %d", time);

	for (int i = 0; i < 2; i++) {
		if (timecount[i] == 0) {
			Novice::DrawSprite(
				int(titlePos[0].x),
				int(titlePos[0].y),
				titleResources[0],
				1,1,
				0.0f,
				0xFFFFFFFF);
			Novice::DrawSprite(
				int(titlePos[1].x),
				int(titlePos[1].y),
				titleResources[1],
				1, 1,
				0.0f,
				0xFFFFFFFF);
		}else if (timecount[i] == 1) {
			Novice::DrawSprite(
				int(titlePos[0].x),
				int(titlePos[0].y),
				titleResources[0],
				1, 1,
				0.0f,
				0xFFFFFFFF); 
			Novice::DrawSprite(
				int(titlePos[1].x),
				int(titlePos[1].y),
				titleResources[1],
				1, 1,
				0.0f,
				0xFFFFFFFF);
		}
	}

}


