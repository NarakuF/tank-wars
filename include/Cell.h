#ifndef CELL_H
#define CELL_H

#include "Point.h"


namespace TankWars
{

class Player;

/**
 * Represent a cell.
 * Each cell has a position
 * and a boolean represent is this ell is wall or not
 * one setter for set this cell to a all
 * and two getter for the position and isWall
 *
 * @author Guandong Liu, Gefei Tian
 */
class Cell
{
    public:
        /**
         * Construct a cell
         * @param p, the point of this cell at
         * @param isWall, is this cell is wall
         */
        Cell(const Point& p, bool isWall = false);

        /**
         * Setter for isWall
         * @param flag True is the cell is a wall
         * true for is a wall
         */
        void setIsWall(bool flag) noexcept;

        /**
         * Getter for the position
         * @return Point, as the position
         */
        Point getPosition() const noexcept;

        /**
         * Getter for is wall
         * @return true if it is
         */
        bool isWall() const noexcept;

    private:
        /** The position of a cell. */
        Point position_;

        /** The flag to determine if the cell is a wall. */
        bool isWall_;
};
}

#endif // CELL_H
