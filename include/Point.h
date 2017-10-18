#ifndef POINT_H
#define POINT_H

namespace TankWars
{

/**
 * A point has x coordinate and y coordinate.
 * two getter to get the x and y
 * two operator to modify the point
 *
 * @author Guandong Liu, Gefei Tian
 */
class Point
{
    public:
        /**
         * Construct a point.
         */
        Point();

        /**
         * Construct a point.
         * @param x The x position
         * @param y The y position
         */
        Point(int x, int y);

        /**
         * Overload the operator+
         * @param Point p the point to add
         * @return Point, the new point
         */
        Point operator+(Point p) noexcept;

        /**
         * Check if two points are the same point
         * @param Point p the point to check
         * @return true if two points are the same
         */
        bool operator==(Point p) const noexcept;

        /** Get the x coordinate of the point. */
        int getX() const noexcept;

        /** Get the y coordinate of the point. */
        int getY() const noexcept;

    private:
        /** The x coordinate of the point. */
        int x_;

        /** The y coordinate of the point. */
        int y_;
};
}

#endif // POINT_H
