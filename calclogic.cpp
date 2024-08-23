#include "calclogic.h"
#include <QDebug>

CalcLogic::CalcLogic(QObject *parent)
    : QObject(parent)
    { };

void CalcLogic::calculator(QString str, State state)
{
    if (_stateToFunc.count(state)) {
        _stateToFunc[state](str);
    }

    qDebug() << _number1 << _sign << _number2;
    emit ResultOfProcessing(_allSolution, _result);
}

void CalcLogic::Num(QString num)
{
    _inputNumberDependsDot[_dotPressed](num);

    if(_number2 != 0)
    {
        _allSolution.push_back(num);
    }
}

void CalcLogic::Sign(QString sign)
{
    if(_number1 != 0 && _number2 != 0){
        EquelForSign();
    }

    if (_sign == '\0'){
        _number1 = _number2;
        _number2 = 0;

        _allSolution.push_back(sign);
        _sign = sign;
        _dotPressed = false;
        _degreeForDot = 10;
    }
    else{
        _sign = sign;
        _allSolution.back() = sign[0];
    }

}

void CalcLogic::Dot(QString)
{
    if(!_dotPressed)
    {
        _dotPressed = true;

        if(_allSolution.isEmpty() || _allSolution.back() == _sign[0])
        {
            _allSolution.push_back('0');
        }

        _allSolution.push_back('.');
    }
}

void CalcLogic::Erase(QString)
{
    if(!_allSolution.isEmpty() && _allSolution.back() == '.')
    {
        _allSolution.chop(1);
        _dotPressed = false;
    }
    if(_number2 != 0)
    {
        _allSolution.chop(1);
        QString number_in_qstring = QString::number(_number2).back();
        double number = number_in_qstring.toDouble();


        if(_dotPressed)
        {
            qDebug() << number /_degreeForDot*10;
            _number2 -= number / _degreeForDot *10;
            _degreeForDot /= 10;
        }

        else
        {
            _number2 = static_cast<int>(_number2/10);
        }
    }
}

void CalcLogic::EraseAll(QString)
{
    _number1 = 0;
    _number2 = 0;
    _sign = '\0';

    _allSolution.clear();
    _result.clear();

    _dotPressed = false;
    _degreeForDot = 10;
}

void CalcLogic::EqualForSolution(QString sign)
{
    _signToFunc[sign](sign);
    _dotPressed = false;
    _degreeForDot = 10;
}

void CalcLogic::EquelForSign()
{
    EqualForSolution(_sign);
    if(_number1 != 0 && _number1 != 0  && _sign != '\0'){
        _sign = '\0';
        _number2 = _result.toDouble();
    }
}

void CalcLogic::Equal(QString)
{
    EqualForSolution(_sign);
    _allSolution = _result;

    _number2 = _result.toDouble();
    _number1 = 0;
    _sign = '\0';
}

void CalcLogic::dotPressed(QString num)
{
    _number2 = _number2 + num.toDouble() / _degreeForDot;
    _degreeForDot *= 10;
}

void CalcLogic::dotNotPressed(QString num)
{
    _number2 = _number2*10 + num.toDouble();
}

void CalcLogic::plus(QString)
{
    _result = QString::number(_number1 + _number2);
}

void CalcLogic::minus(QString)
{
    _result = QString::number(_number1 - _number2);
}

void CalcLogic::divide(QString)
{

    if (_number2 != 0)
        _result = QString::number(_number1 / _number2);
    else
        _result = "Error";
}

void CalcLogic::multiply(QString)
{
    _result = QString::number(_number1 * _number2);
}


void CalcLogic::Percent(QString)
{
    _allSolution.chop(QString::number(_number2).size());
    if(_number1 == 0)
    {
        _number2 /= 100;
    }
    else if(_sign == "/" || _sign == "*")
    {
        _number2 /= 100;
    }
    else
    {
        _number2 *= _number1 / 100;
    }

    _allSolution.push_back(QString::number(_number2));
}
