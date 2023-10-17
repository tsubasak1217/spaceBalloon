#include "Emitter.h"
#include "Trajectory.h"

void Emitter::Update(Player player, Map map/*,Color* color*/) {

	pos_ = player.GetPos();
	size_ = { player.GetSize().x / 4, player.GetSize().y / 4 };

	if (++frameCount >= DeterminedFrame) {
		particles.push_back(new Trajectory(pos_, 60,size_));
		frameCount = 0;
	}

	auto iterator = particles.begin();
	while (iterator != particles.end()) {
		(*iterator)->Update(player, map);
		if((*iterator) -> isAlive()){
			iterator++;
		} else {
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
