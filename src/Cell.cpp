#include "Cell.h"

using namespace std;
using namespace TankWars;

Cell::Cell(const Point& p, bool isWall) : position_(p), isWall_(isWall) {}

void Cell::setIsWall(bool flag) noexcept
{
    isWall_ = flag;
}

Point Cell::getPosition() const noexcept
{
    return position_;
}

bool Cell::isWall() const noexcept
{
    return isWall_;
}
