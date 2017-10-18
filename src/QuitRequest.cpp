#include <string>
#include "QuitRequest.h"

using namespace std;
using namespace TankWars;

QuitRequest::QuitRequest() : Request(true) {}

QuitRequest::~QuitRequest() {}

bool QuitRequest::shouldQuit() const noexcept
{
    return true;
}
