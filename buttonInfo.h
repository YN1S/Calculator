#ifndef BUTTONINFO_H
#define BUTTONINFO_H

#include "state.h"

struct ButtonInfo
{
    State state;
    int row;
    int column;
    int rowSpan;
    int columnSpan;
};

#endif // BUTTONINFO_H
