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

    QPushButton* buttonPlus = new QPushButton{"+"};
    buttonPlus->setObjectName("+");
    buttonPlus->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    _buttonAndState.insert({buttonPlus, State::inputOperator});
    connect(buttonPlus, &QPushButton::clicked, this, &CalcUI::sendButtonToLogic);

    QPushButton* buttonMinus = new QPushButton{"-"};
    buttonMinus->setObjectName("-");
    buttonMinus->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    _buttonAndState.insert({buttonMinus, State::inputOperator});
    connect(buttonMinus, &QPushButton::clicked, this, &CalcUI::sendButtonToLogic);

    QPushButton* buttonMultiply = new QPushButton{"*"};
    buttonMultiply->setObjectName("*");
    buttonMultiply->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    _buttonAndState.insert({buttonMultiply, State::inputOperator});
    connect(buttonMultiply, &QPushButton::clicked, this, &CalcUI::sendButtonToLogic);

    QPushButton* buttonDivide = new QPushButton{"/"};
    buttonDivide->setObjectName("/");
    buttonDivide->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    _buttonAndState.insert({buttonDivide, State::inputOperator});
    connect(buttonDivide, &QPushButton::clicked, this, &CalcUI::sendButtonToLogic);

    _pUIGridLayout->addWidget(buttonDivide, 2, 3, 1, 1);
    _pUIGridLayout->addWidget(buttonMultiply, 3, 3, 1, 1);
    _pUIGridLayout->addWidget(buttonPlus, 4, 3, 1, 1);
    _pUIGridLayout->addWidget(buttonMinus, 5, 3, 1, 1);

    logic._operatorToFunc =
    {
        {buttonPlus,     [this](QObject& dummy, State state){ logic.plus(dummy);     }},
        {buttonMinus,    [this](QObject& dummy, State state){ logic.minus(dummy);    }},
        {buttonMultiply, [this](QObject& dummy, State state){ logic.multiply(dummy); }},
        {buttonDivide,   [this](QObject& dummy, State state){ logic.divide(dummy);   }}
    };

    logic._percentForOperator =
    {
        {buttonPlus,     [this](QObject& dummy, State state){ logic.percentPlusOrMinus(dummy);                   }},
        {buttonMinus,    [this](QObject& dummy, State state){ logic.percentPlusOrMinus(dummy);                   }},
        {buttonMultiply, [this](QObject& dummy, State state){ logic.percentMultiplyOrDivideOrNotSelected(dummy); }},
        {buttonDivide,   [this](QObject& dummy, State state){ logic.percentMultiplyOrDivideOrNotSelected(dummy); }}
    };
}

QGridLayout *CalcUI::createLayout()
{
    setDisplayParameters();

    _pUIGridLayout = new QGridLayout;

    QPushButton* historyButton = new QPushButton{"History"};
    historyButton->setObjectName("History");
    historyButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    connect(historyButton, &QPushButton::clicked, this, &CalcUI::toggleScrollAreaVisibility);

    _pUIGridLayout->addWidget(historyButton, 0, 0, 1, 2);
    _pUIGridLayout->addWidget(_displaySolving, 1, 0, 1, 4);
    _pUIGridLayout->addWidget(_historyArea, 0, 4, 7, 3);


    createButtonsFromContainer(_pUIGridLayout, buttonsNameNumber, buttonsInfoNumber);
    // createButtonsFromContainer(_pUIGridLayout, buttonsNameSign,   buttonsInfoSign);
    createButtonsFromContainer(_pUIGridLayout, buttonsNameOther,  buttonsInfoOther);
    // createButtonsFromContainer(_pUIGridLayout, buttonNameoHistory,buttonInfoHistory);

    return _pUIGridLayout;
}

QPushButton *CalcUI::createButton(const QString &str, State state)
{
    QPushButton* pcmd = new QPushButton{str};
    pcmd->setObjectName(str);
    pcmd->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    _buttonAndState.insert({pcmd, state});
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
    // Инициализация QLineEdit для отображения текущего решения
    _displaySolving = new QLineEdit;
    _displaySolving->setReadOnly(true);
    // _displaySolving->setText("0");
    _displaySolving->setAlignment(Qt::AlignRight);
    _displaySolving->setStyleSheet("QLineEdit { font-size: 18pt}");
    _displaySolving->setMinimumSize(150, 50);
    _displaySolving->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    // Инициализация QLabel для отображения истории вычислений
    _displayHistory = new QLabel;
    // _displayHistory->setText("0");
    _displayHistory->setAlignment(Qt::AlignRight);  // Лучше использовать AlignLeft для истории
    _displayHistory->setWordWrap(true);  // Включаем перенос слов для длинных текстов

    // Инициализация QScrollArea для области с историей
    _historyArea = new QScrollArea(this);  // Инициализация с указанием родителя
    _historyArea->setWidget(_displayHistory);  // Устанавливаем QLabel как виджет для QScrollArea
    _historyArea->setWidgetResizable(true);  // Разрешаем изменение размера виджета внутри QScrollArea
    _historyArea->setFixedSize(150, 230);  // Устанавливаем фиксированный размер для области прокрутки
    _historyArea->setVisible(false);
}

void CalcUI::sendButtonToLogic()
{
    logic.calculator(sender(), _buttonAndState.at(sender()));
}

void CalcUI::toggleScrollAreaVisibility()
{
    _historyArea->setVisible(!_historyArea->isVisible());

    adjustSize();
}

void CalcUI::getResultsOfProcessing(QObject* sign, double number2, double result, State currentState)
{

    if(currentState == State::inputEraseAll)
    {
        _allSolution.clear();
        _displaySolving->clear();
        _allHistory.clear();
        _displayHistory->clear();
        _previousState = State::notSelected;
        return;
    }

    if(_previousState == State::inputEqual && currentState == State::inputNumber)
    {
        return;
    }

    if(_previousState == State::inputOperator && currentState == State::inputOperator)
    {
        _allSolution.chop(1);
        _allSolution.push_back(sign->objectName());
        _displaySolving->setText(_allSolution);
        return;
    }

    _previousState = currentState;

    static QString number;

    if(currentState == State::inputOperator && _isFirstOperator)
    {
        number.clear();
        _allSolution.push_back(sign->objectName());
        _displaySolving->setText(_allSolution);
        _isFirstOperator = false;
        return;
    }

    else if(currentState == State::inputOperator && !_isFirstOperator)
    {
        number.clear();
        _allHistory.push_back(_allSolution + '=' + QString::number(result) + "\n\n");
        _allSolution = QString::number(result) + sign->objectName();
        _displaySolving->setText(_allSolution);
        _displayHistory->setText(_allHistory);
        return;
    }

    if(currentState == State::inputEqual)
    {
        number.clear();
        _allHistory.push_back(_allSolution + '=' + QString::number(result) + "\n\n");
        _allSolution = QString::number(result);
        _displaySolving->setText(_allSolution);
        _displayHistory->setText(_allHistory);
        _isFirstOperator = true;
        return;
    }

    _allSolution.chop(number.size());
    number = QString::number(number2);
    _allSolution.push_back(number);

    _displaySolving->setText(_allSolution);
    _displayHistory->setText(_allHistory);
}
