#pragma once
#include "Particle.h"
#include "Player.h"

class Trajectory :
    public Particle
{
public:
    Trajectory(Vector2 pos_, int lifespan,Vector2 retainSize) :Particle(pos_, lifespan,retainSize) {}

    void Update(Player player, Map map)override;
    void Draw(GlobalVariable globalV)override;

};

