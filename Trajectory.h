#pragma once
#include "Particle.h"
#include "Player.h"

class Trajectory :
    public Particle
{
private:
    float size = 6;
    Trajectory(Vector2 pos_, int lifespan) :Particle(pos_, lifespan) {}

public:
    Trajectory(Vector2 pos_, int lifespan,float size) :Particle(pos_, lifespan),size(size){}

    void Update()override;
    void Draw(GlobalVariable globalV)override;

};

