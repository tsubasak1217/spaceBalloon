#include "Emitter.h"
#include "Trajectory.h"

void Emitter::Update(Player player) {
	pos_ = player.GetPos();
	if (++frameCount >= DeterminedFrame) {
		particles.push_back(new Trajectory(pos_,60));
		frameCount = 0;
	}
	auto iterator = particles.begin();
	while (iterator != particles.end()) {
		(*iterator)->Update();
		if ((*iterator)->isAlive()) {
			iterator++;
		}
		else {
			iterator = particles.erase(iterator);
		}
	}

}

void Emitter::Draw(GlobalVariable globalV) {
	auto iterator = particles.begin();
	while (iterator != particles.end())
	{
		(*iterator)->Draw(globalV);
		iterator++;
	}
}
