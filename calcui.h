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

class CalcUI : public QWidget
{
    Q_OBJECT

public:
    CalcUI(QWidget *parent = nullptr);

private: // Переменные
    CalcLogic logic;
    QLineEdit* _displaySolving;
    QLabel* _displayHistory;
    QScrollArea* _historyArea;
    QGridLayout* _pUIGridLayout;

    int _previousWidth;
    int _previoutHeight;

    double _previousResult;
    QString _allHistory;
    QString _allSolution;
    QString _number;

    bool _isFirstOperator{true};
    State _previousState;

    std::map<QObject*, State> _buttonAndState;

    bool _previousStateIsOperator {false};

private: // Функции
    QGridLayout* createLayout();
    QPushButton* createButton(const QString &str, State state);
    void createButtonsFromContainer(QGridLayout *gridLayout, const std::vector<QString>& buttonsName, const std::vector<ButtonInfo>& buttonsInfo);
    void setDisplayParameters();

public slots:
    void sendButtonToLogic();
    void getResultsOfProcessing(QObject* sign, double number2, double result, State currentState);
    void toggleScrollAreaVisibility();
};

#endif // CALCUI_H
