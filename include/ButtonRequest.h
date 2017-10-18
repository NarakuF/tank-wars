#ifndef BUTTONREQUEST_H
#define BUTTONREQUEST_H

#include "Request.h"

namespace TankWars
{
/**
 * User Button Press Request.
 * Check the position of user's mouse
 * also if the user press the mouse button or not
 *
 * @author Guandong Liu, Gefei Tian
 */
class ButtonRequest : virtual public Request
{
    public:
        /**
         * Construct a button press request.
         */
        ButtonRequest(/** The x-coordinate of
                    the mouse location. */
            int x,
            /** The y-coordinate of
                the mouse location. */
            int y,
            /** Whether the button was pressed. */
            bool isPressed);

        /** Destructor. */
        virtual ~ButtonRequest();

        /**
         * Whether the user asked the program to quit.
         * @return always false.
         */
        virtual bool shouldQuit() const noexcept;

        /**
         * Whether the user pressed the left button.
         * @return true if the button was pressed.
         */
        virtual bool pressedButton() const noexcept override;

        /**
         * Whether the user released the left button.
         * @return true if the button was released.
         */
        virtual bool releasedButton() const noexcept override;

        /**
         * Get the x-coordinate of the mouse position.
         * @return The x-coordinate of the mouse position.
         */
        virtual int xPosition() const noexcept override;

        /**
         * Get the y-coordinate of the mouse position.
         * @return The y-coordinate of the mouse position.
         */
        virtual int yPosition() const noexcept override;

    private:
        /** The x-coordinate of the mouse location. */
        int x_ = 0;

        /** The y-coordinate of the mouse location. */
        int y_ = 0;

        /** Whether the button was pressed. */
        bool isPressed_ = false;
};
}

#endif // BUTTONREQUEST_H
