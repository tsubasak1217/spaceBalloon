#pragma once
#include "Particle.h"
#include "Player.h"

class Trajectory :
    public Particle
{
private:

public:
   Trajectory(Vector2 pos_, int lifespan,Vector2 retainSize) :Particle(pos_, lifespan,retainSize) {}
    void Update()override;
    void Draw(GlobalVariable globalV)override;

};

