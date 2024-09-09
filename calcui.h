// calcui.h

#ifndef CALCUI_H
#define CALCUI_H

#include <QWidget>
#include <map>
#include <QGridLayout>
#include <QScrollArea>
#include <functional>
#include "state.h"
#include "buttonInfo.h"
#include "calclogic.h"

class QPushButton;
class QLabel;
class QLineEdit;

typedef std::function<void(QObject&, State)> ptrFunc;

class CalcUI : public QWidget
{
    Q_OBJECT

public:
    CalcUI(QWidget *parent = nullptr);

private: // Переменные
    CalcLogic logic;
    QLineEdit* _displaySolving;
    QLabel* _displayAnswer;

    QString _allSolution;

    std::map<QObject*, State> buttonAndState;

    bool _previousStateIsOperator {false};

    // Инициализация _stateToFunc прямо в объявлении класса
    std::map<State, ptrFunc> _stateToFunc
        {
            {State::inputDot,         [this](QObject& dummy, State state) { Dot(dummy,      state); }},
            {State::inputNumber,      [this](QObject& num,   State state) { Num(num,        state); }},
            {State::operatorPlus,     [this](QObject& sign,  State state) { Sign(sign,      state); }},
            {State::operatorMinus,    [this](QObject& sign,  State state) { Sign(sign,      state); }},
            {State::operatorMultiply, [this](QObject& sign,  State state) { Sign(sign,      state); }},
            {State::operatorDivide,   [this](QObject& sign,  State state) { Sign(sign,      state); }},
            {State::inputEraseAll,    [this](QObject& dummy, State state) { EraseAll(dummy, state); }},
            // {State::inputErase,       [this](QObject& dummy, State state) { Erase(dummy,    state); }},
            {State::inputPercent,     [this](QObject& dummy, State state) { Percent(dummy,  state); }},
            {State::inputEqual,       [this](QObject& dummy, State state) { Equal(dummy,    state); }}
        };

    std::map<bool, ptrFunc> _drawOperator
    {
        {true,  [this](QObject& dummy, State state) { stateIsOperator(dummy,    state); }},
        {false, [this](QObject& dummy, State state) { stateIsNotOperator(dummy, state); }},
    };

private: // Функции
    QGridLayout* createLayout();
    QPushButton* createButton(const QString &str, State state);
    void createButtonsFromContainer(QGridLayout *gridLayout, const std::vector<QString>& buttonsName, const std::vector<ButtonInfo>& buttonsInfo);
    void setDisplayParameters();
    void drawResult(QObject* button, State state);

    void Num(QObject& num, State);
    void Sign(QObject&sign, State);
    void Dot(QObject&, State);
    // void Erase(QObject&, State state);
    void EraseAll(QObject&, State);
    void Percent(QObject&, State);
    void Equal(QObject&, State);

    void stateIsOperator(QObject &sign, State);
    void stateIsNotOperator(QObject &sign, State);

public slots:
    void sendButtonToLogic();
    void getResultsOfProcessing(QObject *button, State state, double result);

};

#endif // CALCUI_H
