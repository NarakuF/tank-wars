#ifndef BULLET_H
#define BULLET_H

#include "string"
#include "stdexcept"
#include <Point.h>
#include <Cell.h>

namespace TankWars
{
/**
 * Bullet class represent a bullet.
 * The bullet can has a position, direction
 * and a boolean to represent is this an ultimate bullet
 * three public method as a getters
 * one public method to move the bullet.
 *
 * @author Guandong Liu, Gefei Tian
 */
class Bullet
{
    public:
        /**
         * The constructor for Bullet
         * @param position The position of this bullet
         * @param direction The direction for this bullet
         * @bool isUlt, is this bullet is an ultimate
         */
        Bullet(const Point& position, std::string direction, bool isUlt = false);

        /**
         * the destructor
         */
        virtual ~Bullet();

        /**
         * Getter for the position
         * @return Point, as the position
         */
        Point getPosition() const noexcept;

        /**
         * Getter for the direction
         * @return string, the direction
         */
        std::string getDirection() const noexcept;

        /**
         * Getter for isUlt
         * @return true if this is an ultimate
         */
        bool isUlt() const noexcept;

        /**
         * The movement of this bullet
         * @param int, as the speed for this bullet
         */
        void move(int speed);

    protected:

    private:
        /** The position of this bullet */
        Point position_;

        /** The direction of this bullet */
        std::string direction_;

        /** If this bullet is an ultimate */
        bool isUlt_;
};
}

#endif // BULLET_H
