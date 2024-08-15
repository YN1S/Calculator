#ifndef CALCUI_H
#define CALCUI_H

#include <QWidget>
#include <map>
#include <QGridLayout>
#include <QScrollArea>
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
    QLabel* _displayAnswer;
    std::map<QObject*, State> buttonAndState;

private: // Функции
    QGridLayout* createLayout();
    QPushButton* createButton(const QString &str, State state);
    void createButtonsFromContainer(QGridLayout *gridLayout, const std::vector<QString>& buttonsName, const std::vector<ButtonInfo>& buttonsInfo);
    void setDisplayParameters();

public slots:
    void sendButtonToLogic();
    void getResultsOfProcessing(QString AllSolution, QString result);

};
#endif // CALCUI_H
