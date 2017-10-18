
#include "Tank.h"

using namespace std;
using namespace TankWars;

Tank::Tank() {}

Tank::Tank(TankType type)
{
    switch (type)
    {
    case TankType::NIGHTMARE:
        speed_ = 3;
        muzzleVelocity_ = 1;
        break;
    case TankType::WARRIOR:
        speed_ = 1;
        muzzleVelocity_ = 2;
        break;
    default:
        speed_ = 0;
        break;
    }
}

int Tank::getSpeed() const noexcept
{
    return speed_;
}

int Tank::getMuzzleVelocity() const noexcept
{
    return muzzleVelocity_;
}
