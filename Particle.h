#pragma once
#include <Vector2.h>
#include <GlobalVariable.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>
#include <Color.hpp>
#include "Player.h"

class Particle
{
protected:
	Vector2 location;
	Vector2 vector;
	int lifespan;	//フレーム数
	Color* color;
	Vector2 retainSize;

public:
	Particle(Vector2 pos, int lifespan, Vector2 retainSize) :location(pos), lifespan(lifespan), retainSize(retainSize), vector(Vector2()), color(new Color()) {
		vector.x = sinf((rand() % 360) * (float(M_PI) / 180.f));
		vector.y = cosf((rand() % 360) * (float(M_PI) / 180.f));
	}
	virtual void Update(Map map) = 0;
	virtual void Draw(GlobalVariable globalV) = 0;
	bool isAlive() {		  
		return lifespan >= 0;
	}
};

