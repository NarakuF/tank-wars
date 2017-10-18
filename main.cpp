#include <iostream>
#include <stdexcept>
#include <memory>
#include <windows.h>
#include "TankWars.h"
#include "Display.h"

using namespace std;
using namespace TankWars;

/**
 * \namespace TankWars
 * A tank war is a two-player game. Each player can control a tank
 * to fight against other player. The game has two different mode,
 * competitive and deathmatch. In the competitive mode, the player
 * who destroys other player's tank wins the game; In the deathmatch
 * mode, one player earns one point by killing other player, and the
 * player who scores more points in the limited time wins the game.
 *
 * @author Guandong Liu, Gefei Tian
 */

/**
 * Construct a tank war game and start the game by reading the inputs
 */
int main()
{
    string mode;
    shared_ptr<Player> p1;
    shared_ptr<Player> p2;
    shared_ptr<TankWars> game;

    // read the input, if the input is invalid, read again until correct
    while (true)
    {
        try
        {
            cout << "Please select the game mode: competitive or deathmatch" << endl;
            cin >> mode;
            game = make_shared<TankWars>(mode, p1, p2);
            break;
        }
        catch (exception& e)
        {
            cerr << e.what() << endl;
            continue;
        }
    }

    string p1tank;
    while (true)
    {
        try
        {
            cout << "Please select player1's tank: nightmare or warrior" << endl;
            cin >> p1tank;
            p1 = make_shared<Player>(p1tank, Point(1, 1), "right");
            break;
        }
        catch (exception& e)
        {
            cerr << e.what() << endl;
            continue;
        }
    }

    string p2tank;
    while (true)
    {
        try
        {
            cout << "Please select player2's tank: nightmare or warrior" << endl;
            cin >> p2tank;
            p2 = make_shared<Player>(p2tank, Point(31, 1), "left");
            break;
        }
        catch (exception& e)
        {
            cerr << e.what() << endl;
            continue;
        }
    }

    try
    {
        game = make_shared<TankWars>(mode, p1, p2);

        // Initialize the graphical display
        Display display(game);

        // Add some images to the display
        display.addImage("image/wall.bmp"); // 0
        display.addImage("image/grass.bmp"); // 1

        display.addImage("image/p1tankU.bmp"); // 2
        display.addImage("image/p1tankD.bmp"); // 3
        display.addImage("image/p1tankL.bmp"); // 4
        display.addImage("image/p1tankR.bmp"); // 5

        display.addImage("image/p2tankU.bmp"); // 6
        display.addImage("image/p2tankD.bmp"); // 7
        display.addImage("image/p2tankL.bmp"); // 5
        display.addImage("image/p2tankR.bmp"); // 9

        display.addImage("image/tankbullet.bmp"); // 10
        display.addImage("image/bomb.bmp"); // 11

        display.addImage("image/gameover.bmp"); // 12

        // Run until quit.
        for (;;)
        {
            // Check all pending requests.
            for (;;)
            {
                shared_ptr<Request> request = display.getNextRequest();
                if (!request)
                {
                    break;
                }
                if (request->shouldQuit())
                {
                    // Request to close the window
                    cout << "User closed the window" << endl;
                    return 0;
                }
                else if (request->pressedButton())
                {
                    // Pressed the left mouse button
                    cout << "Mouse button was pressed" << request->xPosition() << " " << request->yPosition()<< endl;
                }
                else if (request->releasedButton())
                {
                    // Released the left mouse button
                    cout << "Mouse button was released" << request->xPosition() << " " << request->yPosition()<< endl;
                }
            }
            display.refresh();
        }
    }
    catch (const exception& e)
    {
        cerr << e.what() << endl;
        return 1;
    }

    return 0;
}
