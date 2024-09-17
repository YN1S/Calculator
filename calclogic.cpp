// calclogic.cpp

#include "calclogic.h"
#include <QDebug>

CalcLogic::CalcLogic(QObject *parent)
    : QObject(parent)
{ }

void CalcLogic::calculator(QObject* button, State state)
{

    _stateToFunc[state](*button, state);

    qDebug() << "Final: " << _number1 << _number2;
    emit ResultOfProcessing(_currentOperator, _number2, _result, state);
}

void CalcLogic::Num(QObject& num, State state)
{
    if(_previoutState == State::inputEqual)
    {
        return;
    }

    _inputNumberDependsDot[_dotPressed](num, state);
    _previoutState = state;
}

void CalcLogic::Sign(QObject& button, State state)
{
    if(!_operatorPressed)
    {
        _number1 = _number2;
        _number2 = 0;

        _dotPressed = false;
        _degreeForDot = 10;
        _operatorPressed = true;
    }

    if(_previoutState == State::inputNumber)
    {
        Equal(*_currentOperator, state);
    }

    _currentOperator = &button;
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

    _previoutState = State::notSelected;

    _dotPressed = false;
    _degreeForDot = 10;
    _operatorPressed = false;
}

void CalcLogic::Equal(QObject&, State state)
{

    if(_operatorToFunc.count(_currentOperator))
    {
        _operatorToFunc[_currentOperator](*_currentOperator, state);
        _number1 = _result;
        _number2 = 0;
        _dotPressed = false;
        _degreeForDot = 10;
        _previoutState = state;
    }
}

void CalcLogic::Percent(QObject& dummy, State state)
{
    if(!_percentForOperator.count(_currentOperator))
    {
        percentMultiplyOrDivideOrNotSelected(dummy);
        return;
    }
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

    qDebug() << _result << "plus";
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

