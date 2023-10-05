#include "Effect.h"

void Effect::Update(Player player) {
	frameCount_++;
	player.Init();
}
