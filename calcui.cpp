#include "calcui.h"

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QDebug>
#include "buttons.h"

CalcUI::CalcUI(QWidget *parent)
    : QWidget(parent)
{
    connect(&logic, &CalcLogic::ResultOfProcessing, this, &CalcUI::getResultsOfProcessing);
    setLayout(createLayout());
}

QGridLayout *CalcUI::createLayout()
{
    setDisplayParameters();

    QGridLayout* pUIGridLayout = new QGridLayout;
    pUIGridLayout->addWidget(_displaySolving, 0, 0, 1, 4);
    pUIGridLayout->addWidget(_displayAnswer, 1, 0, 1, 4);


    createButtonsFromContainer(pUIGridLayout, buttonsNameNumber, buttonsInfoNumber);
    createButtonsFromContainer(pUIGridLayout, buttonsNameSign,   buttonsInfoSign);
    createButtonsFromContainer(pUIGridLayout, buttonsNameOther,  buttonsInfoOther);

    return pUIGridLayout;
}

QPushButton *CalcUI::createButton(const QString &str, State state)
{
    QPushButton* pcmd = new QPushButton{str};
    pcmd->setObjectName(str);
    pcmd->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    buttonAndState.insert({pcmd, state});
    connect(pcmd, &QPushButton::clicked, this, &CalcUI::sendButtonToLogic);
    return pcmd;
}

void CalcUI::createButtonsFromContainer(QGridLayout* gridLayout, const std::vector<QString> &buttonsName, const std::vector<ButtonInfo> &buttonsInfo)
{
    for(int i{0}; i < buttonsName.size(); ++i)
    {
        gridLayout->addWidget(createButton(buttonsName[i], buttonsInfo[i].state), buttonsInfo[i].row,     buttonsInfo[i].column,
                              buttonsInfo[i].rowSpan, buttonsInfo[i].columnSpan);
    }
}

void CalcUI::setDisplayParameters()
{
    _displaySolving = new QLineEdit;
    _displaySolving->setReadOnly(true);
    _displaySolving->setText(0);
    _displaySolving->setAlignment(Qt::AlignRight);
    _displaySolving->setStyleSheet("QLineEdit { font-size: 18pt}");
    _displaySolving->setMinimumSize(150, 50);

    _displayAnswer = new QLabel;
    _displayAnswer->setText(0);
    _displayAnswer->setAlignment(Qt::AlignRight);

}

void CalcUI::sendButtonToLogic()
{
    logic.calculator(sender(), buttonAndState.at(sender()));
}

void CalcUI::getResultsOfProcessing(QObject* button, State state, double result)
{
    _displayAnswer->setText(QString::number(result));

    if(_stateToFunc.count(state))
    {
        _stateToFunc[state](*button, state);
    }

    _displaySolving->setText(_allSolution);
}

void CalcUI::Num(QObject& num, State state)
{
    _allSolution.push_back(num.objectName());
    _previousStateIsOperator = false;
}

void CalcUI::Sign(QObject& sign, State state)
{
    _drawOperator.at(_previousStateIsOperator)(sign, state);

    _previousStateIsOperator = true;
}

void CalcUI::Dot(QObject&, State)
{
    if(_allSolution.isEmpty())
    {
        _allSolution.push_back("0.");
    }
    else if(_allSolution.back() != '.')
    {
        _allSolution.push_back('.');
    }

}

void CalcUI::EraseAll(QObject&, State)
{
    _allSolution.clear();
    _previousStateIsOperator = false;
}

void CalcUI::Equal(QObject& dummy, State state)
{
    _allSolution = _displayAnswer->text();
}

void CalcUI::stateIsOperator(QObject &sign, State)
{
    _allSolution.back() = sign.objectName().at(0);
}

void CalcUI::stateIsNotOperator(QObject &sign, State)
{
    if(_allSolution.isEmpty())
    {
        _allSolution.push_back('0');
    }
    _allSolution.push_back(sign.objectName());
}

void CalcUI::Percent(QObject&, State state)
{
    if(!_allSolution.isEmpty() && _allSolution.back() != '%')
    {
        _allSolution.push_back('%');
    }
}
