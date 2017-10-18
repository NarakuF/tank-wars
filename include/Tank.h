#ifndef TANK_H
#define TANK_H

#include "Point.h"
#include "TankType.h"

namespace TankWars
{

/**
 * The tank of the player controls.
 * The tank has two types, nightmare and warrior.
 * The tank has a speed and a muzzleVelocity
 * there are two getter for those filed
 *
 * @author Guandong Liu, Gefei Tian
 */
class Tank
{
    public:

        /**
         * Construct a tank by default.
         */
        Tank();

        /**
         * Construct a tank with given type.
         * @param type The type of the tank
         */
        Tank(TankType type);

        /**
         * Getter for speed of the tank
         * @return int, the speed of the tank
         */
        int getSpeed() const noexcept;

        /**
         * Getter for the muzzle velocity
         * @return int, the muzzle velocity
         */
        int getMuzzleVelocity() const noexcept;


    private:
        /** The speed of the tank. */
        int speed_;

        /** The muzzle velocity of the tank, how fast the bullet is. */
        int muzzleVelocity_;
};
}

#endif // TANK_H
