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

    std::map<QObject*, ptrFunc> _operatorToFunc;
    std::map<QObject*, ptrFunc> _percentForOperator;

private:
    double _number1{0};
    double _number2{0};

    double _result;

    bool _dotPressed{false};
    int _degreeForDot{10};

    QObject* _currentOperator;
    State _previoutState = State::notSelected;
    bool _operatorPressed{false};

    std::map<State, ptrFunc> _stateToFunc
    {
        {State::inputDot,         [this](QObject& dummy, State state) { Dot(dummy,      state); }},
        {State::inputNumber,      [this](QObject& num,   State state) { Num(num,        state); }},
        {State::inputOperator,    [this](QObject& sign,  State state) { Sign(sign,      state); }},
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

public:
    void calculator(QObject* str, State state);

    void plus(QObject& dummy);
    void minus(QObject& dummy);
    void divide(QObject& dummy);
    void multiply(QObject& dummy);

    void percentMultiplyOrDivideOrNotSelected(QObject& dummy);
    void percentPlusOrMinus(QObject& dummy);

private:
    void Num(QObject& num, State);

    void Sign(QObject&button, State);
    void Dot(QObject&, State);
    void Erase(QObject&, State state);
    void EraseAll(QObject&, State);
    void Percent(QObject&, State);
    void Equal(QObject&, State);

    void EqualForSolution(QObject& sign);
    void EquelForSign();

    void dotPressed(QObject& num);
    void dotNotPressed(QObject& num);

signals:
    void ResultOfProcessing(QObject* sign, double number2, double result, State currentState);
};

#endif // CALCLOGIC_H
