﻿#pragma once
#include <Vector2.h>
#include "Player.h"
#include <vector>

class Particle;

class Emitter{
	private:
		//初期化
		static const int EffectMax = 5;
		static const int DeterminedFrame = 6;
		int frameCount;
		Vector2 pos_;
		std::vector<Particle*> particles;

	public:
		Emitter() {
			frameCount = 0;
			pos_ = { 0,0 };
			particles.clear();
		};

		//アップデート
		void Update(Player player);

		//ドロー
		void Draw(GlobalVariable globalV);
};
