#pragma once
#include "Particle.h"
#include "Player.h"

class Trajectory :
    public Particle
{
public:


    Trajectory(Player player, int lifespan) :Particle(player.GetPos(), lifespan, { player.GetSize().x / 4,player.GetSize().y / 4 }, color.setCode(0x76fafeff)) {
    }

    void Update()override;
    void Draw(GlobalVariable globalV,Scene scene)override ;

};