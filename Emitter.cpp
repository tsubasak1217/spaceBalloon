#include "Emitter.h"
#include "Trajectory.h"
#include "BloodTrajectory.h"

void Emitter::Update(Player &player) {
	pos_ = player.GetPos();
	Color color = Color();
	if (++frameCount >= DeterminedFrame) {
		//動いているときにエフェクトを表示
		if (sqrtf(powf(pos_.x - previousFramePos_.x,2)) >= 2 || sqrtf(powf(pos_.y - previousFramePos_.y,2)) >= 2) {
			if (player.GetIsUnrivaled()) {
				color.setCode(0xff5181ff);
			}
			if (player.GetIsUnrivaled()) {
				particles.push_back(new BloodTrajectory(player, 60));
			}
			else {
				particles.push_back(new Trajectory(player, 60));
			}
			frameCount = 0;
		}
	}

	auto iterator = particles.begin();
	while (iterator != particles.end()) {
		(*iterator)->Update();
		if ((*iterator) -> isAlive()){
			iterator++;
		} else {
			iterator = particles.erase(iterator);
		}
	}
	previousFramePos_ = pos_;
}

void Emitter::Draw(GlobalVariable globalV) {
	auto iterator = particles.begin();
	while (iterator != particles.end())
	{
		(*iterator)->Draw(globalV);
		iterator++;
	}
}
