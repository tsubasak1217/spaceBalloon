#pragma once
#include <time.h>
#include <stdio.h>
\#include <Vector2.h>
#include "Player.h"

class Effect{
	private:
		static const int posMax_ = 4;
		static const int effectMax_ = 5;

		int frameCount_;
		
		Vector2 savePos_[posMax_];
		Vector2 effectPos_[posMax][effectMax_];
		float radius_;

	public:
		void Init(Player player) {
			frameCount_ = 0;
			for (int i = 0; i < posMax; i++) {
				savePos_[i] = { 0.0f,0.0f };
				for (int j = 0; j < effectMax; j++) {
					effectPos[i][j] = { 0.0f,0.0f };
				}
			}
			radius = player.GetSize().x / 3.0f;
		}

		//アップデート
		void Update(Player player);
};

