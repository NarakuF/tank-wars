#include "Point.h"

using namespace std;
using namespace TankWars;

Point::Point() {};

Point::Point(int x, int y) : x_(x), y_(y) {}

Point Point::operator+(Point p) noexcept
{
    Point newP(x_ + p.getX(), y_ + p.getY());
    return newP;
}

bool Point::operator==(Point p) const noexcept
{
    return x_ == p.getX() && y_ == p.getY();
}

Point::getX() const noexcept
{
    return x_;
}

Point::getY() const noexcept
{
    return y_;
}
