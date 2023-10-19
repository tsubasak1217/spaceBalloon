#include "Title.h"
#include <Novice.h>


void Title::Update() {


	if (atrrk == 1) {
		time++;
		if (time > 160) {
			time = 0;
		}
		if (time == 1) {
			for (int i = 0; i < 12; i++) {
				velocity[i].y = -18.0;

			}
		}

		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {

				if (time > 150) {
					timecount[j] = 0;
				}

				if (time == GG[j] && j == i) {
					timecount[i] = 1;
				}
			}


			if (timecount[i] == 1) {
				if (i >= 5 && i < 7 || i >= 8 && i < 12) {
					velocity[i].x += acceleration[i].x;
					Box[i].x += velocity[i].x;
				}
				velocity[i].y += acceleration[i].y;
				Box[i].y += velocity[i].y;
			}

			if (i < 5) {
				if (Box[i].y > 500.0) {
					Box[i].y = 500.0;
					timecount[i] = 0;
					velocity[i].y = 0.0f;
					velocity[i].x = 0.0f;
				}
			}
			if (i >= 5) {
				if (Box[i].y > 200.0) {
					Box[i].y = 200.0;
					timecount[i] = 0;
					velocity[i].y = 0.0f;
					velocity[i].x = 0.0f;
				}
			}
		}
	}



};

void Title::Draw() {


	for (int i = 0; i < 12; i++) {
		if (timecount[i] == 0) {
			Novice::DrawBox(
				int(Box[i].x),
				int(Box[i].y),
				100,100,
				0.0f,
				0x008000FF,
				kFillModeSolid);
		}
		else if (timecount[i] == 1) {
			Novice::DrawBox(
				int(Box[i].x),
				int(Box[i].y),
				100,100,
				0.0f,
				RED, 
				kFillModeSolid);
		}
	}

}


