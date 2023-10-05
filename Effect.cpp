#include "Effect.h"

void Effect::Update(Player player) {
	//フレーム
	frameCount_++;

	//乱数の初期化
	unsigned int currentTime = time(nullptr);
	srand(currentTime);
	int savePosDigt = 0;

	//座標の保存

	if (frameCount_ % 4 == 0) {
		for (int i = savePosDigit; i < posMax_; i++) {
			savePos_[i] = { player.GetPos.x ,player.GetPos.y };
			for (int j = 0; j < effectMax_; j++) {
				effectPos_[i][j] = { rand() % (savePos_[i] + radius_), rand() % (savePos_[i] + radius_ };
			}
			savePosDigt++;
			if (savePosDigt > 3)
				savePosDigt = 0;
			break;
		}
	}
}

void Effect::Draw() {

	for (inti = 0; i < posMax_; i++) {
		Novice::DrawEllipse(
			int(effectPos_.x),
			int(effectPos_.y * 1.0f),
			20,		//後で変える
			20,		//後で変える
			0.0f,
			WHITE,	//後で変える
			kFillModeSolid
		);
	}

}
