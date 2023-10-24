#pragma once
#include "Trajectory.h"
class BloodTrajectory :
    public Trajectory
{
private:
    float theta;
public:
    BloodTrajectory(Player player, int ls) :Trajectory(player, ls), theta(0) {
        color.setCode(PINK);
    }
    void Draw(GlobalVariable globalV,Scene scene)override;
};

