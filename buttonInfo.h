#ifndef BUTTONINFO_H
#define BUTTONINFO_H

#include "state.h"

struct ButtonInfo
{
    State state;
    std::pair<int, int> position;
    std::pair<int, int> size;
};

#endif // BUTTONINFO_H
