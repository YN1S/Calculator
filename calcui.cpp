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
    QObject *button = sender();

    logic.calculator(button->objectName(), buttonAndState.at(button));
}

void CalcUI::getResultsOfProcessing(QString AllSolution, QString result)
{
    _displaySolving->setText(AllSolution);
    _displayAnswer->setText(result);
}
