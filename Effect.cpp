#include "Effect.h"

void Effect::Update(Player player) {
	//�t���[��
	frameCount_++;

	//�����̏�����
	unsigned int currentTime = time(nullptr);
	srand(currentTime);
	int savePosDigt = 0;

	//���W�̕ۑ�

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
			20,		//��ŕς���
			20,		//��ŕς���
			0.0f,
			WHITE,	//��ŕς���
			kFillModeSolid
		);
	}

}
