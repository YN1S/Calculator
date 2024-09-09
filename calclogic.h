// calclogic.h

#ifndef CALCLOGIC_H
#define CALCLOGIC_H

#include <QString>
#include <map>
#include <QObject>
#include <functional> // include for std::function
#include "state.h"

typedef std::function<void(QObject&, State)> ptrFunc;  // Изменяем typedef для использования QObject

class CalcLogic : public QObject
{
    Q_OBJECT

public:
    CalcLogic(QObject* parent = nullptr);

private:
    double _number1{0};
    double _number2{0};

    double _result;

    bool _dotPressed{false};
    int _degreeForDot{10};

    State _currentOperator = State::notSelected;
    State _previoutState = State::notSelected;

    std::map<State, ptrFunc> _stateToFunc
    {
        {State::inputDot,         [this](QObject& dummy, State state) { Dot(dummy,      state); }},
        {State::inputNumber,      [this](QObject& num,   State state) { Num(num,        state); }},
        {State::operatorPlus,     [this](QObject& sign,  State state) { Sign(sign,      state); }},
        {State::operatorMinus,    [this](QObject& sign,  State state) { Sign(sign,      state); }},
        {State::operatorMultiply, [this](QObject& sign,  State state) { Sign(sign,      state); }},
        {State::operatorDivide,   [this](QObject& sign,  State state) { Sign(sign,      state); }},
        {State::inputEraseAll,    [this](QObject& dummy, State state) { EraseAll(dummy, state); }},
        {State::inputErase,       [this](QObject& dummy, State state) { Erase(dummy,    state); }},
        {State::inputPercent,     [this](QObject& dummy, State state) { Percent(dummy,  state); }},
        {State::inputEqual,       [this](QObject& dummy, State state) { Equal(dummy,    state); }}
    };

    std::map<bool, ptrFunc> _inputNumberDependsDot
    {
        {true,  [this](QObject& num, State state) { dotPressed(num);    }},
        {false, [this](QObject& num, State state) { dotNotPressed(num); }},
    };

    std::map<State, ptrFunc> _operatorToFunc
    {
        {State::operatorPlus,     [this](QObject& dummy, State state){ plus(dummy);     }},
        {State::operatorMinus,    [this](QObject& dummy, State state){ minus(dummy);    }},
        {State::operatorMultiply, [this](QObject& dummy, State state){ multiply(dummy); }},
        {State::operatorDivide,   [this](QObject& dummy, State state){ divide(dummy);   }}
    };

    std::map<State, ptrFunc> _percentForOperator
    {
        {State::operatorPlus,     [this](QObject& dummy, State state){ percentPlusOrMinus(dummy);                  }},
        {State::operatorMinus,    [this](QObject& dummy, State state){ percentPlusOrMinus(dummy);                  }},
        {State::operatorMultiply, [this](QObject& dummy, State state){ percentMultiplyOrDivideOrNotSelected(dummy); }},
        {State::operatorDivide,   [this](QObject& dummy, State state){ percentMultiplyOrDivideOrNotSelected(dummy); }},
        {State::notSelected,      [this](QObject& dummy, State state){ percentMultiplyOrDivideOrNotSelected(dummy); }}
    };

public:
    void calculator(QObject* str, State state);

private:
    void Num(QObject& num, State);

    void Sign(QObject&, State);
    void Dot(QObject&, State);
    void Erase(QObject&, State state);
    void EraseAll(QObject&, State);
    void Percent(QObject&, State);
    void Equal(QObject&, State);

    void EqualForSolution(QObject& sign);
    void EquelForSign();

    void dotPressed(QObject& num);
    void dotNotPressed(QObject& num);

    void plus(QObject& dummy);
    void minus(QObject& dummy);
    void divide(QObject& dummy);
    void multiply(QObject& dummy);

    void percentMultiplyOrDivideOrNotSelected(QObject& dummy);
    void percentPlusOrMinus(QObject& dummy);

signals:
    void ResultOfProcessing(QObject* button, State state, double result);

// public slots:
//     void getPressedButton;
};

#endif // CALCLOGIC_H
