#ifndef MODE_H
#define MODE_H

namespace tankwar
{

/**
 * The mode of the tank war game. It has two types, competitive and deathmatch.
 */
class Mode
{
    public:
        Mode();

        /** Get the time*/
        int getTime() const noexcept;

    protected:

    private:
        /** The remaining time of the mode. */
        int time_;



};
}

#endif // MODE_H
