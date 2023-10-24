#include "Title.h"
#include <Novice.h>

void Title::Update(char* keys, char* preKeys, ChangeScene changeScene) {

	if (changeScene.GetIsStart()) {
		if (changeScene.GetStartTimer() == 119) {
			Init();
		}
	}
	//タイマースタート
	if (time_[0] < 300) {
		time_[0]++;
	}
	//スペースを動かす処理
	if (spacetimecount_[4] == 2) {
		for (int i = 0; i < 5; i++) {
			spacetimecount_[i] = 0;
		}
		time_[1] = 0;
		SPACEHit = 0;
	}
	if (SPACEHit == 1) {
		time_[1]++;
	}

	//速度Yに値を与える
	if (time_[0] == 50) {
		for (int i = 0; i < 2; i++) {
			velocity_[i].y = -12.0f;
		}
	}
	if (time_[1] == 1) {
		for (int i = 0; i < 5; i++) {
			spacevelocity_[i].y = -1.7f;
		}
	}

	//スぺースを押すと動く変化
	if (keys[DIK_SPACE]) {
		keysHit = 1;
		SPACEHit = 1;
	}
	else {
		keysHit = 0;
	}


	//------------------------------------------------------//
	//                   スペースバルーン                   //　　
	//------------------------------------------------------//

	//タイマーと設定時間が合ったとき
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			if (time_[0] == jumpcount_[j] && j == i) {
				timecount_[i] = 1;
			}
		}
		//落下処理
		if (timecount_[i] == 1) {
			velocity_[i].y += acceleration_[i].y;
			titlePos_[i].y += velocity_[i].y;
		}
		if (titlePos_[1].y < 25.0) {
			passing = 1;
		}
		//落下を止める処理
		if (titlePos_[i].y > 25.0 && passing == 1) {
			velocity_[i].y = -1.8f;
			acceleration_[i].y = 0.05f;
		}
	}

	//------------------------------------------------------//
	//                       [SPACE]                        //　　
	//------------------------------------------------------//

	
	//タイマーと設定時間が合ったとき
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (time_[1] == spacejumpcount_[j] && j == i) {
				spacetimecount_[i] = 1;
			}
		}
		//落下処理
		if (spacetimecount_[i] == 1) {
			spacevelocity_[i].y += spaceacceleration_[i].y;
			spacePos_[i + 1].y += spacevelocity_[i].y;
		}
		//落下を止める処理
		if (spacePos_[i + 1].y > 540.0f && spacetimecount_[i] == 1) {
			spacePos_[i + 1].y = 540.0f;
			spacetimecount_[i] = 2;
			spacevelocity_[i].y = 0.0f;
		}

	}
	
};


void Title::Draw(ChangeScene changeScene ) {

	Novice::ScreenPrintf(0,100," %d",time_[1]);

	for (int i = 0; i < 2; i++) {
		//----------------------タイトルロゴを表示------------------------//
		if (timecount_[i] == 0) {
			Novice::DrawSprite(
				int(titlePos_[0].x),
				int(titlePos_[0].y) + int(EaseInQuint(changeScene.easeT_) * 720),
				titleResources[0],
				1, 1,
				0.0f,
				0xFFFFFFFF);
			Novice::DrawSprite(
				int(titlePos_[1].x),
				int(titlePos_[1].y) + int(EaseInQuint(changeScene.easeT_) * 720),
				titleResources[1],
				1, 1,
				0.0f,
				0xFFFFFFFF);
		}
		else if (timecount_[i] == 1) {
			Novice::DrawSprite(
				int(titlePos_[0].x),
				int(titlePos_[0].y) + int(EaseInQuint(changeScene.easeT_) * 720),
				titleResources[0],
				1, 1,
				0.0f,
				0xFFFFFFFF);
			Novice::DrawSprite(
				int(titlePos_[1].x),
				int(titlePos_[1].y )+ int(EaseInQuint(changeScene.easeT_) * 720),
				titleResources[1],
				1, 1,
				0.0f,
				0xFFFFFFFF);
		}

	}

	//-------------操作表示--------------//
	for (int i = 0; i < 7; i++) {
		if (i >= 1 && i < 6) {
			if (spacetimecount_[i-1] >= 0 ) {
				Novice::DrawSpriteRect(
					int(spacePos_[i].x),
					int(spacePos_[i].y) + int(EaseInQuint(changeScene.easeT_) * 720), 
					i * 37, 0,
					37, 46,
					titleResources[2],
					(37.0f / 257.0f), (47.0f / 64.0f),
					0.0f,
					0xFFFFFFFF
				);
			}
		}else {
			Novice::DrawSpriteRect(
				int(spacePos_[i].x),
				int(spacePos_[i].y) + int(EaseInQuint(changeScene.easeT_) * 720),
				i * 37, 0,
				37, 46,
				titleResources[2],
				(37.0f / 257.0f), (47.0f / 64.0f),
				0.0f,
				0xFFFFFFFF
			);
		}
		
		if (i >= 1 && i < 6) {
			if (spacetimecount_[i - 1] >= 0 && keysHit == 1) {
				Novice::DrawSpriteRect(
					int(spacePos_[i].x),
					int(spacePos_[i].y) + int(EaseInQuint(changeScene.easeT_) * 720),
					i * 37, 0,
					37, 46,
					titleResources[2],
					(37.0f / 257.0f), (47.0f / 64.0f),
					0.0f,
					0xFFFFFFFF
				);
			}
		}

	}
}

