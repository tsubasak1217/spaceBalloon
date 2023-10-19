#pragma once
#include <Vector2.h>
class Title {

private:

	Vector2 Box[12] = {0.0f,0.0f};
	 Vector2 velocity[12] = { 0.0f,0.0f };//速度
  	 Vector2 acceleration[12] = { 0.0f,0.0f };//加速度

	float width[2];
	float vertical[2];
	int atrrk;
	int time;
	int timecount[10] = { 0 };
	int GG[10] = { 0 };
public:
	void Init() {
		time = 0;
		atrrk = 1;
		 width[0] = 100.0f;
		 width[1] = 100.0f;
		 vertical[0] = 200.0f;
		 vertical[1] = 200.0f;

		for (int i = 0; i < 12; i++) {

			if (i < 5) {
				Box[i].x = width[0];
				Box[i].y = vertical[0];
				width[0] += 150;
			}
			if (i >= 5) {
				Box[i].x = width[1];
				Box[i].y = vertical[1];
				width[1] -= 150;
			}
			acceleration[i].y = 0.8f;
		}
	
	};
	
	//アップデート
	void Update();

	//ドロー
	void Draw();


};

