#ifndef TankWars_H
#define TankWars_H

#include <memory>
#include <vector>
#include "Cell.h"
#include "Tank.h"
#include "Player.h"
#include "ModeType.h"

namespace TankWars
{

/**
 * The tank war game, Having all the information of the game.
 *
 * @author Guandong Liu, Gefei Tian
 */
class TankWars
{
    public:
        /**
         * Construct a TankWars game.
         */
        TankWars();

        /**
         * The constructor for the TankWars.
         * @param mode The mode of the game
         * @param p1 The first player
         * @param p2 The second player
         */
        TankWars(const std::string& mode, std::shared_ptr<Player> p1, std::shared_ptr<Player> p2);

        /**
         * Destruct a TankWars game.
         */
        ~TankWars();

        /**
         * Getter for the time.
         * @return int, the time
         */
        int getTime() const noexcept;

        /**
         * Getter for the map.
         * @return the map of the game
         */
        std::vector<std::shared_ptr<Cell>> getMap() const noexcept;

        /**
         * Getter for the player1
         * @return the player 1
         */
        std::shared_ptr<Player> getPlayer1() const noexcept;

        /**
         * Getter for the player2
         * @return the player 2
         */
        std::shared_ptr<Player> getPlayer2() const noexcept;

        /**
         * Getter for the winner
         * @return the winner
         */
        std::string getWinner() const noexcept;

        /**
         * Set the game time.
         * @param n The time of the game
         */
        void setTime(unsigned int n) noexcept;

        /**
         * Let player select the game mode
         */
        void selectMode(std::string mode);

        /**
         * Generate the map of the game.
         */
        void generateMap() noexcept;

        /**
         * Move the player
         * @param p The player to move
         * @param target The target of the player
         * @param dir The direction to move
         */
        void movePlayer(std::shared_ptr<Player> p, std::shared_ptr<Player> target, std::string dir);

        /**
         * Player's fire
         * @param p The player to fire
         * @param target The target of the player
         */
        void fire(std::shared_ptr<Player> p, std::shared_ptr<Player> target) noexcept;

        /**
         * Player's ult
         * @param p The player to ult
         * @param target The target of the player
         */
        void ult(std::shared_ptr<Player> p, std::shared_ptr<Player> target) noexcept;

        /**
         * Move the player's bullets
         * @param p The player to move
         * @param target The target of the player
         */
        void moveBullets(std::shared_ptr<Player> p, std::shared_ptr<Player> target) noexcept;

        /**
         * Check if the bullets hit anything
         * @param p The player to check
         * @param target The target of the player
         */
        void checkBullets(std::shared_ptr<Player> p, std::shared_ptr<Player> target) noexcept;

        /**
         * Check if two tank hit each other by checking if two cells are overlapped.
         * @param p1 The first point
         * @param p2 The first point
         * @return true if if they hit each other
         */
        bool crash(const Point& p1, const Point& p2) const noexcept;

        /**
         * Determine if the game is end.
         * @return True if the game is end, otherwise false
         */
        bool isEnd() noexcept;

    private:
        /** The mode of the game. */
        ModeType mode_;

        /** The time of the game. */
        unsigned int time_;

        /** The size of the map. */
        const int size_ = 33;

        /** The map of the game. */
        std::vector<std::shared_ptr<Cell>> map_;

        /** The first player of the game. */
        std::shared_ptr<Player> p1_;

        /** The second player of the game. */
        std::shared_ptr<Player> p2_;

        /** The winner of the game. */
        std::string winner_;

        /**
         * Find the needed cell in the map
         * @return p, represent needed cell
         */
        std::shared_ptr<Cell> findCell(const Point& p) const noexcept;
};
}

#endif // TankWars_H
