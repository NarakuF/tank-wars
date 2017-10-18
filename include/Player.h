#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include <stdexcept>
#include <memory>
#include "Bullet.h"
#include "Tank.h"

namespace TankWars
{

/**
 * The player of the tank war game.
 * A player has score, position, tank and bullets.
 *
 * @author Guandong Liu, Gefei Tian
 */
class Player
{
    public:

        /**
         * Construct a player.
         */
        Player();

        /**
         * Construct a player.
         * @param tank The tank of the player control
         * @param p The position of the player
         */
        Player(std::string tank, const Point& p, std::string dir);

        /**
         * Getter for the tank
         * @return the tank of the player
         */
        Tank getTank() const noexcept;

        /**
         * Getter for the score of the player.
         * @return the score of the player
         */
        unsigned int getScore() const noexcept;

        /**
         * Getter for the position of the player.
         * @return the position of the player
         */
        Point getPosition() const noexcept;

        /**
         * Getter for the direction
         * @return the direction
         */
        std::string getDirection() const noexcept;

        /**
         * Getter for all the bullets
         * @return all bullets
         */
        const std::vector<std::shared_ptr<Bullet>>& getBullets() const noexcept;

        /**
         * Getter for the energy
         * @return int, as the energy
         */
        unsigned int getEnergy() const noexcept;

        /**
         * Set the player score
         * @param unsigned int n, as player's score
         */
        void setScore(unsigned int n) noexcept;

        /**
         * Set the move direction
         * @param string dir, as he direction
         */
        void setDirection(std::string dir);

        /**
         * Setter for all bullets
         * @param bullets, as all the bullets
         */
        void setBullets(const std::vector<std::shared_ptr<Bullet>>& bullets) noexcept;



        /**
         * Select the type of the tank.
         * @param tank The type of the tank
         * @throw invalid_argument if there is no such tank type
         */
        void selectTank(std::string tank);

        /**
         * Move the position.
         * @param x The x position
         * @param y The y position
         */
        void move(int x, int y) noexcept;

        /**
         * The player control the tank to fire.
         * @param p The position where the player fires
         */
        void fire(const Point& p) noexcept;

        /**
         * Player control the tank to use ult
         * @param p The position where the player uses ult
         */
        void ult(const Point& p) noexcept;

        /**
         * The movement of the bullets
         */
        void moveBullets() noexcept;

        /**
         * The energy player gained
         */
        void gainEnergy() noexcept;

    protected:

    private:
        /** The tank of the player. */
        Tank tank_;

        /** The score of the player in a game. */
        unsigned int score_ = 0;

        /** The position of the player. */
        Point position_;

        /** The direction of the player faces. */
        std::string direction_;

        /** The bullets of the player shoots. */
        std::vector<std::shared_ptr<Bullet>> bullets_;

        /** The energy that player has */
        unsigned int energy_ = 0;
};
}

#endif // PLAYER_H
