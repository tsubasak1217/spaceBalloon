#pragma once
#include "Particle.h"
#include "Player.h"

class Trajectory :
    public Particle
{
public:
    Trajectory(Vector2 pos_,int lifespan) :Particle(pos_, lifespan){}
    void Update()override;
    void Draw(GlobalVariable globalV)override;
};

