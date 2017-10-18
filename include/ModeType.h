#ifndef MODETYPE_H
#define MODETYPE_H

namespace TankWars
{

/**
 * The mode has two types, competitive and deathmatch.
 *
 * @author Guandong Liu, Gefei Tian
 */
enum class ModeType
{
    /** The player who destroys other player's tank wins the game. */
    COMPETITIVE,

    /** The player who gets more points in the limited time wins the game. */
    DEATHMATCH
};
}

#endif // MODETYPE_H
