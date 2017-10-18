#include "TankWars.h"
#include <algorithm>
#include <iostream>
#include <memory>

using namespace std;
using namespace TankWars;

TankWars::TankWars() {}

TankWars::TankWars(const string& mode, shared_ptr<Player> p1, shared_ptr<Player> p2) : p1_(p1), p2_(p2)
{
    selectMode(mode);
    generateMap();
    if (mode_ == ModeType::COMPETITIVE)
    {
        time_ = 1000;
    }
    else
    {
        time_ = 10000;
    }
    winner_ = "Game is not end, no winner";
}

TankWars::~TankWars()
{
}

int TankWars::getTime() const noexcept
{
    return time_;
}

vector<shared_ptr<Cell>> TankWars::getMap() const noexcept
{
    return map_;
}

shared_ptr<Player> TankWars::getPlayer1() const noexcept
{
    return p1_;
}

shared_ptr<Player> TankWars::getPlayer2() const noexcept
{
    return p2_;
}

string TankWars::getWinner() const noexcept
{
    return winner_;
}

void TankWars::setTime(unsigned int n) noexcept
{
    time_ = n;
}

void TankWars::selectMode(std::string mode)
{
    // choose between competitive and death match
    transform(mode.begin(), mode.end(), mode.begin(), ::tolower);
    if (mode == "competitive")
    {
        mode_ = ModeType::COMPETITIVE;
    }
    else if (mode == "deathmatch")
    {
        mode_ = ModeType::DEATHMATCH;
    }
    else
    {
        throw invalid_argument("No such mode type.");
    }
}

// create the map
void TankWars::generateMap() noexcept
{
    bool flag = false;
    int length = (size_ - 15) / 2;

    for (int x = 0; x < size_; ++x)
    {
        for (int y = 0; y < 3; ++y)
        {
            Point p(x, y);
            map_.push_back(make_shared<Cell>(p));
        }
    }

    for (int x = 0; x < size_; ++x)
    {
        for (int y = 0; y < length; ++y)
        {
            Point p(x, y + 3);
            map_.push_back(make_shared<Cell>(p, flag));
        }
        if ((x + 1) % 3 == 0)
        {
            flag = !flag;
        }
    }

    for (int x = 0; x < size_; ++x)
    {
        for (int y = 0; y < 3; ++y)
        {
            Point p(x, length + y + 3);
            map_.push_back(make_shared<Cell>(p));
        }
    }

    flag = true;
    for (int x = 0; x < size_; ++x)
    {
        for (int y = 0; y < 3; ++y)
        {
            Point p(x, length + y + 6);
            map_.push_back(make_shared<Cell>(p, flag));
        }
        if ((x + 4) % 12 == 0)
        {
            flag = false;
        }
        else if ((x + 1) % 12 == 0)
        {
            flag = true;
        }
    }

    for (int x = 0; x < size_; ++x)
    {
        for (int y = 0; y < 3; ++y)
        {
            Point p(x, length + y + 9);
            map_.push_back(make_shared<Cell>(p));
        }
    }

    flag = false;
    for (int x = 0; x < size_; ++x)
    {
        for (int y = 0; y < length; ++y)
        {
            Point p(x, y + length + 12);
            map_.push_back(make_shared<Cell>(p, flag));
        }
        if ((x + 1) % 3 == 0)
        {
            flag = !flag;
        }
    }

    for (int x = 0; x < size_; ++x)
    {
        for (int y = 0; y < 3; ++y)
        {
            Point p(x, size_ + y - 3);
            map_.push_back(make_shared<Cell>(p));
        }
    }
}

void TankWars::movePlayer(shared_ptr<Player> p, shared_ptr<Player> target, string dir)
{
    // move the player if the player won't have crash
    if (dir == "up")
    {
        p->setDirection(dir);
        if (findCell(p->getPosition() + Point(0, -p->getTank().getSpeed() - 1)) &&
                !findCell(p->getPosition() + Point(0, -p->getTank().getSpeed() - 1))->isWall() &&
                !findCell(p->getPosition() + Point(1, -p->getTank().getSpeed() - 1))->isWall() &&
                !findCell(p->getPosition() + Point(-1, -p->getTank().getSpeed() - 1))->isWall() &&
                !crash(p->getPosition() + Point(0, -p->getTank().getSpeed()), target->getPosition()))
        {
            p->move(0, -p->getTank().getSpeed());
        }
    }
    else if (dir == "down")
    {
        p->setDirection(dir);
        if (findCell(p->getPosition() + Point(0, p->getTank().getSpeed() + 1)) &&
                !findCell(p->getPosition() + Point(0, p->getTank().getSpeed() + 1))->isWall() &&
                !findCell(p->getPosition() + Point(1, p->getTank().getSpeed() + 1))->isWall() &&
                !findCell(p->getPosition() + Point(-1, p->getTank().getSpeed() + 1))->isWall() &&
                !crash(p->getPosition() + Point(0, p->getTank().getSpeed()), target->getPosition()))
        {
            p->move(0, p->getTank().getSpeed());
        }
    }
    else if (dir == "left")
    {
        p->setDirection(dir);
        if (findCell(p->getPosition() + Point(-p->getTank().getSpeed() - 1, 0)) &&
                !findCell(p->getPosition() + Point(-p->getTank().getSpeed() - 1, 0))->isWall() &&
                !findCell(p->getPosition() + Point(-p->getTank().getSpeed() - 1, 1))->isWall() &&
                !findCell(p->getPosition() + Point(-p->getTank().getSpeed() - 1, -1))->isWall() &&
                !crash(p->getPosition() + Point(-p->getTank().getSpeed(), 0), target->getPosition()))
        {
            p->move(-p->getTank().getSpeed(), 0);
        }
    }
    else if (dir == "right")
    {
        p->setDirection(dir);
        if (findCell(p->getPosition() + Point(p->getTank().getSpeed() + 1, 0)) &&
                !findCell(p->getPosition() + Point(p->getTank().getSpeed() + 1, 0))->isWall() &&
                !findCell(p->getPosition() + Point(p->getTank().getSpeed() + 1, 1))->isWall() &&
                !findCell(p->getPosition() + Point(p->getTank().getSpeed() + 1, -1))->isWall() &&
                !crash(p->getPosition() + Point(p->getTank().getSpeed(), 0), target->getPosition()))
        {
            p->move(p->getTank().getSpeed(), 0);
        }
    }
    else
    {
        throw invalid_argument("No such direction.");
    }
}

void TankWars::fire(shared_ptr<Player> p, shared_ptr<Player> target) noexcept
{
    // fire a bullet to a direction
    if (p->getDirection() == "up")
    {
        p->fire(p->getPosition() + Point(0, -2));
    }
    else if (p->getDirection() == "down")
    {
        p->fire(p->getPosition() + Point(0, 2));
    }
    else if (p->getDirection() == "left")
    {
        p->fire(p->getPosition() + Point(-2, 0));
    }
    else if (p->getDirection() == "right")
    {
        p->fire(p->getPosition() + Point(2, 0));
    }
    checkBullets(p, target);
}

void TankWars::ult(shared_ptr<Player> p, shared_ptr<Player> target) noexcept
{
    // fire a ultimate bullet to a direction
    if (p->getDirection() == "up")
    {
        p->ult(p->getPosition() + Point(0, -2));
    }
    else if (p->getDirection() == "down")
    {
        p->ult(p->getPosition() + Point(0, 2));
    }
    else if (p->getDirection() == "left")
    {
        p->ult(p->getPosition() + Point(-2, 0));
    }
    else if (p->getDirection() == "right")
    {
        p->ult(p->getPosition() + Point(2, 0));
    }
    checkBullets(p, target);
}

void TankWars::moveBullets(shared_ptr<Player> p, shared_ptr<Player> target) noexcept
{
    p->moveBullets();

    // check bullets
    checkBullets(p, target);
}

void TankWars::checkBullets(shared_ptr<Player> p, shared_ptr<Player> target) noexcept
{
    vector<shared_ptr<Bullet>> bullets = p->getBullets();

    // check each bullet
    for (auto iter = bullets.begin(); iter != bullets.end(); ++iter)
    {
        if (!findCell((*iter)->getPosition()) || (findCell((*iter)->getPosition())->isWall() && !(*iter)->isUlt()))
        {
            bullets.erase(iter);
            p->setBullets(bullets);
        }
        else if ((*iter)->getPosition().getX() >= target->getPosition().getX() - 1 &&
                 (*iter)->getPosition().getX() <= target->getPosition().getX() + 1 &&
                 (*iter)->getPosition().getY() >= target->getPosition().getY() - 1 &&
                 (*iter)->getPosition().getY() <= target->getPosition().getY() + 1)
        {
            if ((*iter)->isUlt())
            {
                p->setScore(p->getScore() + 5);
            }
            else
            {
                p->setScore(p->getScore() + 1);
            }
            bullets.erase(iter);
            p->setBullets(bullets);
        }
        if (iter == bullets.end())
        {
            break;
        }
    }
}

bool TankWars::crash(const Point& p1, const Point& p2) const noexcept
{
    return p1.getX() >= p2.getX() - 2 &&
           p1.getX() <= p2.getX() + 2 &&
           p1.getY() >= p2.getY() - 2 &&
           p1.getY() <= p2.getY() + 2;
}

bool TankWars::isEnd() noexcept
{
    if (mode_ == ModeType::COMPETITIVE)
    {
        if (p1_->getScore() == 1)
        {
            winner_ = "Player 1 wins";
            return true;
        }
        else if (p2_->getScore() == 1)
        {
            winner_ = "Player 2 wins";
            return true;
        }
        else
        {
            winner_ = "Draw, no winner";
            return time_ == 0;
        }
    }
    else
    {
        if (time_ != 0)
        {
            return false;
        }
        else
        {
            if (p1_->getScore() > p2_->getScore())
            {
                winner_ = "Player 1 wins";
            }
            else if (p1_->getScore() < p2_->getScore())
            {
                winner_ = "Player 2 wins";
            }
            else
            {
                winner_ = "Draw, no winner";
            }
            return true;
        }
    }
}

shared_ptr<Cell> TankWars::findCell(const Point& p) const noexcept
{
    for (auto& c : map_)
    {
        if (c->getPosition() == p)
        {
            return c;
        }
    }
    return shared_ptr<Cell>();
}
