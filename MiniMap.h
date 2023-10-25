#pragma once
#include "player.h"
class MiniMap{

public:
	float miniMapSize = 4.0f;
	void Draw(GlobalVariable globalV, Scene scene, ChangeScene changeScene, Map map,Player player);

	int miniMapImgs[5] = {
		Novice::LoadTexture("./Resources./Images./game./clock_mini.png"),
		Novice::LoadTexture("./Resources./Images./game./flag_mini.png"),
		Novice::LoadTexture("./Resources./Images./game./lifeBalloon.png"),
		Novice::LoadTexture("./Resources./Images./game./lifeUI.png"),
		Novice::LoadTexture("./Resources./Images./game./tutorial3.png"),
	};
};

