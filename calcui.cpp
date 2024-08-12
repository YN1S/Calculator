#include "calcui.h"

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QDebug>

CalcUI::CalcUI(QWidget *parent)
    : QWidget(parent),
    _buttons({
    {'#', {inputEraseAll, {2, 0}, {1, 1}}}, {'C', {inputErase,  {2, 1}, {1, 1}}}, {'%', {inputPercent, {2, 2}, {1, 1}}}, {'/', {inputOtherSign,  {2, 3}, {1, 1}}},
    {'7', {inputNumber,   {3, 0}, {1, 1}}}, {'8', {inputNumber, {3, 1}, {1, 1}}}, {'9', {inputNumber,  {3, 2}, {1, 1}}}, {'*', {inputOtherSign,  {3, 3}, {1, 1}}},
    {'4', {inputNumber,   {4, 0}, {1, 1}}}, {'5', {inputNumber, {4, 1}, {1, 1}}}, {'6', {inputNumber,  {4, 2}, {1, 1}}}, {'-', {inputOtherSign,      {4, 3}, {1, 1}}},
    {'1', {inputNumber,   {5, 0}, {1, 1}}}, {'2', {inputNumber, {5, 1}, {1, 1}}}, {'3', {inputNumber,  {5, 2}, {1, 1}}}, {'+', {inputOtherSign,  {5, 3}, {1, 1}}},
    {'0', {inputNumber,   {6, 0}, {1, 2}}},                                       {'.', {inputDot,     {6, 2}, {1, 1}}}, {'=', {inputEqual,      {6, 3}, {1, 1}}}

}) {
    connect(&logic, &CalcLogic::ResultOfProcessing, this, &CalcUI::getResultsOfProcessing);
    setLayout(createLayout());
}

QGridLayout *CalcUI::createLayout()
{
    setDisplayParameters();

    QGridLayout* pUIGridLayout = new QGridLayout;
    pUIGridLayout->addWidget(_displaySolving, 0, 0, 1, 4);
    pUIGridLayout->addWidget(_displayAnswer, 1, 0, 1, 4);


    for(const auto [button, info] : _buttons){
        pUIGridLayout->addWidget(createButton(button), info.position.first, info.position.second, info.size.first, info.size.second);
    }

    return pUIGridLayout;
}

QPushButton *CalcUI::createButton(const QChar &str)
{
    QPushButton* pcmd = new QPushButton{str};
    pcmd->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    buttonAndState.insert({pcmd, _buttons.at(str).state});
    connect(pcmd, &QPushButton::clicked, this, &CalcUI::sendButtonToLogic);
    return pcmd;
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
    QPushButton *button = qobject_cast<QPushButton *>(sender());

    QString letter = button->text();
    logic.calculator(letter.at(0), buttonAndState.at(button));
}

void CalcUI::getResultsOfProcessing(QString AllSolution, QString result)
{
    _displaySolving->setText(AllSolution);
    _displayAnswer->setText(result);
}
