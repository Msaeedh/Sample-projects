#include "calculator.h"
#include <QDebug>

Calculator::Calculator(QObject *parent) : QObject(parent) ,mDisplay(0.0) , mFirstOperand(0.0)
    ,mSecondOperand(0.0) , mWaitingForSecondOperand (false)
{
    connect(this , &Calculator::buttonClicked , this , &Calculator::onBtnClicked) ;
}

void Calculator::DigitPressed(QString digit)
{
    qDebug()<< "Calculator::DigitPressed(QString digit)" ;

    if(!mWaitingForSecondOperand)
    {
        mFirstOperand = mFirstOperand*10 + digit.toDouble() ;
        setDisplay(mFirstOperand) ;
    }else {
        mSecondOperand = mSecondOperand*10 + digit.toDouble() ;
        setDisplay(mSecondOperand) ;
    }
}

void Calculator::OperatorPressed(QString op)
{
    if(mWaitingForSecondOperand == true)
        return ;
    qDebug()<< "Calculator::OperatorPressed(QString op)" ;
    Op = op ;
    mWaitingForSecondOperand = true ;
    setDisplay(0.0) ;
}

void Calculator::clear()
{
    qDebug()<< "Calculator::clear()" ;

    setDisplay(0.0) ;
    mFirstOperand = 0.0 ;
    mSecondOperand = 0.0 ;
    Op = "" ;
    mWaitingForSecondOperand = false ;
}

void Calculator::equal_Pressed()
{
    qDebug() << "Calculator::equal_Pressed()" ;

    if(mWaitingForSecondOperand == false)
        return ;
    if(Op == "+")
        setDisplay(mFirstOperand + mSecondOperand) ;
    else if(Op == "-")
        setDisplay(mFirstOperand - mSecondOperand) ;
    else if(Op == "*")
        setDisplay(mFirstOperand * mSecondOperand) ;
    else if(Op == "/")
        setDisplay(mFirstOperand / mSecondOperand) ;

    mFirstOperand = display() ;
    mSecondOperand = 0.0 ;
    Op = "" ;
    mWaitingForSecondOperand = false ;
}

void Calculator::onBtnClicked(QString Btn)
{
    qDebug()<< "Calculator::onBtnClicked(QString Btn)";

    std::string btn = Btn.toStdString() ;
    switch (btn[0]) {
    case '+':
    case '-':
    case '*':
    case '/':
        OperatorPressed(Btn) ;
        break;
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
        DigitPressed(Btn) ;
        break;
    case '=':
        equal_Pressed();
        break;
    case 'C':
        clear() ;
        break;
    }
}

double Calculator::display() const
{
    return mDisplay;
}



//void Calculator::btc(QString btn)
//{
//    qDebug()<< "Calculator::btc(QString btn)" ;
//    btnClicked(btn) ;
//}

void Calculator::setDisplay(double newDisplay)
{
    if (qFuzzyCompare(mDisplay, newDisplay))
        return;
    mDisplay = newDisplay;
    emit DisplayChanged();
}
