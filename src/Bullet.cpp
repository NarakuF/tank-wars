#include "Bullet.h"

using namespace std;
using namespace TankWars;

Bullet::Bullet(const Point& position, string direction, bool isUlt) :
    position_(position), direction_(direction), isUlt_(isUlt) {}

Bullet::~Bullet() {}

Point Bullet::getPosition() const noexcept
{
    return position_;
}


string Bullet::getDirection() const noexcept
{
    return direction_;
}

bool Bullet::isUlt() const noexcept
{
    return isUlt_;
}

void Bullet::move(int speed)
{
    // Bullet can move towards to four direction
    if (direction_ == "up")
    {
        position_ = position_ +  Point(0, -speed);
    }
    else if (direction_ == "down")
    {
        position_ = position_ +  Point(0, speed);
    }
    else if (direction_ == "left")
    {
        position_ = position_ +  Point(-speed, 0);
    }
    else if (direction_ == "right")
    {
        position_ = position_ +  Point(speed, 0);
    }
    else
    {
        throw invalid_argument("No such direction.");
    }
}
