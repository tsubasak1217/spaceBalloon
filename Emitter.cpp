#include "Emitter.h"
#include "Trajectory.h"

void Emitter::Update(Player player, Map map) {
	pos_ = player.GetPos();
	size_ = player.GetSize() / 4;
	

	if (++frameCount >= DeterminedFrame) {
		//動いているときにエフェクトを表示
		if (sqrtf(powf(pos_.x - previousFramePos_.x,2)) >= 2 || sqrtf(powf(pos_.y - previousFramePos_.y,2)) >= 2) {
			particles.push_back(new Trajectory(pos_, 60, size_));
			frameCount = 0;
		}
	}

	auto iterator = particles.begin();
	while (iterator != particles.end()) {
		(*iterator)->Update(map);
		if ((*iterator) -> isAlive()){
			iterator++;
		} else {
			iterator = particles.erase(iterator);
		}
	}

	previousFramePos_ = pos_;

	/* デバック */
	Novice::ScreenPrintf(100, 80, "%f,%f", player.GetPos().x, player.GetPos().y);
	Novice::ScreenPrintf(100, 100, "%f,%f", previousFramePos_.x,previousFramePos_.y);
	Novice::ScreenPrintf(100, 120, "%f,%f", player.GetVelocity().x, player.GetVelocity().y);
}

void Emitter::Draw(GlobalVariable globalV) {
	auto iterator = particles.begin();
	while (iterator != particles.end())
	{
		(*iterator)->Draw(globalV);
		iterator++;
	}
}
