#ifndef BUTTONS_H
#define BUTTONS_H

#include <map>
#include <vector>
#include <QObject>
#include <QPushButton>
#include "buttonInfo.h"
#include "state.h"


// QPushButton* button0 = new QPushButton("0");
// QPushButton* button1 = new QPushButton("1");
// QPushButton* button2 = new QPushButton("2");
// QPushButton* button3 = new QPushButton("3");
// QPushButton* button4 = new QPushButton("4");
// QPushButton* button5 = new QPushButton("5");
// QPushButton* button6 = new QPushButton("6");
// QPushButton* button7 = new QPushButton("7");
// QPushButton* button8 = new QPushButton("8");
// QPushButton* button9 = new QPushButton("9");

// QPushButton* buttonDivide =   new QPushButton("/");
// QPushButton* buttonMultiply = new QPushButton("*");
// QPushButton* buttonPlus =     new QPushButton("+");
// QPushButton* buttonMinus =    new QPushButton("-");
// QPushButton* buttonEqual =    new QPushButton("=");

// QPushButton* buttonDot =      new QPushButton(".");
// QPushButton* ButtonPercent =  new QPushButton("%");
// QPushButton* ButtonAllClear = new QPushButton("AC");
// QPushButton* ButtonClear =    new QPushButton("C");



// std::map<QObject*, ButtonInfo> buttons
// {
//     {ButtonAllClear, {inputEraseAll, 2, 0, 1, 1}}, {ButtonClear, {inputErase,  2, 1, 1, 1}}, {ButtonPercent, {inputPercent, 2, 2, 1, 1}}, {buttonDivide,   {inputOtherSign,  2, 3, 1, 1}},
//     {button7,        {inputNumber,   3, 0, 1, 1}}, {button8,     {inputNumber, 3, 1, 1, 1}}, {button9,       {inputNumber,  3, 2, 1, 1}}, {buttonMultiply, {inputOtherSign,  3, 3, 1, 1}},
//     {button4,        {inputNumber,   4, 0, 1, 1}}, {button5,     {inputNumber, 4, 1, 1, 1}}, {button6,       {inputNumber,  4, 2, 1, 1}}, {buttonMinus,    {inputOtherSign,  4, 3, 1, 1}},
//     {button1,        {inputNumber,   5, 0, 1, 1}}, {button2,     {inputNumber, 5, 1, 1, 1}}, {button3,       {inputNumber,  5, 2, 1, 1}}, {buttonPlus,     {inputOtherSign,  5, 3, 1, 1}},
//     {button0,        {inputNumber,   6, 0, 1, 2}},                                           {buttonDot,     {inputDot,     6, 2, 1, 1}}, {buttonEqual,    {inputEqual,      6, 3, 1, 1}}
// };

std::vector<QString> buttonsName
{
    "AC", "C", "%", "/",
    "7" , "8", "9", "*",
    "4" , "5", "6", "-",
    "1" , "2", "3", "+",
    "0" ,      ".", "="
};

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


std::vector<QString> buttonsNameSign
{
    "/",
    "*",
    "+",
    "-"
};

std::vector<ButtonInfo> buttonsInfoSign
{
    {inputOtherSign,  2, 3, 1, 1},
    {inputOtherSign,  3, 3, 1, 1},
    {inputOtherSign,  4, 3, 1, 1},
    {inputOtherSign,  5, 3, 1, 1}
};

std::vector<QString> buttonsNameOther
{
    "AC", "C", "%", ".", "="
};

std::vector<ButtonInfo> buttonsInfoOther
{
    {inputEraseAll, 2, 0, 1, 1}, {inputErase,  2, 1, 1, 1}, {inputPercent, 2, 2, 1, 1}, {inputDot,     6, 2, 1, 1}, {inputEqual,      6, 3, 1, 1}
};

std::vector<ButtonInfo> buttonsInfo
{
    {inputEraseAll, 2, 0, 1, 1}, {inputErase,  2, 1, 1, 1}, {inputPercent, 2, 2, 1, 1}, {inputOtherSign,  2, 3, 1, 1},
    {inputNumber,   3, 0, 1, 1}, {inputNumber, 3, 1, 1, 1}, {inputNumber,  3, 2, 1, 1}, {inputOtherSign,  3, 3, 1, 1},
    {inputNumber,   4, 0, 1, 1}, {inputNumber, 4, 1, 1, 1}, {inputNumber,  4, 2, 1, 1}, {inputOtherSign,  4, 3, 1, 1},
    {inputNumber,   5, 0, 1, 1}, {inputNumber, 5, 1, 1, 1}, {inputNumber,  5, 2, 1, 1}, {inputOtherSign,  5, 3, 1, 1},
    {inputNumber,   6, 0, 1, 2},                            {inputDot,     6, 2, 1, 1}, {inputEqual,      6, 3, 1, 1}
};

#endif // BUTTONS_H
