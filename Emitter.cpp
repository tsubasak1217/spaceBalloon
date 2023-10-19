#include "Emitter.h"
#include "Trajectory.h"

void Emitter::Update(Player player, Map map, Color color) {
	pos_ = player.GetPos();
	size_ = {player.GetSize().x / 4,player.GetSize().y / 4 };
	
	if (++frameCount >= DeterminedFrame) {
		//動いているときにエフェクトを表示
		if (sqrtf(powf(pos_.x - previousFramePos_.x,2)) >= 2 || sqrtf(powf(pos_.y - previousFramePos_.y,2)) >= 2) {
			if (player.GetIsUnrivaled()) {
				color.setCode(0xff5181ff);
			}
			else {
				color.setCode(WHITE);
			}
			particles.push_back(new Trajectory(pos_, 60, size_,color));
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
}

void Emitter::Draw(GlobalVariable globalV) {
	auto iterator = particles.begin();
	while (iterator != particles.end())
	{
		(*iterator)->Draw(globalV);
		iterator++;
	}
}
