#ifndef DISPLAY_H
#define DISPLAY_H

#include <string>
#include <vector>
#include <memory>
#include "TankWars.h"
#include "Request.h"

class SDL_Window;
class SDL_Renderer;
class SDL_Texture;
class SDL_Rect;

namespace TankWars
{


/**
 * SDL Display. Display the tank war game.
 *
 * @author Guandong Liu, Gefei Tian
 */
class Display
{
    public:
        /**
         * Create a graphical display with specified size.
         * @throw domain_error if the display could not
         * be created and initialized.
         */
        Display(std::shared_ptr<TankWars> TankWars_, /** Display width. */ int width = 660,
                                      /** Display height. */ int height = 660);

        /**
         * Destruct the graphical display.  This closes
         * the display.
         */
        ~Display();

        /**
         * Close the graphical display and release the
         * resources.
         */
        void close() noexcept;

        /**
        * Set the title
        */
        void setTitle() noexcept;

        /**
         * Add an image to the collection.
         */
        void addImage(/** The location of the file. */
            const std::string& fileLocation) noexcept;

        /**
         * Get the next request from the user.  If quit
         * is requested, the display is closed and
         * deleted.  If a button is pressed, then the
         * window title is changed.
         * @return The request event that occurred or
         * null if no event occurred.
         */
        std::shared_ptr<Request> getNextRequest() noexcept;

        /**
         * Refresh the display.
         * @throw domain_error if the display could not
         * be refreshed.
         */
        void refresh();

    private:
        /** The tank war game */
        std::shared_ptr<TankWars> TankWars_;

        /** The display title */
        std::string title_;

        /** The display window. */
        SDL_Window* window_ = nullptr;

        /** The display rendering tool. */
        SDL_Renderer* renderer_ = nullptr;

        /** The collection of images. */
        std::vector<SDL_Texture*> images_;

        /** The width of the window. */
        const int width_ = 0;

        /** The height of the window. */
        const int height_ = 0;

        /** The size of the image. */
        const int size_ = 20;

        /** Player1's direction */
        int p1dir_;

        /** Player's direction */
        int p2dir_;


        /**
         * Clear the background to opaque whiGuandong Liu, Gefei Tiante.
         */
        void clearBackground();

        /**
         * The helper function for refresh
         * @param texture The image to render
         * @param destination The position of the image
         * @param name The name of the image
         */
        void refreshHelper(SDL_Texture* texture, SDL_Rect& destination, const std::string& name);

        /**
         * convert the direction into int
         * @param p, last direction
         * @param dir, the direction.
         * @return int, as the direction.
         */
        int dirToInt(int p, std::string dir);
};
}

#endif // DISPLAY_H
