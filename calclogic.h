#ifndef CALCLOGIC_H
#define CALCLOGIC_H

#include <QString>
#include <map>
#include <QObject>
#include "state.h"

typedef std::function<void(QString)> ptrFunc;

class CalcLogic : public QObject
{
    Q_OBJECT

public:
    CalcLogic(QObject* parent = nullptr);

private:
    double _number1{0};
    QString _sign{'\0'};
    double _number2{0};

    QString _allSolution;
    QString _result;

    bool _dotPressed{false};
    int _degreeForDot{10};

    std::map<State, ptrFunc> _stateToFunc
        {
            {State::inputDot,       [this](QString dummy) { Dot(dummy);      }},
            {State::inputNumber,    [this](QString num)   { Num(num);        }},
            {State::inputOtherSign, [this](QString sign)  { Sign(sign);      }},
            {State::inputEraseAll,  [this](QString dummy) { EraseAll(dummy); }},
            {State::inputErase,     [this](QString dummy) { Erase(dummy);    }},
            {State::inputPercent,   [this](QString dummy) { Percent(dummy);  }},
            {State::inputEqual,     [this](QString dummy) { Equal(dummy);    }}
        };

    std::map<bool, ptrFunc> _inputNumberDependsDot
        {
         {true, [this](QString num) { dotPressed(num);    }},
         {false,[this](QString num) { dotNotPressed(num); }},
         };

    std::map<QString, ptrFunc> _signToFunc
        {
            {"+", [this](QString dummy){ plus(dummy); }},
            {"-", [this](QString dummy){ minus(dummy); }},
            {"*", [this](QString dummy){ multiply(dummy); }},
            {"/", [this](QString dummy){ divide(dummy); }}
        };

public:
    void calculator(QString str, State state);

private:
    void Num(QString num);
    void Sign(QString sign);

    // void Minus(QChar dummy);
    void Dot(QString dummy);
    void Erase(QString dummy);
    void EraseAll(QString dummy);
    void Percent(QString dummy);
    void Equal(QString dummy);

    void EqualForSolution(QString sign);
    void EquelForSign();

    void dotPressed(QString num);
    void dotNotPressed(QString num);

    void plus(QString);
    void minus(QString);
    void divide(QString);
    void multiply(QString);

signals:
    void ResultOfProcessing(QString AllSolution, QString result);
};

#endif // CALCLOGIC_H
