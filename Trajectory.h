#pragma once
#include "Particle.h"
#include "Player.h"

class Trajectory :
    public Particle
{
public:
    Trajectory(Player player, int lifespan) :Particle(player.GetPos(), lifespan, { player.GetSize().x / 4,player.GetSize().y / 4 }, Color()) {}

    void Update()override;
    void Draw(GlobalVariable globalV)override ;

};