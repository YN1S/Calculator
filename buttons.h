#ifndef BUTTONS_H
#define BUTTONS_H

#include <map>
#include <vector>
#include <QObject>
#include <QPushButton>
#include "buttonInfo.h"
#include "state.h"

std::vector<QString> buttonsNameNumber
{
    "7" , "8", "9",
    "4" , "5", "6",
    "1" , "2", "3",
    "0"
};

std::vector<ButtonInfo> buttonsInfoNumber
{
    {inputNumber,   3, 0, 1, 1}, {inputNumber, 3, 1, 1, 1}, {inputNumber,  3, 2, 1, 1},
    {inputNumber,   4, 0, 1, 1}, {inputNumber, 4, 1, 1, 1}, {inputNumber,  4, 2, 1, 1},
    {inputNumber,   5, 0, 1, 1}, {inputNumber, 5, 1, 1, 1}, {inputNumber,  5, 2, 1, 1},
    {inputNumber,   6, 0, 1, 2}
};


// std::vector<QString> buttonsNameSign
// {
//     "/",
//     "*",
//     "+",
//     "-"
// };

// std::vector<ButtonInfo> buttonsInfoSign
// {
//     {operatorDivide,    2, 3, 1, 1},
//     {operatorMultiply,  3, 3, 1, 1},
//     {operatorPlus,      4, 3, 1, 1},
//     {operatorMinus,     5, 3, 1, 1}
// };

std::vector<QString> buttonsNameOther
{
    "AC", /*"C",*/ "%", ".", "="
};

std::vector<ButtonInfo> buttonsInfoOther
{
    {inputEraseAll, 2, 0, 1, 2}, /*{inputErase,  2, 1, 1, 1},*/ {inputPercent, 2, 2, 1, 1}, {inputDot,     6, 2, 1, 1}, {inputEqual,      6, 3, 1, 1}
};

std::vector<QString> buttonNameoHistory
{
    "History"
};

std::vector<ButtonInfo> buttonInfoHistory
{
    {inputHistory, 0, 0, 1, 2}
};

#endif // BUTTONS_H
