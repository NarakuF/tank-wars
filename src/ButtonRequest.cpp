#include "ButtonRequest.h"
#include <memory>

using namespace std;
using namespace TankWars;

ButtonRequest::ButtonRequest(int x, int y, bool isPressed)
    : Request(true), x_(x), y_(y), isPressed_(isPressed) {}

ButtonRequest::~ButtonRequest() {}

bool ButtonRequest::shouldQuit() const noexcept
{
    return false;
}

bool ButtonRequest::pressedButton() const noexcept
{
    return isPressed_;
}

bool ButtonRequest::releasedButton() const noexcept
{
    return !isPressed_;
}

int ButtonRequest::xPosition() const noexcept
{
    return dynamic_pointer_cast<const ButtonRequest>(shared_from_this())->x_;
}

int ButtonRequest::yPosition() const noexcept
{
    return y_;
}
