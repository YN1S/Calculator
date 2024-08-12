#include "calclogic.h"
#include <QDebug>

CalcLogic::CalcLogic(QObject *parent)
    : QObject(parent),
    _stateToFunc{
        {State::inputDot,       [this](QChar dummy) { Dot(dummy);      }},
        {State::inputNumber,    [this](QChar num)   { Num(num);        }},
        {State::inputOtherSign, [this](QChar sign)  { Sign(sign);      }},
        {State::inputEraseAll,  [this](QChar dummy) { EraseAll(dummy); }},
        {State::inputErase,     [this](QChar dummy) { Erase(dummy);    }},
        {State::inputPercent,   [this](QChar dummy) { Percent(dummy);  }},
        {State::inputEqual,     [this](QChar dummy) { Equal(dummy);    }}
    }
{ }

void CalcLogic::calculator(QChar str, State state)
{
    if (_stateToFunc.count(state)) {
        _stateToFunc[state](str);
    }

    qDebug() << _number1 + _sign + _number2;
    emit ResultOfProcessing(_allSolutiion, _result);
}

void CalcLogic::Num(QChar num)
{
    if(_number2 == '0'){
        _number2.back() = num;
    }
    else{
        _number2.push_back(num);
    }

    if(_allSolutiion == '0'){
        _allSolutiion.back() = num;
    }
    else{
        _allSolutiion.push_back(num);
    }
    EqualForSolution();
}

void CalcLogic::Sign(QChar sign)
{
    if(!_number1.isEmpty() && !_number2.isEmpty()){
        EquelForSign();
    }

    if (_sign == '\0'){
        _number1 = _number2;
        _number2.clear();

        _allSolutiion.push_back(sign);
        _sign = sign;
    }
    else{
        _sign = sign;
        _allSolutiion.back() = sign;
    }
}

void CalcLogic::Dot(QChar)
{
    if(std::find(_number2.begin(), _number2.end(), '.') == _number2.end()){
        if((_number2 == '0' || _number2.isEmpty()) && _allSolutiion.back() != '0'){
            _allSolutiion.push_back('0');
        }
        _number2.push_back('.');
        _allSolutiion.push_back('.');
    }
}

void CalcLogic::Erase(QChar)
{
    if(!_number2.isEmpty()){
        _allSolutiion.chop(1);
        _number2.chop(1);
    }
}

void CalcLogic::EraseAll(QChar)
{
    _number1 = '0';
    _number2 = '0';
    _sign = '\0';

    _allSolutiion.clear();
    _result.clear();
}

void CalcLogic::EqualForSolution()
{
    if(!_number1.isEmpty() && !_number1.isEmpty() && _sign != '\0'){
        switch (_sign.unicode()) {
        case '+':
            _result = QString::number(_number1.toDouble() + _number2.toDouble());
            break;
        case '-':
            _result = QString::number(_number1.toDouble() - _number2.toDouble());
            break;
        case '*':
            _result = QString::number(_number1.toDouble() * _number2.toDouble());
            break;
        case '/':
            if (_number2.toDouble() != 0)
                _result = QString::number(_number1.toDouble() / _number2.toDouble());
            else{
                _result = "Error";
            }
            break;
        default:
            _result = "Error";  // Обработка неизвестного оператора
            break;
        }
    }
}

void CalcLogic::EquelForSign()
{
    EqualForSolution();
    if(!_number1.isEmpty() && !_number1.isEmpty() && _sign != '\0'){
        _sign = '\0';
        _number2 = _result;
    }
}

void CalcLogic::Equal(QChar){
    EqualForSolution();
    _allSolutiion = _result;
}

void CalcLogic::Percent(QChar)
{
     _allSolutiion.chop(_number2.size());
    if(_number1 == '0')
    {
        _number2 = QString::number(_number2.toDouble() / 100);
    }
    else
    {
        switch(_sign.unicode())
        {
        case '/':
        case '*':
            // _allSolutiion.chop(_number2.size());
            _number2 = QString::number(_number2.toDouble() / 100);
            break;
        case '+':
        case '-':
            // _allSolutiion.chop(_number2.size());
            _number2 = QString::number(_number1.toDouble() * (_number2.toDouble() / 100));
            break;
        }
    }
    _allSolutiion.push_back(_number2);
    // setSolutionAndResult();
}
