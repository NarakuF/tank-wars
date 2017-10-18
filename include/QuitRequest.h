#ifndef QUITREQUEST_H
#define QUITREQUEST_H

#include <string>
#include "Request.h"

namespace TankWars
{

/**
 * User Quit Request.
 * handle the quit request made by the user
 *
 * @author Guandong Liu, Gefei Tian
 */
class QuitRequest : virtual public Request
{
    public:
        /**
         * Default constructor.
         */
        QuitRequest();

        /** Destructor. */
        virtual ~QuitRequest();

        /**
         * Whether the user asked the program to quit.
         * @return always true for this class.
         */
        virtual bool shouldQuit() const noexcept;
};
}

#endif // QUITREQUEST_H
