#ifndef CALCLOGIC_H
#define CALCLOGIC_H

#include <QString>
#include <map>
#include <QObject>
#include "state.h"

typedef std::function<void(QChar)> ptrFunc;

class CalcLogic : public QObject
{
    Q_OBJECT

public:
    CalcLogic(QObject* parent = nullptr);

private:
    QString _number1{'0'};
    QChar _sign{'\0'};
    QString _number2{'0'};

    QString _allSolutiion;
    QString _result;

    std::map<State, ptrFunc> _stateToFunc;

public:
    void calculator(QChar str, State state);

private:
    void Num(QChar num);
    void Sign(QChar sign);

    // void Minus(QChar dummy);
    void Dot(QChar dummy);
    void Erase(QChar dummy);
    void EraseAll(QChar dummy);
    void Percent(QChar dummy);
    void Equal(QChar dummy);

    void EqualForSolution();
    void EquelForSign();

    void setSolutionAndResult();

signals:
    void ResultOfProcessing(QString AllSolution, QString result);
};

#endif // CALCLOGIC_H
