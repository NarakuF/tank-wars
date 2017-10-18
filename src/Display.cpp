#include <SDL2/SDL.h>
#include <stdexcept>
#include <iostream>
#include <memory>

#include "Display.h"
#include "TankWars.h"
#include "QuitRequest.h"
#include "ButtonRequest.h"

using namespace std;
using namespace TankWars;

Display::Display(shared_ptr<TankWars> TankWars, int width, int height)
    : TankWars_(TankWars), width_(width), height_(height)
{
    p1dir_ = dirToInt(1, TankWars_->getPlayer1()->getDirection());

    p2dir_ = dirToInt(2, TankWars_->getPlayer2()->getDirection());

    // Initialize SDL2
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        throw domain_error(string("SDL Initialization failed due to: ") + SDL_GetError());
    }

    // Construct the screen window
    setTitle();
    window_ = SDL_CreateWindow(title_.c_str(), SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED,
                               width_, height_, SDL_WINDOW_SHOWN);
    if (!window_)
    {
        close();
        throw domain_error(string("Unable to create the window due to: ") + SDL_GetError());
    }

    // Construct the renderer
    renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer_)
    {
        close();
        throw domain_error(string("Unable to create the renderer due to: ") + SDL_GetError());
    }

    // Clear the window
    clearBackground();
}

Display::~Display()
{
    close();
}

void Display::close() noexcept
{

    // Delete the SDL2 resources in reverse order of
    // their construction, starting with the images
    for (SDL_Texture* image : images_)
    {
        if (image)
        {
            SDL_DestroyTexture(image);
        }
    }

    // Clear the collection of images to ensure
    // idempotence
    images_.clear();

    // Destroy the renderer and window, and set the
    // variables to nullptr to ensure idempotence
    if (renderer_)
    {
        SDL_DestroyRenderer(renderer_);
        renderer_ = nullptr;
    }
    if (window_)
    {
        SDL_DestroyWindow(window_);
        window_ = nullptr;
    }

    // The last step is to quit SDL
    SDL_Quit();
}

void Display::setTitle() noexcept
{
    title_ = string("Tank War: Time: ") + to_string(TankWars_->getTime())
             + ". P1 scores: " + to_string(TankWars_->getPlayer1()->getScore())
             + ". P1 energy: " + to_string(TankWars_->getPlayer1()->getEnergy()) + "%"
             + ". P2 scores: " + to_string(TankWars_->getPlayer2()->getScore())
             + ". P2 energy: " + to_string(TankWars_->getPlayer2()->getEnergy()) + "%"
             + ". Winner: " + TankWars_->getWinner();
}

void Display::addImage(const string& fileLocation) noexcept
{
    if (renderer_)
    {
        // Load the image from the file
        SDL_Surface* imageSurface = SDL_LoadBMP(fileLocation.c_str());
        if (imageSurface)
        {
            // Convert the image to a texture
            SDL_Texture* imageTexture =
                SDL_CreateTextureFromSurface(renderer_, imageSurface);
            if (imageTexture)
            {
                // Add the image to the collection
                images_.push_back(imageTexture);
            }
            else
            {
                cerr << "Unable to load the image file at " << fileLocation
                     << " due to: " << SDL_GetError() << endl;
            }

            // The surface is not longer needed
            SDL_FreeSurface(imageSurface);
        }
        else
        {
            cerr << "Unable to load the image file at " << fileLocation
                 << " due to: " << SDL_GetError() << endl;
        }
    }
}

shared_ptr<Request> Display::getNextRequest() noexcept
{

    // Remove one event from the queue
    SDL_Event event;

    while (SDL_PollEvent(&event) != 0)
    {
        // The type determines what kind of request occurred
        switch (event.type)
        {
        // The user Xed out the window
        case SDL_QUIT:
            close();
            return make_shared<QuitRequest>();

        // The user pressed a mouse button
        case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                title_ = "Mouse button was pressed at (" +
                         to_string(event.button.x) + ", " + to_string(event.button.y) + ")";
                SDL_SetWindowTitle(window_, title_.c_str());
                return make_shared<ButtonRequest>(event.button.x, event.button.y, true);
            }
            break;

        // The user released a mouse button
        case SDL_MOUSEBUTTONUP:
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                return make_shared<ButtonRequest>(event.button.x, event.button.y, false);
            }
            break;

        case SDL_KEYDOWN:
            if (!TankWars_->isEnd())
            {
                switch (event.key.keysym.sym)
                {
                case SDLK_w:
                    p1dir_ = 2;
                    TankWars_->movePlayer(TankWars_->getPlayer1(), TankWars_->getPlayer2(), "up");
                    cout << "Player1 up " << TankWars_->getPlayer1()->getPosition().getX()
                         << ", " << TankWars_->getPlayer1()->getPosition().getY() << endl;
                    break;
                case SDLK_s:
                    p1dir_ = 3;
                    TankWars_->movePlayer(TankWars_->getPlayer1(), TankWars_->getPlayer2(), "down");
                    break;
                case SDLK_a:
                    p1dir_ = 4;
                    TankWars_->movePlayer(TankWars_->getPlayer1(), TankWars_->getPlayer2(), "left");
                    break;
                case SDLK_d:
                    p1dir_ = 5;
                    TankWars_->movePlayer(TankWars_->getPlayer1(), TankWars_->getPlayer2(), "right");
                    break;
                case SDLK_LSHIFT:
                    TankWars_->fire(TankWars_->getPlayer1(), TankWars_->getPlayer2());
                    break;
                case SDLK_q:
                    TankWars_->ult(TankWars_->getPlayer1(), TankWars_->getPlayer2());
                    break;
                case SDLK_UP:
                    p2dir_ = 6;
                    TankWars_->movePlayer(TankWars_->getPlayer2(), TankWars_->getPlayer1(), "up");
                    cout << "Player2 up " << TankWars_->getPlayer2()->getPosition().getX()
                         << ", " << TankWars_->getPlayer2()->getPosition().getY() << endl;
                    break;
                case SDLK_DOWN:
                    p2dir_ = 7;
                    TankWars_->movePlayer(TankWars_->getPlayer2(), TankWars_->getPlayer1(), "down");
                    cout << "Player2 down " << TankWars_->getPlayer2()->getPosition().getX()
                         << ", " << TankWars_->getPlayer2()->getPosition().getY() << endl;
                    break;
                case SDLK_LEFT:
                    p2dir_ = 8;
                    TankWars_->movePlayer(TankWars_->getPlayer2(), TankWars_->getPlayer1(), "left");
                    cout << "Player2 left " << TankWars_->getPlayer2()->getPosition().getX()
                         << ", " << TankWars_->getPlayer2()->getPosition().getY() << endl;
                    break;
                case SDLK_RIGHT:
                    p2dir_ = 9;
                    TankWars_->movePlayer(TankWars_->getPlayer2(), TankWars_->getPlayer1(), "right");
                    cout << "Player2 right " << TankWars_->getPlayer2()->getPosition().getX()
                         << ", " << TankWars_->getPlayer2()->getPosition().getY() << endl;
                    break;
                case SDLK_RSHIFT:
                    TankWars_->fire(TankWars_->getPlayer2(), TankWars_->getPlayer1());
                    break;
                case SDLK_p:
                    TankWars_->ult(TankWars_->getPlayer2(), TankWars_->getPlayer1());
                    break;
                }
            }
            break;

        // All other events are ignored
        default:
            break;
        }
    }
    return shared_ptr<Request>();
}


void Display::refresh()
{
    if (renderer_)
    {
        setTitle();
        SDL_SetWindowTitle(window_, title_.c_str());

        // Clear the window
        clearBackground();

        SDL_Rect destination;
        SDL_Texture* imageTexture;


        // draw the cells (map)
        for (const auto& c : TankWars_->getMap())
        {
            destination = { c->getPosition().getX() * size_, c->getPosition().getY() * size_, size_, size_ };
            if (c->isWall())
            {
                imageTexture = images_[0];
            }
            else
            {
                imageTexture = images_[1];
            }
            // Get the image for the cell
            refreshHelper(imageTexture, destination, "cell");
        }

        // draw the player1
        destination = { TankWars_->getPlayer1()->getPosition().getX() * size_ - size_, TankWars_->getPlayer1()->getPosition().getY() * size_ - size_, size_ * 3, size_ * 3};
        imageTexture = images_[p1dir_];
        // Get the image for the player1
        refreshHelper(imageTexture, destination, "player1");

        // draw the player1's bullets
        for (const auto& b : TankWars_->getPlayer1()->getBullets())
        {
            destination = { b->getPosition().getX() * size_, b->getPosition().getY() * size_, size_, size_};
            if (b->isUlt())
            {
                imageTexture = images_[11];
            }
            else
            {
                imageTexture = images_[10];
            }
            refreshHelper(imageTexture, destination, "player1's bullets");
        }

        // draw the player2
        destination = { TankWars_->getPlayer2()->getPosition().getX() * size_ - size_, TankWars_->getPlayer2()->getPosition().getY() * size_ - size_, size_ * 3, size_ * 3};
        imageTexture = images_[p2dir_];
        // Get the image for the player2
        refreshHelper(imageTexture, destination, "player2");

        // draw the player2's bullets
        for (const auto& b : TankWars_->getPlayer2()->getBullets())
        {
            destination = { b->getPosition().getX() * size_, b->getPosition().getY() * size_, size_, size_};
            if (b->isUlt())
            {
                imageTexture = images_[11];
            }
            else
            {
                imageTexture = images_[10];
            }
            refreshHelper(imageTexture, destination, "player2's bullets");
        }

        // draw the end
        if (!TankWars_->isEnd())
        {
            TankWars_->moveBullets(TankWars_->getPlayer1(), TankWars_->getPlayer2());
            TankWars_->moveBullets(TankWars_->getPlayer2(), TankWars_->getPlayer1());
            TankWars_->getPlayer1()->gainEnergy();
            TankWars_->getPlayer2()->gainEnergy();
            TankWars_->setTime(TankWars_->getTime() - 1);
        }
        else
        {
            destination = { width_ / 2 - 200, height_ / 2 - 200, 400, 400 };
            imageTexture = images_[12];
            refreshHelper(imageTexture, destination, "end");
        }

        SDL_RenderPresent(renderer_);
    }
}

int Display::dirToInt(int p, string dir)
{
    if (p == 1)
    {
        if (dir == "up")
        {
            return 2;
        }
        else if (dir == "down")
        {
            return 3;
        }
        else if (dir == "left")
        {
            return 4;
        }
        else if (dir == "right")
        {
            return 5;
        }
        else
        {
            throw invalid_argument("No such direction.");
        }
    }
    else if (p == 2)
    {
        if (dir == "up")
        {
            return 6;
        }
        else if (dir == "down")
        {
            return 7;
        }
        else if (dir == "left")
        {
            return 8;
        }
        else if (dir == "right")
        {
            return 9;
        }
        else
        {
            throw invalid_argument("No such direction.");
        }
    }
    else
    {
        throw invalid_argument("No such player.");
    }
}

void Display::clearBackground()
{
    if (renderer_)
    {
        // Clear the window to opaque white
        if (SDL_SetRenderDrawColor(renderer_, 0xff, 0xff, 0xff, 0xff) != 0)
        {
            close();
            throw domain_error(string("Unable to set the background color due to: ")
                               + SDL_GetError());
        }
        if (SDL_RenderClear(renderer_) != 0)
        {
            close();
            throw domain_error(string("Unable to set the background color due to: ")
                               + SDL_GetError());
        }
    }
}

void Display::refreshHelper(SDL_Texture* texture, SDL_Rect& destination, const string& name)
{
    if (texture)
    {
        // Render the image at the location,
        // rotated by its angle
        if (SDL_RenderCopyEx(renderer_, texture, nullptr,
                             &destination, 0,
                             nullptr, SDL_FLIP_NONE) != 0)
        {
            close();
            throw domain_error(string("Unable to render the " + name + " cells due to: ")
                               + SDL_GetError());
        }
    }
    else
    {
        close();
        throw domain_error("Missing " + name + " image texture");
    }
}
