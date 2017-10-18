#ifndef TANKTYPE_H
#define TANKTYPE_H

namespace TankWars
{

/**
 * The tank has two types, nightmare and warrior.
 *
 * @author Guandong Liu, Gefei Tian
 */
enum class TankType
{
    /** Nightmare tank has faster speed but slower attack speed. */
    NIGHTMARE,

    /** Warrior tank has slower speed but faster attack speed. */
    WARRIOR
};
}

#endif // TANKTYPE_H
