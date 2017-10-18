#include "Player.h"
#include <iostream>
#include <algorithm>

using namespace std;
using namespace TankWars;

Player::Player()
{
    position_ = Point(0, 0);
}

Player::Player(string tank, const Point& p, string dir) : position_(p), direction_(dir)
{
    selectTank(tank);
}

Tank Player::getTank() const noexcept
{
    return tank_;
}

unsigned int Player::getScore() const noexcept
{
    return score_;
}

Point Player::getPosition() const noexcept
{
    return position_;
}

string Player::getDirection() const noexcept
{
    return direction_;
}

const vector<shared_ptr<Bullet>>& Player::getBullets() const noexcept
{
    return bullets_;
}

unsigned int Player::getEnergy() const noexcept
{
    return energy_;
}

void Player::setScore(unsigned int n) noexcept
{
    score_ = n;
}

void Player::setDirection(string dir)
{
    if (dir == "up" || dir == "down" || dir == "left" || dir == "right")
    {
        direction_ = dir;
    }
    else
    {
        throw invalid_argument("No such direction.");
    }
}

void Player::setBullets(const vector<shared_ptr<Bullet>>& bullets) noexcept
{
    bullets_ = bullets;
}


void Player::selectTank(string tank)
{
    // To lowercase
    transform(tank.begin(), tank.end(), tank.begin(), ::tolower);

    if (tank == "nightmare")
    {
        tank_ = Tank(TankType::NIGHTMARE);
    }
    else if (tank == "warrior")
    {
        tank_ = Tank(TankType::WARRIOR);
    }
    else
    {
        throw invalid_argument("No such tank type.");
    }
}

void Player::move(int x, int y) noexcept
{
    position_ = position_ + Point(x, y);
}

void Player::fire(const Point& p) noexcept
{
    shared_ptr<Bullet> bullet = make_shared<Bullet>(p, direction_);
    bullets_.push_back(bullet);
}

void Player::ult(const Point& p) noexcept
{
    // when the player has enough energy, he can use an ultra
    if (energy_ == 100)
    {
        // set the next bullet to an ultra bullet
        shared_ptr<Bullet> bullet = make_shared<Bullet>(p, direction_, true);
        bullets_.push_back(bullet);
        energy_ = 0;
    }
}

void Player::moveBullets() noexcept
{
    for (auto& b : bullets_)
    {
        b->move(tank_.getMuzzleVelocity());
    }
}

void Player::gainEnergy() noexcept
{
    // keep adding energy
    if (energy_ != 100)
    {
        energy_++;
    }
}
