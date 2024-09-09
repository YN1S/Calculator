// calclogic.cpp

#include "calclogic.h"
#include <QDebug>

CalcLogic::CalcLogic(QObject *parent)
    : QObject(parent)
{ }

void CalcLogic::calculator(QObject* button, State state)
{
    if(_stateToFunc.count(state))
    {
        _stateToFunc[state](*button, state);
    }

    qDebug() << "Final: " << _number1 << _number2;
    emit ResultOfProcessing(button, state, _result);
}

void CalcLogic::Num(QObject& num, State state)
{
    _inputNumberDependsDot[_dotPressed](num, state);
    _previoutState = state;
}

void CalcLogic::Sign(QObject& dummy, State state)
{
    if(_currentOperator == State::notSelected)
    {
        // qDebug() << "SIGN 2-nd if: "  << _number1 << _sign << _number2;
        _number1 = _number2;
        _number2 = 0;

        _dotPressed = false;
        _degreeForDot = 10;
    }

    if(_previoutState == State::inputNumber)
    {
        // qDebug() << "SIGN 1-st if before: "  << _number1 << _sign << _number2;
        Equal(dummy, state);
        // qDebug() << "SIGN 1-st if after: "  << _number1 << _sign << _number2;
    }


    _currentOperator = state;
    _previoutState = state;
}

void CalcLogic::Dot(QObject&, State)
{
    _dotPressed = true;
}

void CalcLogic::Erase(QObject& dummy, State state)
{
    // Аналогичная логика
}

void CalcLogic::EraseAll(QObject&, State)
{
    _number1 = 0;
    _number2 = 0;
    _result = 0;

    _currentOperator = State::notSelected;
    _previoutState = State::notSelected;

    _dotPressed = false;
    _degreeForDot = 10;
}

void CalcLogic::Equal(QObject& dummy, State state)
{
    if(_operatorToFunc.count(_currentOperator))
    {
        _operatorToFunc[_currentOperator](dummy, state);
        _number1 = _result;
        _number2 = 0;

        _dotPressed = false;
        _degreeForDot = 10;
    }
}

void CalcLogic::Percent(QObject& dummy, State state)
{
    _percentForOperator.at(_currentOperator)(dummy, state);
}


void CalcLogic::dotPressed(QObject& num)
{
    _number2 = _number2 + num.objectName().toDouble() / _degreeForDot;
    _degreeForDot *= 10;
}

void CalcLogic::dotNotPressed(QObject& num)
{
    _number2 = _number2*10 + num.objectName().toDouble();
}

void CalcLogic::plus(QObject&)
{
    _result = _number1 + _number2;
}

void CalcLogic::minus(QObject&)
{
    _result = _number1 - _number2;
}

void CalcLogic::divide(QObject&)
{
    if (_number2 != 0)
        _result = _number1 / _number2;
}

void CalcLogic::multiply(QObject&)
{
    _result = _number1 * _number2;
}

void CalcLogic::percentMultiplyOrDivideOrNotSelected(QObject &dummy)
{
    _number2 /= 100;
}

void CalcLogic::percentPlusOrMinus(QObject &dummy)
{
    _number2 *= _number1 / 100;
}


