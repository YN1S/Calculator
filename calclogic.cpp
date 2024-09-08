// calclogic.cpp

#include "calclogic.h"
#include <QDebug>

CalcLogic::CalcLogic(QObject *parent)
    : QObject(parent)
{ }

void CalcLogic::calculator(QObject* str, State state)
{
    if(_stateToFunc.count(state))
    {
        _stateToFunc[state](*str, state);
    }

    qDebug() << _number1 << _sign << _number2;
}

void CalcLogic::Num(QObject& num, State state)
{
    _inputNumberDependsDot[_dotPressed](num, state);
    _previoutState = state;
}

void CalcLogic::Sign(QObject& dummy, State state)
{
    if(_previoutState == State::inputNumber)
    {
        Equal(dummy, state);
    }


    if(_currentOperator == State::notSelected)
    {
        _number1 = _number2;
        _number2 = 0;

        _dotPressed = false;
        _degreeForDot = 10;
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

void CalcLogic::EraseAll(QObject& dummy, State state)
{
    _number1 = 0;
    _number2 = 0;
    _currentOperator = State::notSelected;
    _previoutState = State::notSelected;

    _dotPressed = false;
    _degreeForDot = 10;
}

void CalcLogic::EqualForSolution(QObject& sign)
{
    _dotPressed = false;
    _degreeForDot = 10;
}

void CalcLogic::EquelForSign()
{
    if(_number1 != 0 && _number1 != 0  && _sign != '\0'){
        _sign = '\0';
    }
}

void CalcLogic::Equal(QObject& dummy, State state)
{
    _operatorToFunc[_currentOperator](dummy, state);

    _number2 = _result;
    _number1 = 0;

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

void CalcLogic::Percent(QObject&, State state)
{
    _allSolution.chop(QString::number(_number2).size());
    if(_number1 == 0)
    {
        _number2 /= 100;
    }
    else if(_currentOperator == State::operatorMultiply || _currentOperator == State::operatorDivide)
    {
        _number2 /= 100;
    }
    else
    {
        _number2 *= _number1 / 100;
    }

    _allSolution.push_back(QString::number(_number2));
}
